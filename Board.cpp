#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>

class Player;

class Board{
    public:
        std::vector<std::vector<char>> letters;
        std::string ziehbare_steine;


        Board(){
            for(int row= 1; row < 21; row ++) {
                std::vector<char> temp_vec(20,'.');
                letters.push_back(temp_vec);
            }
            /* HIer steht & für Joker */
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

        void display(){
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

        void place_word(std::string word, int x_start, int y_start, std::string direction, Player* pointer_to_player){

            std::vector<std::vector<char>> letters_temp = letters;

            bool error = false;

            if(direction == "d"){
                if(word.length() + y_start <= 15){
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
                    std::cout << " Das Wort ist zu lang\n";
                }
            }
            if(direction == "r"){
                if(word.length() + x_start <= 15){
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
                    std::cout << " Das Wort ist zu lang\n";
                }
            }
            if(error == false){
                letters = letters_temp;

                /*Hier müssen die plazierten Wörter überprüft werden */

                /* Hier muss überprüft werden, ob Player p die nötigen Steine besitzt */

                /* Hier muss der Score richtig berechnet werden */

                (&pointer_to_player).add_to_score(word.length());

                /* Hier muss der Spieler die neuen Steine ziehen: void steine_ziehen */

                /* Disese Steine müssen aus ziehbare_steine entfernt werden */
            }
        }
};

