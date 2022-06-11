#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>

class Board;

class Player{
    public:
        Player(){
            score = 0;
        }
        void steine_ziehen(Board* pbrett){
            for(int i=0; i <= 6; i++){
                if(stein[i] != ' '){
                    int r = rand() % (&pbrett).ziehbare_steine.length();      // Returns a pseudo-random integer between 0 and RAND_MAX.
                    stein[i] = char((&pbrett).ziehbare_steine[r]);
                    (&pbrett).ziehbare_steine.erase(r,r+1);
            /* Hier muss ein neuer Stein aus der Menge der Ziehbaren Steine gezogen weerden.
             Aus dieser Menge muss der Stein entfertnt werden. */
                }
            }
        }
        void add_to_score(int n){
            score += n;
        }
        int get_score(){
            return score;
        }
    private:
        int score;
        char stein[7];
};


