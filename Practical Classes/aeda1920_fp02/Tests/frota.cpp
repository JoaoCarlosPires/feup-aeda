#include "frota.h"
#include <string>

using namespace std;

void Frota::adicionaVeiculo(Veiculo *v1) {
    veiculos.push_back(v1);
}

int Frota::menorAno() {
    int ano_menor = 0;
    vector<Veiculo *>::const_iterator itr = veiculos.begin();
    int i = 0;
    for (itr; itr != veiculos.end(); itr++) {
        if (i == 0) {
            ano_menor = (*itr)->getAno();
        } else if ((*itr)->getAno() < ano_menor) {
            ano_menor = (*itr)->getAno();
        }
        i++;
    }
    return ano_menor;
}

int Frota::numVeiculos() {
    return veiculos.size();
}

ostream &operator<<(ostream &o, const Frota &f) {
    vector<Veiculo *> veiculos = f.veiculos;
    vector<Veiculo *>::const_iterator itr = veiculos.begin();
    for (itr; itr != veiculos.end(); itr++) {
        (*itr)->info();
    }
}

vector<Veiculo *> Frota::operator()(int anoM) const {
    vector<Veiculo *> to_return;
    vector<Veiculo *>::const_iterator itr = veiculos.begin();
    for (itr ; itr != veiculos.end(); itr++) {
        if ((*itr)->getAno() == anoM) {
            to_return.push_back(*itr);
        }
    }
    return to_return;
}

float Frota::totalImposto() const {
    float total;
    vector<Veiculo *>::const_iterator itr = veiculos.begin();
    for (itr ; itr != veiculos.end(); itr++) {
        total += (*itr)->calcImposto();
    }
    return total;
}


