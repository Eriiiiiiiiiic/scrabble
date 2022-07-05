#ifndef FINDEN_H_
#define FINDEN_H_

#include <iostream>
#include <vector>
#include <fstream>
#include "./dict_to_vector.h"

using namespace std;

vector<string> dictionary = dict_vector();

bool finden(int n0, int n, string word) { // file muss 2^k Zeilen haben!

    int halflenght = n/2;
    int middle = n0 + halflenght;

    //dict_word bestimmen: an der stelle middle
    string dict_word = dictionary[middle];

    if(n==1){
        return (dict_word == word);
    }


    if(middle <= 267752){

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
