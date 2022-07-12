#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "./Board.h"
#include "./Player.h"

using namespace std;


void game_loop(Board *brett, Player *p, bool is_player1) {
    int x = 0;
    int y = 0;
    string coords = "";
    string word = "";
    string direction = "";

    markierung:
        if (is_player1) cout << "Spieler 1 ist am Zug! Hier das aktuelle Brett:\n";
        else cout << "Spieler 2 ist am Zug! Hier das aktuelle Brett:\n";
        brett->display();
        p->display();

        cout << "Wo soll dein Wort beginnen? (z.B. b7): ";
        cin >> coords;
        // coords in int Koordinaten umwandeln
        // Die Koordinaten werden in Zahlen zwischen 0 und 14 umgewandelt.
        x = int (coords[0]) - 65;
        if (x >= 32) x -= 32;
        try {
            y = stoi(coords.substr(1)) - 1;
        } catch (const invalid_argument& ex) {
            cout << "Bitte gib die Koordinaten in der Form xn an, dabei ist:\n";
            cout << " - x ein Buchstabe zwischen a und o (x Koordinate)\n";
            cout << " - n eine ganze Zahl zwischen 1 und 15 (y Koordinate)\n";
            cout << "Beispiele: b7, f15, a3, o11\n\n\n";
            goto markierung;
        }
        if (x < 0 || x > 14 || y < 0 || y > 14) {
            cout << "Bitte gib die Koordinaten in der Form xn an, dabei ist:\n";
            cout << " - x ein Buchstabe zwischen a und o (x Koordinate)\n";
            cout << " - n eine ganze Zahl zwischen 1 und 15 (y Koordinate)\n";
            cout << "Beispiele: b7, f15, a3, o11\n\n\n";
            goto markierung;
        }

        cout << "Was ist dein Wort?: ";
        cin >> word;

        cout << "Vertikal oder Horizontal?(v,h): ";
        cin >> direction;
        if (!(direction == "v" || direction == "h")) {
            cout << "Bitte gib eine gueltige Richtung an.\n";
            goto markierung;
        }
        cout << "\n";

        if (brett->move_is_valid(word, x, y, direction)) {
            if (p->wort_setzen(brett, word, x, y, direction)) {
                brett->place_word(word, x, y, direction, p); //hier koennen bei schlechtem Input Fehler gethrowed werden und dann gecatched.
            }
            else {
                cout << "Dir fehlen die noetigen Steine!\n";
                cout << "Versuche ein anderes Wort.\n\n";
                goto markierung;
            }
        }
        else {
            cout << "Dein Wort ist fehlerhaft!\n";
            cout << "Versuche ein anderes Wort.\n\n";
            goto markierung;
        }


    cout << "Spieler 1 hat gespielt!\n\n";
    cout << "Er hat " << p->get_score() << " Punkte!\n\n";
    cout << "Er zieht neue Steine:\n";
    p->display();
    cout << "\n\n\n";
    return;
}

int main() {

    srand(time(NULL));  // Random-Seed initalisieren

    Board brett;
    Player p1;
    Player p2;

    (&p1)->steine_ziehen(&brett);
    (&p2)->steine_ziehen(&brett);

    for(int i=0; i <= 10; i++){  /* Das Abbruchskriterium ist noch nicht ganz richtig */
        // Einen Spielzug durchfuehren
        if (i%2 == 0) {
            game_loop(&brett, &p1, true);
        } else {
            game_loop(&brett, &p2, false);
        }
        (&brett)->round++; // Rundenzaehler erhoehen
    }

    return 0;
}
