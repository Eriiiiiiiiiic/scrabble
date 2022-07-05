#ifndef FINDEN_H_
#define FINDEN_H_

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

bool finden(string word) { // file muss 2^k Zeilen haben!
    bool gefunden = false;
    string file_word; // Ein Speicherplatz für die Wörter im dicitionary
    ifstream fin;
    fin.open("dictionary.txt",ios::in); //öffnet die Datei zum lesen
    while(!fin.eof() && !gefunden){ //Solange man nicht am end-of-file ankommt oder es noch nicht gefunden hat, mache weiter.
        fin>>file_word;       //Neues Wort aus der Datei erhalten.
        if(file_word == word){gefunden = true;} //(Könnte mindestens in O(log_2(words)) gehen) Hier wäre ein lexikographischer Vergleich und die Ordnung im Lexikon interessant.
        else if(file_word > word){cout << "just a tiny bit bigger: " << file_word << endl; return false;} //in Diesem Fall ist das Wort nicht existent, also meldet es einen Fehler.
    }
}
#endif  // FINDEN_H_
