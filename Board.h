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
        string ziehbare_steine;


        Board();

        void display();

        bool is_in_dict(string, int, int, string);

        void place_word(string, int, int, string, Player*);
};

#endif  // BOARD_H_
