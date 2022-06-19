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
        string word = "";
        string direction = "";

        if(i%2 == 0){
            markierung1:
                cout << "Spieler 1 ist am Zug! Hier das aktuelle Brett:\n";
                brett.display();
                p1.display();

                cout << "Wo soll dein Wort beginnen? (x Koordinate): ";
                if (!(cin >> x) || x < 1 || x > 15) {  // möglicherweise falsche Eingabe abfangen
                    cout << "Bitte gib die x Koordinate als ganze Zahl zwischen 1 und 15 an.\n";
                    cin.clear();  // Fehlermeldungen löschen
                    cin.sync();  // falsche Eingabe entfernen
                    goto markierung1;
                }

                cout << "Wo soll dein Wort beginnen? (y Koordinate): ";
                if (!(cin >> y) || y < 1 || y > 15) {  // möglicherweise falsche Eingabe abfangen
                    cout << "Bitte gib die y Koordinate als ganze Zahl zwischen 1 und 15 an.\n";
                    cin.clear();  // Fehlermeldungen löschen
                    cin.sync();  // falsche Eingabe entfernen
                    goto markierung1;
                }

                cout << "Was ist dein Wort?: ";
                cin >> word;
                cout << "Vertikal oder Horizontal?(v,h): ";
                cin >> direction;
                cout << "\n";

                if (brett.is_in_dict(word)) {
                    if(p1.wort_setzen(word)){
                        brett.place_word(word,x,y,direction,&p1); //hier können bei schlechtem Input Fehler gethrowed werden und dann gecatched.
                    }
                    else{
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

                cout << "Wo soll dein Wort beginnen? (x Koordinate): ";
                if (!(cin >> x) || x < 1 || x > 15) {  // möglicherweise falsche Eingabe abfangen
                    cout << "Bitte gib die x Koordinate als ganze Zahl zwischen 1 und 15 an.\n";
                    cin.clear();  // Fehlermeldungen löschen
                    cin.sync();  // falsche Eingabe entfernen
                    goto markierung2;
                }

                cout << "Wo soll dein Wort beginnen? (y Koordinate): ";
                if (!(cin >> y) || y < 1 || y > 15) {  // möglicherweise falsche Eingabe abfangen
                    cout << "Bitte gib die y Koordinate als ganze Zahl zwischen 1 und 15 an.\n";
                    cin.clear();  // Fehlermeldungen löschen
                    cin.sync();  // falsche Eingabe entfernen
                    goto markierung2;
                }

                cout << "Was ist dein Wort?: ";
                cin >> word;

                cout << "Vertikal oder Horizontal?(v,h): ";
                cin >> direction;


                if (brett.is_in_dict(word)) {
                    if(p2.wort_setzen(word)){
                        brett.place_word(word,x,y,direction,&p2); //hier können bei schlechtem Input Fehler gethrowed werden und dann gecatched.
                    }
                    else{
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
    }

    return 0;
}
