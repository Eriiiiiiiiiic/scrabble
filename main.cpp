#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "./Board.h"
#include "./Player.h"
#include "./setcolor.h"

int main() {

    srand(time(NULL));  // Random-Seed initalisieren

    Board brett;
    Player p1;
    Player p2;

    setcolor( 0x07 );  // Initial color for program

    brett.display();

    std::cout << "Spieler 1 ist am Zug!\n";
    brett.place_word("worlds",2,4,"d",&p1);
    std::cout << "Spieler 1 hat gespielt!\n";
    std::cout << "Er hat " << p1.get_score() << " Punkte!\n";

    brett.display();

    std::cout << "Spieler 2 ist am Zug!\n";
    brett.place_word("Maths",5,2,"r",&p2);
    std::cout << "Spieler 2 hat gespielt!\n";
    std::cout << "Er hat " << p2.get_score() << " Punkte!\n";

    brett.display();

    std::cout << "Spieler 1 ist am Zug!\n";
    brett.place_word("message",5,1,"d",&p1);
    std::cout << "Fehler! Daher hat sich nichts verändert\n";
    std::cout << "Er hat immernoch " << p1.get_score() << " Punkte!\n";

    brett.display();

    return 0;
}
