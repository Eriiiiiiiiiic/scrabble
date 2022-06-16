#include "./Player.h"
#include "./Board.h"

using namespace std;


// ____________________________________________________________________________
Player::Player() {
    score = 0;
    for (int i = 0; i <= 6; i++) {
        stein[i] = ' ';
    }
}

// ____________________________________________________________________________
void Player::steine_ziehen(Board* board) {
    for (int i = 0; i <= 6; i++) {
        if(stein[i] == ' ' && board->ziehbare_steine.length()!= 0) {  /*&& board->ziehbare_steine.length()!= 0  WICHTIG FEHLT */
            int r = rand() % board->ziehbare_steine.length();      /* Zufällige Zahl von 0 bis zur Anzahl an Steinen -1*/
            stein[i] = char(board->ziehbare_steine[r]);
            board->ziehbare_steine.erase(r,1);
            /* Hier muss ein neuer Stein aus der Menge der Ziehbaren Steine gezogen weerden.
               Aus dieser Menge muss der Stein entfertnt werden. */
        }
    }
}

// ____________________________________________________________________________
void Player::stein_setzen(char letter) {
    for (int i = 0; i <= 6; i++) {
        if (stein[i] == letter) {
            stein[i] = ' ';
            break;
        }
    }
}

// ____________________________________________________________________________
void Player::add_to_score(int n) {
    score += n;
}

// ____________________________________________________________________________
int Player::get_score() {
    return score;
}

// ____________________________________________________________________________
char* Player::get_steine() {
    return stein;
}


void Player::display(){
    cout << "\n ~~~~~~=";
    for (int i = 0; i <= 6; i++) {
        cout << stein[i];
    }
    cout << "=~~~~~~ \n\n" ;
}
