#include "jogador.h"


void Jogador::adicionaAposta(const Aposta & ap)
{
this->apostas.insert(ap);
}


unsigned Jogador::apostasNoNumero(unsigned num) const
{
    tabHAposta::const_iterator itr;
    tabHInt::iterator itr2;
    tabHInt aux;
    int vezes = 0;
    for (itr = apostas.begin(); itr != apostas.end(); itr++) {
        aux = (*itr).getNumeros();
        for (itr2 = aux.begin(); itr2 != aux.end(); itr2++) {
            if ((*itr2) == num) {
                vezes++;
            }
        }
    }
	return vezes;
}


tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const
{
    tabHAposta::const_iterator itr;
	tabHAposta money;
	int certos = 0;
	for (itr = apostas.begin(); itr != apostas.end(); itr++) {
	    Aposta aux((*itr).getNumeros());
	    certos = aux.calculaCertos(sorteio);
	    if (certos >= 3) {
	        money.insert(aux);
	    }
	}
	return money;
}
