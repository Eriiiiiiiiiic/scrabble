#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <fstream>

#ifndef BOARD_H_
#define BOARD_H_

using namespace std;


class Player;

class Board{
    public:
        vector<vector<char>> letters;
        vector<vector<bool>> joker;
        string ziehbare_steine;
        bool first_word_placed;
        string bonusfelder_for_points;

        Board();

        void display();

        bool move_is_valid(string, int, int, string);

        void word_score(string, int, int, string, Player*);

        // Addiert den Wert aller Steine des Gegenspielers die dieser
        // am Ende des Spiels noch uebrig hatte zu den Punkten des
        // Spielers, der das Spiel beendet hat.
        void final_letters_score(int*, Player*);

        void place_word(string, int, int, string, Player*);
};

#endif  // BOARD_H_
