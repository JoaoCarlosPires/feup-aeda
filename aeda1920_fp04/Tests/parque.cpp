#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;

bool InfoCartao::operator <(const InfoCartao &info) const{
    if (frequencia > info.frequencia) {
        return true;
    } else if (frequencia < info.frequencia) {
        return false;
    } else {
        return nome < info.nome;
    }

}

bool compNome(const InfoCartao &info, const InfoCartao &info1) {
    return info.nome < info1.nome;
}

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }

unsigned int ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const { return lotacao-vagas; }



int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    int i = 0;
    vector<InfoCartao>::const_iterator itr = clientes.begin();
    for(itr ; itr!=clientes.end();itr++) {
        if ((*itr).nome == nome) {
            return i;
        }
        i++;
    }
    return -1;
}


int ParqueEstacionamento::getFrequencia(const string &nome) const
{   int freq = 0;
    int ver = 0;
    vector<InfoCartao>::const_iterator itr = clientes.begin();
    for(itr ; itr!=clientes.end();itr++) {
        if ((*itr).nome == nome) {
            freq = (*itr).frequencia;
            ver = 1;
        }
    }
    if (ver == 0) { throw ClienteNaoExistente(nome); }
    return freq;
}


bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;
	clientes.push_back(info);
	numClientes++;
	return true;
}


bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}


bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	vagas--;
	clientes[pos].frequencia += 1;
	return true;
}


bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

		

void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
    insertionSort(clientes);
}



void ParqueEstacionamento::ordenaClientesPorNome()
{
    sort(clientes.begin(), clientes.end(), compNome);
}



vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
    vector<string> nomes;
    ordenaClientesPorFrequencia();
    vector<InfoCartao>::const_iterator itr = clientes.begin();
    for (itr; itr!=clientes.end(); itr++) {
        if ((*itr).frequencia >= n1 && (*itr).frequencia <= n2) {
            nomes.push_back((*itr).nome);
        }
    }
    return nomes;
}


ostream & operator<<(ostream & os, const ParqueEstacionamento & pe)
{
    vector<InfoCartao>::const_iterator itr = pe.clientes.begin();
    for (itr; itr!=pe.clientes.end(); itr++) {
        os << (*itr).nome << endl;
        os << (*itr).presente << endl;
        os << (*itr).frequencia << endl;
    }
    return os;
}



InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
    int i = 0;
    vector<InfoCartao>::const_iterator itr = clientes.begin();
    for (itr; itr!=clientes.end(); itr++) {
        if (i == p) {
            return (*itr);
        }
        i++;
    }
    throw PosicaoNaoExistente(p);

}
