#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "./Board.h"
#include "./Player.h"

using namespace std;


bool game_loop(Board *brett, Player *p, bool is_player1) {
    markierung:
    int x = 0;
    int y = 0;
    string coords = "";
    string word = "";
    string direction = "";
    int start_score = p->get_score();

    if (is_player1) cout << p->name << " ist am Zug! Hier das aktuelle Brett:\n";
    else cout << p->name  << " ist am Zug! Hier das aktuelle Brett:\n";
    brett->display();
    p->display();

    cout << "Wo soll dein Wort beginnen?: ";
    cin >> coords;
    // Wird statt Koordinaten ein "*" eingegeben, so koennen Steine aus der Hand
    // mit Steinen aus dem Beutel getauscht werden.
    if (coords == "*") {
        if (brett->ziehbare_steine.length() < 7) {
            cout << "Es sind nur noch weniger als sieben Steine im Beutel. ";
            cout << "Daher koennen keine Steine mehr getauscht werden!\n";
            string skip = "";
            cout << "Moechtest du eine Runde aussetzen? (y/n): ";
            cin >> skip;
            if (skip == "y") {
                if (is_player1) cout << p->name  << " setzt eine Runde aus.\n\n\n\n";
                else cout << p->name  << " setzt eine Runde aus.\n\n\n\n";
                return true;
            }
            goto markierung;
        }
        cout << "Welche Steine moechtest du tauschen?: ";
        cin >> word;
        if (word == "*") {  // Zug aussetzen
            if (is_player1) cout << p->name  << " setzt eine Runde aus.\n\n\n\n";
            else cout << p->name  << " setzt eine Runde aus.\n\n\n\n";
            return true;
        }
        if (p->steine_tauschen(brett, word)) {
            if (is_player1) cout << p->name  << " hat Steine weggelegt.\n";
            else cout << p->name  << " hat Steine weggelegt.\n";
            cout << "Er zieht neue Steine:\n";
            p->display();
            cout << "\n\n\n";
            return true;
        } else {
            cout << "Du besitzt nicht die Steine, die du tauschen moechtest.\n";
            cout << "Die Angabe der zu tauschenden Steine sollte z.B. AX&, oder ";
            cout << "XXAC sein, falls du etwa die Steine ABCLXX& besitzt.\n";
            cout << "Mit der Eingabe 'Welche Steine moechtest du tauschen?: *' ";
            cout << "kannst du eine Runde aussetzen.\n\n";
            goto markierung;
        }
    }
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
        cout << "Beispiele: b7, f15, a3, o11\n";
        cout << "Mit der Eingabe 'Wo soll dein Wort beginnen?: *' ";
        cout << "kannst du Steine von der Hand mit Steinen aus dem ";
        cout << "Beutel tauschen, oder eine Runde aussetzen.\n\n";
        goto markierung;
    }
    if (x < 0 || x > 14 || y < 0 || y > 14) {
        cout << "Bitte gib die Koordinaten in der Form xn an, dabei ist:\n";
        cout << " - x ein Buchstabe zwischen a und o (x Koordinate)\n";
        cout << " - n eine ganze Zahl zwischen 1 und 15 (y Koordinate)\n";
        cout << "Beispiele: b7, f15, a3, o11\n";
        cout << "Mit der Eingabe 'Wo soll dein Wort beginnen?: *' ";
        cout << "kannst du Steine von der Hand mit Steinen aus dem ";
        cout << "Beutel tauschen, oder eine Runde aussetzen.\n\n";
        goto markierung;
    }

    
    string word_j = "";
    cout << "Was ist dein Wort?: ";
    cin >> word_j;

    int index1 = 0;
    int index2 = 0;
    bool joker_pos[15] = {};
    while (index1 < word_j.length()) {
        if (word_j[index1] == '&') {
            index1++;
            char ch = word_j[index1];
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
                word.push_back(ch);
            } else {
                cout << "Das eingegebene Wort ist ungueltig!\n\n";  // Hier koennte noch eine genauere Fehlermeldung ausgegeben werden.
                goto markierung;
            }
            joker_pos[index2] = true;
            index2++;
        } else {
            char ch = word_j[index1];
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
                word.push_back(ch);
            } else {
                cout << "Das eingegebene Wort ist ungueltig!\n\n";  // Hier koennte noch eine genauere Fehlermeldung ausgegeben werden.
                goto markierung;
            }
            index2++;
            if (index2 >= 15) {
                cout << "Das eingegebene Wort ist zu lang!\n\n";
                goto markierung;
            }
        }
        index1++;
    }
    cout << word << endl;
    for (int i = 0; i < 15; i++) {
        cout << joker_pos[i];
    }
    cout << endl;
    

    cout << "Vertikal oder Horizontal?(v,h): ";
    cin >> direction;
    if (!(direction == "v" || direction == "h")) {
        cout << "Bitte gib eine gueltige Richtung an.\n\n";
        goto markierung;
    }
    cout << "\n";

    int anzahl_steine_inital = p->get_num_steine(); //Um Bingos zu erkennen

    if (brett->move_is_valid(word, x, y, direction)) {
        if (p->wort_setzen(brett, word, x, y, direction)) {
            brett->place_word(word, x, y, direction, p); //hier koennen bei schlechtem Input Fehler gethrowed werden und dann gecatched.

            if((p->get_num_steine()) - anzahl_steine_inital == -7){
                cout << "\nBINGO! Glückwunsch, du hast alle Steine gleichzeitig platziert, das sind 50 Bonuspunkte!\n\n";
                p->add_to_score(50);
            }

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

    if (is_player1) cout << p->name  << " hat gespielt!\n\n";
    else cout << p->name  << " hat gespielt!\n\n";
    if (brett->ziehbare_steine.length() == 0 && p->get_num_steine() == 0) { // Siegbedingung pruefen
        if (is_player1) cout << p->name  << " hat keine Steine und kann keine Steine mehr ziehen. ";
        else cout << p->name  << " hat keine Steine und kann keine Steine mehr ziehen. ";
        cout << "Damit ist das Spiel beendet!\n";
        cout << endl << "Hier ist das finale Brett:\n";
        brett->display();
        return false;
    }
    cout << "Er hat " << (p->get_score()-start_score) << " Punkte bekommen!\n";
    cout << "Insgesamte Punktzahl: " << p->get_score()<< "\n\n";
    cout << "Er zieht neue Steine:\n";
    p->display();
    cout << "\n\n\n";

    brett->first_word_placed = true;  // Das erste Wort wurde schon gesetzt.

    return true;
}

int main() {
cout <<"\n"
"\n"
"   ______________________________________________________________ \n"
" / \\                                                             \\.\n"
"|   |                                                            |.\n"
" \\_ |                              _     _     _                 |.\n"
"    |                             | |   | |   | |                |.\n"
"    |           ___  ___ _ __ __ _| |__ | |__ | | ___            |.\n"
"    |          / __|/ __| '__/ _` | '_ \\| '_ \\| |/ _ \\           |.\n"
"    |          \\__ \\ (__| | | (_| | |_) | |_) | |  __/           |.\n"
"    |          |___/\\___|_|  \\__,_|_.__/|_.__/|_|\\___|           |.\n"
"    |                                                            |.\n"
"    |                                                            |.\n"
"    |    ________________________________________________________|___\n"
"    |  /                                                            /.\n"
"    \\_/____________________________________________________________/.\n\n\n";





    srand(time(NULL));  // Random-Seed initalisieren

    Board brett;
    Player p1;
    Player p2;

    p1.steine_ziehen(&brett);
    p2.steine_ziehen(&brett);

    string name1;
    string name2;
    cout << "Herzlich Willkommen zu Scrabble!\n\n";
    cout << "Spieler 1, geben Sie Ihren Namen ein:\n";
    cin >> name1;
    p1.set_name_to(name1);

    cout << "\n";
    cout << "Spieler 2, geben Sie Ihren Namen ein:\n";
    cin >> name2;
    p2.set_name_to(name2);
    cout << "\n\n";

    int runde = 0;
    while (true) {
        // Einen Spielzug durchfuehren
        if (runde%2 == 0) {
            // Spieler 1 ist am Zug.
            if (!game_loop(&brett, &p1, true)) {
                // Spieler 1 hat das Spiel beendet.
                cout << name1 << " hat " << p1.get_score() << " Punkte und erhaelt zusaetzliche Punkte:\n\n";
                brett.final_letters_score(p2.get_steine_lst(), &p1);
                cout << "Insgesamt hat er also " << p1.get_score() << " Punkte.\n\n";
                cout << name2 << " hat " << p2.get_score() << " Punkte.\n\n";
                break;
            }
        } else {
            // Spieler 2 ist am Zug.
            if (!game_loop(&brett, &p2, false)) {
                // Spieler 2 hat das Spiel beendet.
                cout << name1 << " hat " << p1.get_score() << " Punkte.\n\n";
                cout << name2 << "hat " << p2.get_score() << " Punkte und erhaelt zusaetzliche Punkte:\n";
                brett.final_letters_score(p1.get_steine_lst(), &p2);
                cout << "Insgesamt hat er also " << p2.get_score() << " Punkte.\n\n";
                break;
            }
        }
        runde++; // Rundenzaehler erhoehen
    }
    if (p1.get_score() > p2.get_score()) {
        cout << "Damit gewinnt "<< name1 << ". Herzlichen Glueckwunsch!\n\n";
        cout << "♪┏(°.°)┛┗(°.°)┓┗(°.°)┛┏(°.°)┓ ♪ ♪┏(°.°)┛┗(°.°)┓┗(°.°)┛┏(°.°)┓ ♪ \n\n\n\n\n\n   ";
    } else if (p1.get_score() == p2.get_score()) {
        cout << "Es gibt also einen Gleichstand.";
    } else {
        cout << "Damit gewinnt "<< name1 << ". Herzlichen Glueckwunsch!\n\n";
        cout << "♪┏(°.°)┛┗(°.°)┓┗(°.°)┛┏(°.°)┓ ♪ ♪┏(°.°)┛┗(°.°)┓┗(°.°)┛┏(°.°)┓ ♪ \n\n\n\n\n\n   ";
    }

    return 0;
}
