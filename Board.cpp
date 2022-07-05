#include "./Board.h"
#include "./Player.h"
#include "./color.h"
#include "./finden.h"

using namespace std;


// ____________________________________________________________________________
Board::Board() {
    round = 1;
    for (int row = 0; row < 15; row ++) {
        vector<char> temp_vec(15,'.');
        letters.push_back(temp_vec);
        vector<bool> null_vec(15,0);
        joker.push_back(null_vec);
    }
//    ziehbare_steine = "EEEEEEEEEEEEEEENNNNNNNNNSSSSSSSIIIIIIRRRRRRTTTTTTUUUUUU"
//                      "AAAAADDDDHHHHGGGLLLOOOMMMMBBWZCCFFKKPJVXQY&&"; /* PÄJÖVÜXQY&& */
    ziehbare_steine = "EEEEEEEEEEEEAAAAAAAAAIIIIIIIIIOOOOOOOONNNNNNRRRRRR"
                      "TTTTTTLLLLSSSSUUUUDDDDGGGBBCCMMPPFFHHVVWWYYKJXQZ&&"; /* Englische Verteilung */
}

// ____________________________________________________________________________
void Board::display() {
    /* String markiert wo auf dem Brett welche Bonusfelder liegen. */
    string bonusfelder = "400100040001004"
                         "030002000200030"
                         "003000101000300"
                         "100300010003001"
                         "000030000030000"
                         "020002000200020"
                         "001000101000100"
                         "400100030001004"
                         "001000101000100"
                         "020002000200020"
                         "000030000030000"
                         "100300010003001"
                         "003000101000300"
                         "030002000200030"
                         "400100040001004";

    cout << "\n\n";

    cout << "     a  b  c  d  e  f  g  h  i  j  k  l  m  n  o \n";
    cout << "   .---------------------------------------------.\n";


    int feldindex = 0;
    for (int row = 0; row < 15; row ++) {

        if (row < 9) {
            cout << to_string(row + 1) << "  |";
        }
        else {
            cout << to_string(row + 1) << " |";
        }

        for (int col = 0; col < 15; col ++) {
            /* Stelle die Bonusfelder farblich dar. */
            string textfeld = "  ";
            textfeld.insert(1,1,letters[row][col]);
            if (bonusfelder[feldindex] == '0') {
                color("white", textfeld);
            } else if (bonusfelder[feldindex] == '1') {
                color("light_blue", textfeld);
            } else if (bonusfelder[feldindex] == '2') {
                color("blue", textfeld);
            } else if (bonusfelder[feldindex] == '3') {
                color("yellow", textfeld);
            } else if (bonusfelder[feldindex] == '4') {
                color("red", textfeld);
            }
            feldindex++;
        }
        if (row == 0) {
            cout << "|\t";
            color("light_blue", " . ");
            cout << " x2 Buchstabenwert\n";
        } else if (row == 1) {
            cout << "|\t";
            color("blue", " . ");
            cout << " x3 Buchstabenwert\n";
        } else if (row == 2) {
            cout << "|\t";
            color("yellow", " . ");
            cout << " x2 Wortwert\n";
        } else if (row == 3) {
            cout << "|\t";
            color("red", " . ");
            cout << " x3 Wortwert\n";
        } else if (row == 5) {
            cout << "|\t1 Punkt:   E,A,I,O,N,\n";
        } else if (row == 6) {
            cout << "|\t           R,T,L,S,U\n";
        } else if (row == 7) {
            cout << "|\t2 Punkte:  D,G\n";
        } else if (row == 8) {
            cout << "|\t3 Punkte:  B,C,M,P\n";
        } else if (row == 9) {
            cout << "|\t4 Punkte:  F,H,V,W,Y\n";
        } else if (row == 10) {
            cout << "|\t5 Punkte:  K\n";
        } else if (row == 11) {
            cout << "|\t8 Punkte:  J,X\n";
        } else if (row == 12) {
            cout << "|\t10 Punkte: Q,Z\n";
        } else if (row == 13) {
            cout << "|\t0 Punkte:  &\n";
        } else {
            cout << "|\n";
        }

    }
    cout << "   '---------------------------------------------'\n";
    cout << "\n\n";
}

bool Board::move_is_valid(string word, int x_start, int y_start, string direction) {

    vector<vector<char>> letters_temp = letters;

    for (int index = 0; index < word.length(); index++) {
        /* Mit ASCII einen 32 bit Shift zu Grossbuchstaben machen. */
        if (word[index]>='a' && word[index]<='z') {  //Test ob es ein schon Grossbuchstabe ist */
                word[index] = word[index] - 32; /* Falls nein, transformiere zu Grossbuchstaben */
        }
    }

    bool word_is_crossed = false;  // Das neu gesetzte Wort kreuzt ein bereits gelegtes Wort.
    if (direction == "v") {
        if (word.length() + y_start <= 15 && y_start >= 0) {
            for (int index = 0; index < word.length(); index++) {
                if (letters_temp[y_start + index][x_start] == '.') {
                    letters_temp[y_start + index][x_start] = char(word[index]);
                }
                else if (letters_temp[y_start + index][x_start] == char(word[index])) {
                    word_is_crossed = true;
                }
                else {
                    cout << "Sie versuchen etwas zu überschreiben!\n";
                    return false;
                }
            }
        }
        else{
            cout << "Das Wort ist zu lang oder die Anfangsposition unsinnig!\n";
            return false;
        }
    }
    if (direction == "h") {
        if (word.length() + x_start <= 15 && x_start >= 0) {
            for (int index = 0; index < word.length(); index++) {
                if (letters_temp[y_start][x_start + index] == '.') {
                    letters_temp[y_start][x_start + index] = char(word[index]);
                }
                else if (letters_temp[y_start][x_start + index] == char(word[index])) {
                    word_is_crossed = true;
                }
                else {
                    cout << "Sie versuchen etwas zu überschreiben!\n";
                    return false;
                }
            }
        }
        else {
            cout << "Das Wort ist zu lang oder die Anfangsposition unsinnig!\n";
            return false;
        }
    }
    if (!word_is_crossed && round > 1) {
        cout << "Das Wort ist nicht mit bereits gelegten Woertern verbunden!\n";
        return false;
    }






    /* Alle Buchstaben muessen hier in kleinbuchstaben für dictionary umgewandelt werden */
    for (int x = 0; x < 15; x++){
        for (int y = 0; y < 15; y++){
            /* Mit ASCII einen 32 bit Shift zu kleinbuchstaben machen. */
            if (letters_temp[y][x]>='A' && letters_temp[y][x]<='Z'){  //Test ob es ein schon kleinbuchstabe ist */
                letters_temp[y][x] = letters_temp[y][x] + 32; /* Falls nein, transformiere zu kleinbuchstaben */
            }
        }
    }

    //hier wird vertikal geprüft
    for(int x = 0; x < 15; x++){
        string current_word = "";
        bool gefunden = false;

        for(int y = 0; y < 15; y++){
            if(letters_temp[y][x]!='.'){
                current_word += letters_temp[y][x];
            }
            else{
                if(y!=0){
                    if(letters_temp[y][x]=='.'){  //Also ist das jetzige Element '.', aber davor war das Ende eines Buchstabens.
                        if(current_word.length()>1){ // einzelne Buchstaben sollen nicht als Wörter identifiziert werden! z.B. vertikal im Wort B E E soll nicht "B" überprüft werden.
                            //Jetzt liegt ein String/Block vor
                            //Ist es ein Wort?
                            bool gefunden = finden(0,524288,current_word);  // 2^19 kleinste ZweierPotenz größer als die Anzahl an Zeilen im dictionary

                            if(!gefunden){return false;}


                        }
                        current_word = ""; //Um die Suche nach einem neuen Wort zu erlauben
                    }
                }
            }
        }
    }

    cout << "\n\n";

    //hier wird horizontal geprüft
    for(int y = 0; y < 15; y++){
        string current_word = "";
        bool gefunden = false;

        for(int x = 0; x < 15; x++){
            if(letters_temp[y][x]!='.'){
                current_word += letters_temp[y][x];
            }
            else{
                if(x!=0){
                    if(letters_temp[y][x]=='.'){  //Also ist das jetzige Element '.', aber davor war das Ende eines Buchstabens.
                        if(current_word.length()>1){ // einzelne Buchstaben sollen nicht als Wörter identifiziert werden! z.B. vertikal im Wort B E E soll nicht "B" überprüft werden.
                            //Jetzt liegt ein String/Block vor
                            //Ist es ein Wort?

                            bool gefunden = finden(0,524288,current_word);  // 2^19 kleinste ZweierPotenz größer als die Anzahl an Zeilen im dictionary

                            if(!gefunden){return false;}


                        }
                        current_word = ""; //Um die Suche nach einem neuen Wort zu erlauben
                    }
                }
            }
        }
    }


    cout << "Es ist alles im Wörterbuch!\n";
    return true;
}

// ____________________________________________________________________________
void Board::place_word(string word, int x_start, int y_start,
                       string direction, Player* player) {

    vector<vector<char>> letters_temp = letters;

    bool error = false;

    /* Das Wort muss hier vllt in Großbuchstaben umgewandelt werden */
    for (int i = 0; i < word.length(); i++){
        /* Mit ASCII einen 32 bit Shift zu Großbuchstaben machen. */
        if (word[i]>='a' && word[i]<='z')  /*Ueberpruefe ob es ein kleinbuchstabe ist */
        {
            word[i] = word[i] - 32; /* Falls ja, transformiere zu Großbuchstaben */
        }
    }

    if (direction == "v") {
        if (word.length() + y_start <= 15 && y_start >= 0) {
            for (int index = 0; index < word.length(); index++) {
                if (letters_temp[y_start + index][x_start] == '.' || letters_temp[y_start + index][x_start] == char(word[index])) {
                    letters_temp[y_start + index][x_start] = char(word[index]);
                }
                else {
                    error = true;
                    break;
                }
            }
        }
        else{
            error = true;
            cout << " Das Wort ist zu lang oder die Anfangsposition unsinnig.\n";
        }
    }
    if (direction == "h") {
        if (word.length() + x_start <= 15 && x_start >= 0) {
            for (int index = 0; index < word.length(); index++) {
                if (letters_temp[y_start][x_start + index] == '.' || letters_temp[y_start][x_start + index] == char(word[index])) {
                    letters_temp[y_start][x_start + index] = char(word[index]);
                }
                else {
                    error = true;
                    break;
                }
            }
        }
        else {
            error = true;
            cout << " Das Wort ist zu lang oder die Anfangsposition unsinnig.\n";
        }
    }



    letters = letters_temp;

    /*Hier muessen die plazierten Wörter ueberprueft werden */

    /* Hier muss ueberprueft werden, ob Player p die nötigen Steine besitzt */

    /* Hier muss der Score richtig berechnet werden */



    /* Anfang von Score-Funktion: (man koennte eine eigene Method sogar machen */
    int points = 0;
    int multiplier = 1;

    /* String markiert wo auf dem Brett welche Bonusfelder liegen. */
    string bonusfelder = "400100040001004"
                         "030002000200030"
                         "003000101000300"
                         "100300010003001"
                         "000030000030000"
                         "020002000200020"
                         "001000101000100"
                         "400100030001004"
                         "001000101000100"
                         "020002000200020"
                         "000030000030000"
                         "100300010003001"
                         "003000101000300"
                         "030002000200030"
                         "400100040001004";

    for (int i = 0; i < word.length(); i++) {

        int value = 0;

        if (word[i]=='E' || word[i]=='A' || word[i]=='I' || word[i]=='O' || word[i]=='N' || word[i]=='R' || word[i]=='T' || word[i]=='L' || word[i]=='S' || word[i]=='U') {
            value = 1;
        }
        else if (word[i]=='D' || word[i]=='G') {
            value = 2;
        }
        else if (word[i]=='B' || word[i]=='C' || word[i]=='M' || word[i]=='P') {
            value = 3;
        }
        else if (word[i]=='F' || word[i]=='H' || word[i]=='V' || word[i]=='W' || word[i]=='Y') {
            value = 4;
        }
        else if (word[i]=='K') {
            value = 5;
        }
        else if (word[i]=='J' || word[i]=='X') {
            value = 8;
        }
        else if (word[i]=='Q' || word[i]=='Z') {
            value = 10;
        }
        else if (word[i]=='&') {
            value = 0;
        }
        else {
            value = 0;  /*Hier vllt Errormessage hinzufügen. Alternativ kann man solche Fehler im vorraus beheben */
        }


        if(direction=="v"){
            if(bonusfelder[(y_start+i)*15 + x_start] == '1'){
                value *= 2;
            }
            else if(bonusfelder[(y_start+i)*15 + x_start] == '2'){
                value *= 3;
            }
            else if(bonusfelder[(y_start+i)*15 + x_start] == '3'){
                multiplier *= 2;
            }
            else if(bonusfelder[(y_start+i)*15 + x_start] == '4'){
                multiplier *= 3;
            }
        }
        else if(direction=="h"){
            if(bonusfelder[y_start*15 + x_start + i] == '1'){
                value *= 2;
            }
            else if(bonusfelder[y_start*15 + x_start + i] == '2'){
                value *= 3;
            }
            else if(bonusfelder[y_start*15 + x_start + i] == '3'){
                multiplier *= 2;
            }
            else if(bonusfelder[y_start*15 + x_start + i] == '4'){
                multiplier *= 3;
            }
        }
        /* Das Feld muss auf Wort-Multiplier geprueft werden!! */

        points += value;
    }


    player->add_to_score(multiplier * points);






    /* Hier muss der Spieler die neuen Steine ziehen: void steine_ziehen */
    player->steine_ziehen(this);

}
