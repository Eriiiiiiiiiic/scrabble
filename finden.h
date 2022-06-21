#ifndef FINDEN_H_
#define FINDEN_H_

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

bool finden(int n0, int n, string word) { // file muss 2^k Zeilen haben!

    int halflenght = n/2;
    int middle = n0 + halflenght;


    ifstream fin;
    string dict_word;
    fin.open("dictionary.txt",ios::in); //oeffnet die Datei zum lesen
    fin.seekg(15*middle);
    fin >> dict_word;
    fin.close();

    //cout << "dw: " << dict_word << "   ";
    if(n==1){
        return (dict_word == word);
    }


    if(middle <= 267752){

        fin.seekg(15*middle);



        if(dict_word == word){
            return true;
        }
        else if(dict_word < word){
            return finden(middle,halflenght,word);
        }
        else{
            return finden(n0,halflenght,word);
        }

    }
    else{
        return finden(n0,halflenght,word);
    }
}

#endif  // FINDEN_H_
