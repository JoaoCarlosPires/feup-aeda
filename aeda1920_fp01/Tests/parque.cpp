#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli): lotacao(lot), numMaximoClientes(nMaxCli) {}

unsigned int ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned int ParqueEstacionamento::getNumMaximoClientes() const { return numMaximoClientes; }

int ParqueEstacionamento::posicaoCliente(const string & nome) const {
    vector<InfoCartao>::const_iterator itr = clientes.begin();
    int i = 0;
    for (itr ; itr != clientes.end(); itr++) {
        if ((*itr).nome == nome) {
            return i;
        }
        i++;
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome) {
    InfoCartao cliente_to_add;
    cliente_to_add.nome = nome;
    cliente_to_add.presente = false;
    if (getNumMaximoClientes() != clientes.size()) {
        clientes.push_back(cliente_to_add);
        return true;
    } else {
        return false;
    }

}
bool ParqueEstacionamento::entrar(const string & nome) {
    int lota = 0;
    vector<InfoCartao>::iterator itr = clientes.begin();
    vector<InfoCartao>::iterator itr2 = clientes.begin();
    for (itr2 ; itr2 != clientes.end(); itr2++) {
        if ((*itr2).presente == true) {
            lota += 1;
        }
    }
    if (lota >= lotacao) {
        return false;
    }
    InfoCartao cliente_to_add;
    cliente_to_add.nome = nome;
    cliente_to_add.presente = true;
    for (itr ; itr != clientes.end(); itr++) {
        if ((*itr).nome == nome) {
            if ((*itr).presente == true) {
                return false;
            } else {
                clientes.erase(itr);
                clientes.push_back(cliente_to_add);
                return true;
            }
        }
    }
    return false;
}

bool ParqueEstacionamento::retiraCliente(const string & nome) {
    vector<InfoCartao>::iterator itr = clientes.begin();
    for (itr ; itr != clientes.end(); itr++) {
        if ((*itr).nome == nome) {
            if ((*itr).presente == true) {
                return false;
            } else {
                clientes.erase(itr);
                return true;
            }
        }
    }
    return false;
}

bool ParqueEstacionamento::sair(const string & nome) {
    vector<InfoCartao>::iterator itr = clientes.begin();
    InfoCartao cliente_to_add;
    cliente_to_add.nome = nome;
    cliente_to_add.presente = false;
    for (itr ; itr != clientes.end(); itr++) {
        if ((*itr).nome == nome) {
            if ((*itr).presente == true) {
                clientes.erase(itr);
                clientes.push_back(cliente_to_add);
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {
    int lota = 0;
    vector<InfoCartao>::const_iterator itr = clientes.begin();
    for (itr ; itr != clientes.end(); itr++) {
        if ((*itr).presente == true) {
            lota += 1;
        }
    }
    return lota;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}