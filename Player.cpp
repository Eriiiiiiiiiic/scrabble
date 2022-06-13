#include "./Player.h"
#include "./Board.h"

Player::Player(){
    score = 0;
}

void Player::steine_ziehen(Board* board){
    for(int i=0; i <= 6; i++){
        if(stein[i] != ' '){
            int r = rand() % board->ziehbare_steine.length();      /* Zufällige Zahl von 0 bis zur Anzahl an Steinen -1*/
            stein[i] = char(board->ziehbare_steine[r]);
            board->ziehbare_steine.erase(r,r+1);
            /* Hier muss ein neuer Stein aus der Menge der Ziehbaren Steine gezogen weerden.
               Aus dieser Menge muss der Stein entfertnt werden. */
        }
    }
}


void Player::stein_setzen(char letter){
    for(int i=0; i <= 6; i++){
        if(stein[i] == letter){
            stein[i] = ' ';
            break;
        }
    }
}


void Player::add_to_score(int n){
    score += n;
}

int Player::get_score(){
    return score;
}
