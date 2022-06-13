#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#ifndef BOARD_H_
#define BOARD_H_


class Player;

class Board{
    public:
        std::vector<std::vector<char>> letters;
        std::string ziehbare_steine;


        Board();

        void display();

        void place_word(std::string, int, int, std::string, Player*);
};

#endif  // BOARD_H_
