#include "./Board.h"
#include "./Player.h"


Board::Board(){
    for(int row= 1; row < 21; row ++) {
        std::vector<char> temp_vec(20,'.');
        letters.push_back(temp_vec);
    }
    /* HIer steht & f�r Joker */
    ziehbare_steine = "EEEEEEEEEEEEEEENNNNNNNNNSSSSSSSIIIIIIRRRRRRTTTTTTUUUUUUAAAAADDDDHHHHGGGLLLOOOMMMMBBWZCCFFKKPÄJÜVÖXQY&&";
    /*ziehbare_steine = []
        1 Punkt: E (15), N (9), S (7), I (6), R (6), T (6), U (6), A (5), D (4)
        2 Punkte: H (4), G (3), L (3), O (3)
        3 Punkte: M (4), B (2), W (1), Z (1)
        4 Punkte: C (2), F (2), K (2), P (1)
        6 Punkte: Ä (1), J (1), Ü (1), V (1)
        8 Punkte: Ö (1), X (1)
        10 Punkte: Q (1), Y (1)
        0 Punkte: Joker/Blanko (2) */
}

void Board::display(){
    std::cout << "\n\n";

    std::cout << "    a b c d e f g h i j k l m n o \n";


    for(int row= 1; row <= 15; row ++) {

        if(row <10){
            std::cout << std::to_string(row) << "   ";
        }
        else{
            std::cout << std::to_string(row) << "  ";
        }

        for(int col= 1; col <= 15; col ++) {
            std::cout << letters[row][col] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

void Board::place_word(std::string word, int x_start, int y_start, std::string direction, Player* player){

    std::vector<std::vector<char>> letters_temp = letters;

    bool error = false;

    /* Das Wort muss hier vllt in Großbuchstaben umgewandelt werden */

    if(direction == "d"){
        if(word.length() + y_start <= 15 && y_start >= 0){
            for(int index = 0; index < word.length(); index++){
                if(letters_temp[y_start + index][x_start] == '.' || letters_temp[y_start + index][x_start] == char(word[index])){
                    letters_temp[y_start + index][x_start] = char(word[index]);
                }
                else{
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
    if(direction == "r"){
        if(word.length() + x_start <= 15 && x_start >= 0){
            for(int index = 0; index < word.length(); index++){
                if(letters_temp[y_start][x_start + index] == '.' || letters_temp[y_start][x_start + index] == char(word[index])){
                    letters_temp[y_start][x_start + index] = char(word[index]);
                }
                else{
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
    if(error == false){
        letters = letters_temp;

        /*Hier m�ssen die plazierten W�rter �berpr�ft werden */

        /* Hier muss �berpr�ft werden, ob Player p die n�tigen Steine besitzt */

        /* Hier muss der Score richtig berechnet werden */



        /* Anfang von Score-Funktion: (man könnte eine eigene Method sogar machen */
        int points = 0;
        int multiplier = 1;

        for(int i = 0; i < word.length(); i++){

            int value = 0;

            if(word[i]=='E' || word[i]=='N' || word[i]=='S' || word[i]=='I' || word[i]=='R' || word[i]=='T' || word[i]=='U' || word[i]=='A' || word[i]=='D'){
                value = 1;
            }
            else if(word[i]=='H' || word[i]=='G' || word[i]=='L' || word[i]=='O'){
                value = 2;
            }
            else if(word[i]=='M' || word[i]=='B' || word[i]=='W' || word[i]=='Z'){
                value = 3;
            }
            else if(word[i]=='C' || word[i]=='F' || word[i]=='K' || word[i]=='P'){
                value = 4;
            }
            else if(word[i]=='Ä' || word[i]=='J' || word[i]=='Ü' || word[i]=='V'){
                value = 6;
            }
            else if(word[i]=='Ö' || word[i]=='X'){
                value = 8;
            }
            else if(word[i]=='Q' || word[i]=='Y'){
                value = 10;
            }
            else if(word[i]=='&'){
                value = 0;
            }
            else{
                value = 0;  /*Hier vllt Errormessage hinzufügen. Alternativ kann man solche Fehler im vorraus beheben */
            }

            /* Falls wir auf einem "Buchstabenwert x3" Feld sind, muss das hier noch hinzugefügt werden!! */
            /* Das Feld muss auf Wort-Multiplier geprüft werden!! */

            points += value;
        }


        player->add_to_score(multiplier * points);






        /* Hier muss der Spieler die neuen Steine ziehen: void steine_ziehen */

        /* Disese Steine m�ssen aus ziehbare_steine entfernt werden */
    }
}
