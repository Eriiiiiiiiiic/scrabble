#include "./Board.h"
#include "./Player.h"
#include "./setcolor.h"


// ____________________________________________________________________________
Board::Board() {
    for (int row = 1; row < 21; row ++) {
        std::vector<char> temp_vec(20,'.');
        letters.push_back(temp_vec);
    }
    ziehbare_steine = "EEEEEEEEEEEEEEENNNNNNNNNSSSSSSSIIIIIIRRRRRRTTTTTTUUUUUU"
                      "AAAAADDDDHHHHGGGLLLOOOMMMMBBWZCCFFKKPÄJÜVÖXQY&&";

}

// ____________________________________________________________________________
void Board::display() {
    /* String markiert wo auf dem Brett welche Bonusfelder liegen. */
    std::string bonusfelder = "400100040001004"
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

    std::cout << "\n\n";

    std::cout << "     a  b  c  d  e  f  g  h  i  j  k  l  m  n  o \n";
    std::cout << "   .---------------------------------------------.\n";


    int feldindex = 0;
    for (int row = 1; row <= 15; row ++) {

        if (row <10) {
            std::cout << std::to_string(row) << "  |";
        }
        else {
            std::cout << std::to_string(row) << " |";
        }

        for (int col = 1; col <= 15; col ++) {
            /* Stelle die Bonusfelder farblich dar. */
            if (bonusfelder[feldindex] == '1') {
                setcolor( 0x30 );
            } else if (bonusfelder[feldindex] == '2') {
                setcolor( 0x17 );
            } else if (bonusfelder[feldindex] == '3') {
                setcolor( 0x60 );
            } else if (bonusfelder[feldindex] == '4') {
                setcolor( 0x47 );
            }

            std::cout << " " << letters[row][col] << " ";
            setcolor( 0x07 );
            feldindex++;
        }
        std::cout << "|\n";
    }
    std::cout << "   '---------------------------------------------'\n";
    std::cout << "\n\n";
}

// ____________________________________________________________________________
void Board::place_word(std::string word, int x_start, int y_start,
                       std::string direction, Player* player) {

    std::vector<std::vector<char>> letters_temp = letters;

    bool error = false;

    /* Das Wort muss hier vllt in Großbuchstaben umgewandelt werden */
    for (int i = 0; i < word.length(); i++){
        /* Mit ASCII einen 32 bit Shift zu Großbuchstaben machen. */
        if (word[i]>='a' && word[i]<='z')  /*Überprüfe ob es ein kleinbuchstabe ist */
        {
            word[i] = word[i] - 32; /* Falls ja, transformiere zu Großbuchstaben */
        }
    }

    if (direction == "d") {
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
            std::cout << " Das Wort ist zu lang oder die Anfangsposition unsinnig.\n";
        }
    }
    if (direction == "r") {
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
            std::cout << " Das Wort ist zu lang oder die Anfangsposition unsinnig.\n";
        }
    }
    if (error == false) {
        letters = letters_temp;

        /*Hier müssen die plazierten Wörter Überprüft werden */

        /* Hier muss Überprüft werden, ob Player p die nötigen Steine besitzt */

        /* Hier muss der Score richtig berechnet werden */



        /* Anfang von Score-Funktion: (man könnte eine eigene Method sogar machen */
        int points = 0;
        int multiplier = 1;

        for (int i = 0; i < word.length(); i++) {

            int value = 0;

            if (word[i]=='E' || word[i]=='N' || word[i]=='S' || word[i]=='I' || word[i]=='R' || word[i]=='T' || word[i]=='U' || word[i]=='A' || word[i]=='D') {
                value = 1;
            }
            else if (word[i]=='H' || word[i]=='G' || word[i]=='L' || word[i]=='O') {
                value = 2;
            }
            else if (word[i]=='M' || word[i]=='B' || word[i]=='W' || word[i]=='Z') {
                value = 3;
            }
            else if (word[i]=='C' || word[i]=='F' || word[i]=='K' || word[i]=='P') {
                value = 4;
            }
            else if (word[i]=='Ä' || word[i]=='J' || word[i]=='Ü' || word[i]=='V') {
                value = 6;
            }
            else if (word[i]=='Ö' || word[i]=='X') {
                value = 8;
            }
            else if (word[i]=='Q' || word[i]=='Y') {
                value = 10;
            }
            else if (word[i]=='&') {
                value = 0;
            }
            else {
                value = 0;  /*Hier vllt Errormessage hinzufügen. Alternativ kann man solche Fehler im vorraus beheben */
            }

            /* Falls wir auf einem "Buchstabenwert x3" Feld sind, muss das hier noch hinzugefügt werden!! */
            /* Das Feld muss auf Wort-Multiplier geprüft werden!! */

            points += value;
        }


        player->add_to_score(multiplier * points);






        /* Hier muss der Spieler die neuen Steine ziehen: void steine_ziehen */
        /* Disese Steine müssen aus ziehbare_steine entfernt werden */
        for (int i = 0; i < word.length(); i++) {
            player->stein_setzen(word[i]);
        }

        player->steine_ziehen(this);
    }
}
