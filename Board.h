//Projekt von Paul Schuh und Eric Trébuchon

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

        // Stellt den aktuellen Zustand des Spielbretts graphisch im Terminal
        // dar.
        void display();

        // Prueft saemtliche Voraussetzungen an einen gueltigen Spielzug.
        bool move_is_valid(string, int, int, string);

        // Addiert den Wert des gegebenen Worts zu den Punkten des gegebenen
        // Spielers.
        void word_score(string, int, int, string, Player*);

        // Berechnet den Wert aller gegebenen Steine und addiert/subtrahiert
        // diese zu/von den Punkten des gegebenen Spielers.
        void final_letters_score(int*, Player*, bool);

        // Setzt das gegebene Wort an der gegebenen Stelle auf das Spielbrett.
        // Dabei werden dem Spieler auch die erzielten Punkte zugeschrienen.
        void place_word(string, int, int, string, Player*);
};

#endif  // BOARD_H_
