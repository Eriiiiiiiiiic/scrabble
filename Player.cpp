#include "./Player.h"
#include "./Board.h"

using namespace std;


// ____________________________________________________________________________
Player::Player() {
    score = 0;
    for (int i = 0; i <= 6; i++) {
        stein[i] = ' ';
    }
    for (int i = 0; i < 27; i++) {
        steine_lst[i] = 0;
    }
    num_steine = 0;
}

// ____________________________________________________________________________
void Player::steine_ziehen(Board* board) {
    for (int i = 0; i <= 6; i++) {
        if (num_steine < 7  && board->ziehbare_steine.length() != 0) {
            int r = rand() % board->ziehbare_steine.length();      /* Zuf�llige Zahl von 0 bis zur Anzahl an Steinen -1*/
            int index = int(board->ziehbare_steine[r]) - 65;
            if (index == -27) index = 26;
            steine_lst[index]++;
            num_steine++;
            board->ziehbare_steine.erase(r,1);
            /* Hier wird ein neuer Stein aus der Menge der Ziehbaren Steine gezogen.
               Aus dieser Menge wird der Stein dann entfernt. */
        } else {
            break;
        }
        // Das Array stein muss noch angepasst werden.
        int steinindex = 0;
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < steine_lst[i]; j++) {
                stein[steinindex] = char(i + 65);
                steinindex++;
            }
        }
        for (int i = 0; i < steine_lst[26]; i++) {
            stein[steinindex] = '&';
            steinindex++;
        }
    }
}

// ____________________________________________________________________________
void Player::stein_setzen(char letter) {
    if (steine_lst[int(letter)] > 0) {
        steine_lst[int(letter)]--;
        num_steine--;
    }
    for (int i = 0; i <= 6; i++) {
        if (stein[i] == letter) {
            stein[i] = ' ';
            break;
        }
    }
}

// ____________________________________________________________________________
bool Player::wort_setzen(string word) {
    int wordlength = word.length();
    int word_lst [27] = { };
    for (int i = 0; i < wordlength; i++) {
        int index = int(word[i]) - 65;
        if (index == -27) index = 26;
        word_lst[index]++;
    }
    // �berpr�fe, ob gegebenes Wort buchstabierbar ist.
    bool word_is_spellable = true;
    for (int i = 0; i < 27; i++) {
        if (steine_lst[i] < word_lst[i]) {
            word_is_spellable = false;
        }
    }
    if (!word_is_spellable) {
        return false;
    }
    for (int i = 0; i < 27; i++) {
        steine_lst[i] -= word_lst[i];
    }
    num_steine -= wordlength;
    return true;
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
//    for (int i = 0; i <= 6; i++) {
//        cout << stein[i];
//    }
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < steine_lst[i]; j++) {
            cout << char(i + 65);
        }
    }
    for (int i = 0; i < steine_lst[26]; i++) {
        cout << "&";
    }
    cout << "=~~~~~~ \n\n" ;
}
