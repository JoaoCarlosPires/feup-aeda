#include "aposta.h"
#include <iostream>
#include <sstream>

using namespace std;


bool Aposta::contem(unsigned num) const
{
    tabHInt::const_iterator itr;
    for (itr = numeros.begin(); itr != numeros.end(); itr++) {
        if ((*itr) == num) {return true;}
    }
    return false;
}


void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
    vector<unsigned> aux;
    bool add;
    for (int i = 0; i < valores.size(); i++) {
        if (n == 0) { break;}
        add = true;
        for (int k = 0; k < aux.size(); k++) {
            if (valores[i] == aux[k]) {add = false;}
        }
        if (add == true) {
            aux.push_back(valores[i]);
            this->numeros.insert(valores[i]);
            n--;
        }
    }

}

unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
    tabHInt::const_iterator itr;
    tabHInt::const_iterator itr2;
    int certos = 0;
    for (itr = numeros.begin(); itr != numeros.end(); itr++) {
        for (itr2 = sorteio.begin(); itr2 != sorteio.end(); itr2++) {
            if ((*itr) == (*itr2)) {certos++;}
        }
    }
    return certos;
}





