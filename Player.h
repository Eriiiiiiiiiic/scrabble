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

        // Spiele zieht neue Steine aus dem Vorrat an ziehbaren Steinen,
        // bis er entweder wieder sieben Steine auf der Hand hat, oder bis
        // keine ziehbaren Steine mehr uebrig sind.
        void steine_ziehen(Board*);

        void stein_setzen(char);

        // Falls gegebenes Wort setzbar ist, werden die Buchstaben des Worts
        // aus 'stein' und 'steine_lst' entfernt und true wird zurueckgegeben.
        // Falls nicht, wird false zurueckgegeben
        bool wort_setzen(Board*, string, int, int, string);

        bool steine_tauschen(Board*, string);

        void add_to_score(int);

        int* get_steine_lst();

        int get_num_steine();

        int get_score();

        // Steine ausgeben, die der Spieler zur Verfuegung hat.
        void display();

    private:
        int score;
//        char stein[7];
        int steine_lst [27];
        int num_steine;
};

#endif  // PLAYER_H_
