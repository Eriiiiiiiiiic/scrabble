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

    for(int i=0; i <= 10; i++){  /* Das abbruchskriterium ist noch nicht ganz richtig */
        int x = 0;
        int y = 0;
        string word = "";
        string direction = "";

        if(i%2 == 0){
            while (true) {
                cout << "Spieler 1 ist am Zug! Hier das aktuelle Brett:\n";
                brett.display();
                p1.display();

                cout << "Wo soll dein Wort beginnen? (x Koordinate):\n";
                cin >> x;
                cout << "Wo soll dein Wort beginnen? (y Koordinate):\n";
                cin >> y;

                cout << "Was ist dein Wort?:\n";
                cin >> word;

                cout << "Vertikal oder Horizontal?(v,h):\n";
                cin >> direction;

                if (p1.wort_setzen(word)) {
                    break;
                } else {
                    cout << "Dein Wort lässt sich nicht mit den gegebenen Buchstaben setzen. ";
                    cout << "Versuche ein anderes Wort.\n";
                }
            }

            brett.place_word(word,x,y,direction,&p1);
            cout << "Spieler 1 hat gespielt!\n\n";
            cout << "Er hat " << p1.get_score() << " Punkte!\n\n";
            cout << "Er zieht neue Steine:\n";
            p1.display();
            cout << "\n\n\n";
        }
        else{
            while (true) {
                cout << "Spieler 2 ist am Zug! Hier das aktuelle Brett:\n";
                brett.display();
                p2.display();

                cout << "Wo soll dein Wort beginnen? (x Koordinate):\n";
                cin >> x;
                cout << "Wo soll dein Wort beginnen? (y Koordinate):\n";
                cin >> y;

                cout << "Was ist dein Wort?:\n";
                cin >> word;

                cout << "Vertikal oder Horizontal?(v,h):\n";
                cin >> direction;

                if (p2.wort_setzen(word)) {
                    break;
                } else {
                    cout << "Dein Wort lässt sich nicht mit den gegebenen Buchstaben setzen. ";
                    cout << "Versuche ein anderes Wort.\n";
                }
            }

            brett.place_word(word,x,y,direction,&p2);
            cout << "Spieler 2 hat gespielt!\n\n";
            cout << "Er hat " << p2.get_score() << " Punkte!\n\n";
            cout << "Er zieht neue Steine:\n";
            p2.display();
            cout << "\n\n\n";
        }
    }

    return 0;
}
