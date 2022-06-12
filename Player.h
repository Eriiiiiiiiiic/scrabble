#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>

#ifndef PLAYER_H_
#define PLAYER_H_


class Board;

class Player{
    public:
        Player();

        void steine_ziehen(Board*);

        void add_to_score(int);

        int get_score();

    private:
        int score;
        char stein[7];
};

#endif  // PLAYER_H_
