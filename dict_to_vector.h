//Projekt von Paul Schuh und Eric Trébuchon

#ifndef DICT_TO_VECTOR_H
#define DICT_TO_VECTOR_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<string>  dict_vector() { // file muss 2^k Zeilen haben!
    vector<string> dict;
    string file_word; // Ein Speicherplatz für die Wörter im dicitionary
    ifstream fin;
    fin.open("dictionary.txt",ios::in); //öffnet die Datei zum lesen
    while(!fin.eof()){ //Solange man nicht am end-of-file ankommt oder es noch nicht gefunden hat, mache weiter.
        fin>>file_word;       //Neues Wort aus der Datei erhalten.
        dict.push_back(file_word); //in Diesem Fall ist das Wort nicht existent, also meldet es einen Fehler.
    }
    return dict;
}
#endif  // DICT_TO_VECTOR_H
