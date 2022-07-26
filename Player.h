//Projekt von Paul Schuh und Eric Trébuchon

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
        string name;
        Player();

        // Spiele zieht neue Steine aus dem Vorrat an ziehbaren Steinen,
        // bis er entweder wieder sieben Steine auf der Hand hat, oder bis
        // keine ziehbaren Steine mehr uebrig sind.
        void steine_ziehen(Board*);

        // Falls gegebenes Wort setzbar ist, werden die Buchstaben des Worts
        // aus 'stein' und 'steine_lst' entfernt und true wird zurueckgegeben.
        // Falls nicht, wird false zurueckgegeben.
        bool wort_setzen(Board*, string, bool*, int, int, string);

        // Die angegebenen Steine im uebergebenen string werden mit Steinen
        // aus dem Beutel (board->ziehbare_steine) getauscht, falls der
        // Spieler die zu tauschenden Steine besitzt. Können die Steine
        // getauscht werde, so wird true zurueckgegeben. Andernfalls ist
        // die Rückgabe false.
        bool steine_tauschen(Board*, string);

        // Addiert die gegebene Zahl zur privaten score Variable des Spielers.
        void add_to_score(int);

        // Gibt die private Variable score zurueck.
        int get_score();

        // Gibt das integer array steine_lst zurueck.
        int* get_steine_lst();

        // Gibt die Anzahl der Steine zuruck, die der Spieler besitzt.
        int get_num_steine();

        // Aendert den Namen des Spielers zum gegebenen string.
        void set_name_to(string);

        // Steine ausgeben, die der Spieler zur Verfuegung hat.
        void display(bool);

    private:
        int score;
        int steine_lst [27];
        int num_steine;
};

#endif  // PLAYER_H_
