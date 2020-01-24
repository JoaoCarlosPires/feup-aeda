#ifndef APOSTA_H_
#define APOSTA_H_

#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

typedef unordered_set<unsigned> tabHInt;

class Aposta
{
	tabHInt numeros;
public:
	Aposta() {};
	Aposta(tabHInt num): numeros(num) {}
	void geraAposta(const vector<unsigned> &valores, unsigned n=6);
	bool contem(unsigned num) const;
	unsigned calculaCertos(const tabHInt & sorteio) const;
	tabHInt getNumeros() const { return numeros; }
	int tamanho() const {return numeros.size();}
	int somaNumeros() const {
	    int soma;
	    tabHInt::const_iterator i;
	    for (i = numeros.begin(); i != numeros.end(); i++) {
	        soma += (*i);
	    }
	    return soma;
	}
};	

#endif /*APOSTA_H_*/
