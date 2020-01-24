#ifndef FROTA_H_
#define FROTA_H_

#include <vector>
#include "veiculo.h"
using namespace std;

class Frota {
	vector<Veiculo *> veiculos;
public:
	friend ostream & operator<<(ostream & o, const Frota & f);
    vector<Veiculo *> operator () (int anoM) const;
    float totalImposto() const;
    void adicionaVeiculo(Veiculo *v1);
    int numVeiculos();
    int menorAno();
};

#endif /*FROTA_H_*/
