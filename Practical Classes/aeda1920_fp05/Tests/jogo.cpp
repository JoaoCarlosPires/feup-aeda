/*
 * jogo.cpp
 */

#include "jogo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = frase.find(' ');
  while (pos != string::npos) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}


Jogo::Jogo()
{
    criancas.clear();
}

Jogo::Jogo(list<Crianca>& lc2)
{
    criancas = lc2;
}


void Jogo::insereCrianca(const Crianca &c1)
{
    criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const
{
    return criancas;
}


string Jogo::escreve() const
{
    string to_return = "";
    list<Crianca>::const_iterator itr = criancas.begin();
    for (itr ; itr!=criancas.end(); itr++) {
        to_return += (*itr).escreve() + "\n";
    }
    return to_return;
}


Crianca& Jogo::perdeJogo(string frase)
{
    int npal = numPalavras(frase)-1;
    list<Crianca>::iterator it = criancas.begin();
    list<Crianca>::iterator ite = criancas.end();
    while (criancas.size()>1)
    {
        int nc = criancas.size();
        int p = npal%nc;
        for (int i=1; i<=p ; i++) {
            it ++;
            if (it == ite ) it =criancas.begin();
        }
        cout << "sai: " << it->escreve() << endl;
        it = criancas.erase(it);
        if (it == ite ) it =criancas.begin();
    }
    return *it;
}


list<Crianca>& Jogo::inverte()
{
    criancas.reverse();
    return this->criancas;
}


list<Crianca> Jogo::divide(unsigned id)
{
    list<Crianca>::const_iterator itr = criancas.begin();
    list<Crianca> res;
    for (itr ; itr!=criancas.end(); itr++) {
        if ((*itr).getIdade() > id) {
            res.push_back(*itr);
            criancas.erase(itr);
        }
    }
    return res;
}


void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
    list<Crianca>::const_iterator itr = l1.begin();
    for (itr ; itr!=l1.end(); itr++) {
        criancas.push_back((*itr));
    }
}


bool Jogo::operator==(Jogo& j2)
{
    list<Crianca>::const_iterator itr = this->criancas.begin();
    list<Crianca>::const_iterator itr2 = j2.criancas.begin();
    for (itr2 ; itr2!=j2.criancas.end(); itr2++, itr++) {
        if ((*itr) == (*itr2)) {
        } else {
            return false;
        }
    }
	return true;
}


list<Crianca> Jogo::baralha() const {
    list<Crianca> buffer = this->criancas;
    list<Crianca> nova;

    int rPos;

    /* initialize random seed: */
    srand(time(NULL));

    while (!buffer.empty()) {
        /* generate a random position: */
        rPos = rand() % buffer.size();
        list<Crianca>::iterator it = buffer.begin();
        for (int i = 0; i < rPos; i++, it++);
        nova.push_back(*it);
        buffer.erase(it);
    }

    return nova;
}
