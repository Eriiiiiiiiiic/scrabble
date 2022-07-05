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
        int round;


        Board();

        void display();

        bool move_is_valid(string, int, int, string);

        void place_word(string, int, int, string, Player*);
};

#endif  // BOARD_H_
