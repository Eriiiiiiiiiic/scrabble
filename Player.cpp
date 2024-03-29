//Projekt von Paul Schuh und Eric Trébuchon

#include "./Player.h"
#include "./Board.h"

using namespace std;


// ____________________________________________________________________________
Player::Player() {
    score = 0;
    for (int i = 0; i < 27; i++) {
        steine_lst[i] = 0;
    }
    num_steine = 0;
}

// ____________________________________________________________________________
void Player::steine_ziehen(Board* board) {
    for (int i = 0; i < 7; i++) {
        if (num_steine < 7  && board->ziehbare_steine.length() != 0) {
            int r = rand() % board->ziehbare_steine.length();      /* Zufaellige Zahl von 0 bis zur Anzahl an Steinen -1*/
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
    }
}

// ____________________________________________________________________________
bool Player::wort_setzen(Board* board, string word, bool* joker_pos,
                         int x_start, int y_start, string direction) {

    int joker_lst [26] = { };  // Speichert fuer welche Buchstaben wie viele Joker verwendet werden.
    // Ueberpruefe, ob gegebenes Wort buchstabierbar ist.
    int difference = 0;  // Zaehlt die Anzahl an benoetigten Jokern.

    int num_placed_steine = 0;  // Anzahl der gesetzten Steine.
    int word_lst [27] = { };
    /* Schreibe das Wort in die Listen Form.
    Das Wort muss hier vllt in Grossbuchstaben umgewandelt werden. */
    for (int i = 0; i < word.length(); i++) {
        /* Mit ASCII einen 32 bit Shift zu Grossbuchstaben machen. */
        if (word[i] >= 'a' && word[i] <= 'z') {  /* Ueberpruefe ob es ein Kleinbuchstabe ist */
            word[i] = word[i] - 32;  /* Falls ja, transformiere zu Grossbuchstaben */
        }
        if (direction == "h") {
            if (board->letters[y_start][x_start + i] == '.') {
                int index = int(word[i]) - 65;
                if (joker_pos[i]) {  // Fals hier ein Joker liegen soll, wird dieser gelegt.
                    difference++;
                    num_placed_steine++;
                    if (difference > steine_lst[26]) {
                        // Es sind nicht genug Joker da, um das Wort doch noch
                        // Buchstabieren zu koennen.
                        return false;
                    }
                } else {
                    word_lst[index]++;
                    num_placed_steine++;
                }
            }
        } else if (direction == "v") {
            if (board->letters[y_start + i][x_start] == '.') {
                int index = int(word[i]) - 65;
                if (joker_pos[i]) {  // Fals hier ein Joker liegen soll, wird dieser gelegt.
                    difference++;
                    num_placed_steine++;
                    if (difference > steine_lst[26]) {
                        // Es sind nicht genug Joker da, um das Wort doch noch
                        // Buchstabieren zu koennen.
                        return false;
                    }
                } else {
                    word_lst[index]++;
                    num_placed_steine++;
                }
            }
        }
    }

    // Automatisch restliche Joker verteilen.
    for (int i = 0; i < 26; i++) {
        if (steine_lst[i] < word_lst[i]) {
            int wl_sl = word_lst[i] - steine_lst[i];
            difference += wl_sl;
            word_lst[i] -= wl_sl;
            for (int j = 0; j < wl_sl; j++) {
                joker_lst[i]++;
            }
            if (difference > steine_lst[26]) {
                // Es sind nicht genug Joker da, um das Wort doch noch
                // Buchstabieren zu koennen.
                return false;
            }
        }
    }
    // Positionen der gelegten Joker auf dem Brett speichern,
    if (difference > 0) {
        for (int i = word.length() - 1; i >= 0; i--) {
            int index = int(word[i]) - 65;
            if (direction == "h") {
                if (board->letters[y_start][x_start + i] == '.') {
                    if (joker_pos[i]) {
                        board->joker[y_start][x_start + i] = true;
                    } else if (joker_lst[index] > 0) {
                        joker_lst[index]--;
                        board->joker[y_start][x_start + i] = true;
                    }
                }
            } else if (direction == "v") {
                if (board->letters[y_start + i][x_start] == '.') {
                    if (joker_pos[i]) {
                        board->joker[y_start + i][x_start] = true;
                    } else if (joker_lst[index] > 0) {
                        joker_lst[index]--;
                        board->joker[y_start + i][x_start] = true;
                    }
                }
            }
        }
    }

    // Benoetigte Steine abziehen.
    for (int i = 0; i < 26; i++) {
        steine_lst[i] -= word_lst[i];
    }
    steine_lst[26] -= difference;
    num_steine -= num_placed_steine;
    return true;
}

// ____________________________________________________________________________
bool Player::steine_tauschen(Board* board, string letters) {
    int swap_lst [27] = { };
    /* Schreibe die Buchstaben in die Listen Form.
    Kleinbuchstaben muessen vllt in Grossbuchstaben umgewandelt werden. */
    for (int i = 0; i < letters.length(); i++) {
        if (letters[i] >= 'a' && letters[i] <= 'z') {  /* Ueberpruefe ob es ein Kleinbuchstabe ist */
            letters[i] = letters[i] - 32;  /* Mit ASCII einen 32 bit Shift zu Grossbuchstaben machen. */
            swap_lst[int(letters[i]) - 65]++;
        } else if (letters[i] >= 'A' && letters[i] <= 'Z') {  /* Ueberpruefe ob es ein Grossbuchstabe ist */
            swap_lst[int(letters[i]) - 65]++;
        } else if (letters[i] == '&') {  /* Ueberpruefe ob es ein Joker ist */
            swap_lst[26]++;
        } else {
            // In diesem Fall war die Eingabe ungueltig.
            return false;
        }
    }

    // Pruefe ob der Spieler die zu tauschenden Steine ueberhaupt besitzt.
    for (int i = 0; i < 27; i++) {
        if (steine_lst[i] < swap_lst[i]) {
            // In diesem Fall war die Eingabe ungueltig.
            return false;
        }
    }

    // Steine zuruecklegen und neue Steine ziehen.
    for (int i = 0; i < 27; i++) steine_lst[i] -= swap_lst[i];
    num_steine -= letters.length();
    //cout << board->ziehbare_steine << " + " << letters << " = ";
    board->ziehbare_steine += letters;
    //cout << board->ziehbare_steine << endl;
    steine_ziehen(board);

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
int* Player::get_steine_lst() {
    return steine_lst;
}

// ____________________________________________________________________________
int Player::get_num_steine() {
    return num_steine;
}

void Player::set_name_to(string input_name){
    name = input_name;
}

// ____________________________________________________________________________
void Player::display(bool standard_ASCII) {
    if (standard_ASCII) {
        cout << "\n       -------===##[   ";
    } else {
        cout << "\n⋆ ♔ ♕ ♖ ♗ ♘ ♙ -----♪   "; //♚ ♛ ♜ ♝ ♞ ♟ ♔ ♕ ♖ ♗ ♘ ♙
    }
    for (int i = 0; i < (7 - num_steine) / 2; i++) {
        cout << " ";
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < steine_lst[i]; j++) {
            cout << char(i + 65);
        }
    }
    for (int i = 0; i < steine_lst[26]; i++) {
        cout << "&";
    }
    for (int i = 0; i < (8 - num_steine) / 2; i++) {
        cout << " ";
    }
    if (standard_ASCII) {
        cout << "   ]##===-------       \n\n";
    } else {
        cout << "   ♪----- ♙ ♘ ♗ ♖ ♕ ♔ ⋆\n\n";
    }
}
