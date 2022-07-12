#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>

#ifndef PLAYER_H_
#define PLAYER_H_

using namespace std;


class Board;

class Player{
    public:
        Player();

        void steine_ziehen(Board*);

        void stein_setzen(char);

        // Falls gegebenes Wort setzbar ist, werden die Buchstaben des Worts
        // aus 'stein' und 'steine_lst' entfernt und true wird zurueckgegeben.
        // Falls nicht, wird false zurueckgegeben
        bool wort_setzen(Board*, string, int, int, string);

        void add_to_score(int);

        char* get_steine();

        int get_score();

        // Steine ausgeben, die der Spieler zur Verfuegung hat.
        void display();

    private:
        int score;
        char stein[7];
        int steine_lst [27];
        int num_steine;
};

#endif  // PLAYER_H_
