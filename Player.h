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

        void stein_setzen(char);

        void add_to_score(int);

        char* get_steine();

        int get_score();

        void display();

    private:
        int score;
        char stein[7];
};

#endif  // PLAYER_H_
