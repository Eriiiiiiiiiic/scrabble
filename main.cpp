#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "./Board.h"
#include "./Player.h"

using namespace std;

int main() {

    srand(time(NULL));  // Random-Seed initalisieren

    Board brett;
    Player p1;
    Player p2;

    (&p1)->steine_ziehen(&brett);
    (&p2)->steine_ziehen(&brett);

    for(int i=0; i <= 10; i++){  /* Das Abbruchskriterium ist noch nicht ganz richtig */

        int x = 0;
        int y = 0;
        string coords = "";
        string word = "";
        string direction = "";

        if(i%2 == 0){
            markierung1:
                cout << "Spieler 1 ist am Zug! Hier das aktuelle Brett:\n";
                brett.display();
                p1.display();

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
                    goto markierung1;
                }
                if (x < 0 || x > 14 || y < 0 || y > 14) {
                    cout << "Bitte gib die Koordinaten in der Form xn an, dabei ist:\n";
                    cout << " - x ein Buchstabe zwischen a und o (x Koordinate)\n";
                    cout << " - n eine ganze Zahl zwischen 1 und 15 (y Koordinate)\n";
                    cout << "Beispiele: b7, f15, a3, o11\n\n\n";
                    goto markierung1;
                }

                cout << "Was ist dein Wort?: ";
                cin >> word;

                cout << "Vertikal oder Horizontal?(v,h): ";
                cin >> direction;
                if (!(direction == "v" || direction == "h")) {
                    cout << "Bitte gib eine gueltige Richtung an.\n";
                    goto markierung1;
                }
                cout << "\n";

                if (brett.move_is_valid(word, x, y, direction)) {
                    if (p1.wort_setzen(&brett, word, x, y)) {
                        brett.place_word(word,x,y,direction,&p1); //hier koennen bei schlechtem Input Fehler gethrowed werden und dann gecatched.
                    }
                    else {
                        cout << "Dir fehlen die noetigen Steine!\n";
                        cout << "Versuche ein anderes Wort.\n\n";
                        goto markierung1;
                    }
                }
                else {
                cout << "Dein Wort ist fehlerhaft!\n";
                cout << "Versuche ein anderes Wort.\n\n";
                goto markierung1;
                }


            cout << "Spieler 1 hat gespielt!\n\n";
            cout << "Er hat " << p1.get_score() << " Punkte!\n\n";
            cout << "Er zieht neue Steine:\n";
            p1.display();
            cout << "\n\n\n";
        }
        else{
            markierung2:
                cout << "Spieler 2 ist am Zug! Hier das aktuelle Brett:\n";
                brett.display();
                p2.display();

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
                    goto markierung2;
                }
                if (x < 0 || x > 14 || y < 0 || y > 14) {
                    cout << "Bitte gib die Koordinaten in der Form xn an, dabei ist:\n";
                    cout << " - x ein Buchstabe zwischen a und o (x Koordinate)\n";
                    cout << " - n eine ganze Zahl zwischen 1 und 15 (y Koordinate)\n";
                    cout << "Beispiele: b7, f15, a3, o11\n\n\n";
                    goto markierung2;
                }

                cout << "Was ist dein Wort?: ";
                cin >> word;

                cout << "Vertikal oder Horizontal?(v,h): ";
                cin >> direction;
                if (!(direction == "v" || direction == "h")) {
                    cout << "Bitte gib eine gueltige Richtung an.\n";
                    goto markierung2;
                }
                cout << "\n";

                if (brett.move_is_valid(word, x, y, direction)) {
                    if (p2.wort_setzen(&brett, word, x, y)) {
                        brett.place_word(word,x,y,direction,&p2); //hier koennen bei schlechtem Input Fehler gethrowed werden und dann gecatched.
                    }
                    else {
                        cout << "Dir fehlen die noetigen Steine!\n";
                        cout << "Versuche ein anderes Wort.\n";
                        goto markierung2;
                    }
                }
                else {
                cout << "Dein Wort ist fehlerhaft!\n";
                cout << "Versuche ein anderes Wort.\n";
                goto markierung2;
                }


            cout << "Spieler 2 hat gespielt!\n\n";
            cout << "Er hat " << p2.get_score() << " Punkte!\n\n";
            cout << "Er zieht neue Steine:\n";
            p2.display();
            cout << "\n\n\n";
        }
        (&brett)->round++;
    }

    return 0;
}
