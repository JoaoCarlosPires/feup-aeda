#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo<N,A> & inserirNo(const N &dados);
    Grafo<N,A> & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};

template<class N, class A>
Grafo<N, A>::Grafo() {

}

template<class N, class A>
Grafo<N, A>::~Grafo() {
    typename vector<No<N,A>*>::const_iterator itr = nos.begin();
    for (itr ; itr != nos.end(); itr++) {
        delete *itr;
    }
}

template<class N, class A>
int Grafo<N, A>::numArestas(void) const {
    int arestas = 0;
    typename vector<No<N,A>*>::const_iterator itr = nos.begin();
    for (itr ; itr != nos.end(); itr++) {
        arestas += (*itr)->arestas.size();
    }
    return arestas;
}

template<class N, class A>
int Grafo<N, A>::numNos(void) const {
    return nos.size();
}


template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);


// excecao NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N> 
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};

template <class N>
class ArestaRepetida {
public:
    N inicio;
    N fim;
    ArestaRepetida(N f, N i) {
        inicio = i;
        fim = f;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ar)
{ out << "Aresta repetida: " << ar.inicio << " , " << ar.fim; return out; }

template<class N, class A>
Grafo<N,A> & Grafo<N, A>::inserirNo(const N &dados) {
    typename vector<No<N,A>*>::const_iterator itr = nos.begin();
    for (itr ; itr != nos.end(); itr++) {
        if ((*itr)->info == dados) {
            throw NoRepetido<N>(dados);
        }
    }
    No<N,A> *no1 = new No<N,A>(dados);
    nos.push_back(no1);
    return *this;
}

template<class N, class A>
Grafo<N,A> &Grafo<N, A>::inserirAresta(const N &inicio, const N &fim, const A &val) {
    typename vector<No<N, A> *>::const_iterator itr = nos.begin();
    int i = 0;
    No<N,A> *fim_no = NULL;
    for (itr; itr != nos.end(); itr++) {
        if ((*itr)->info == inicio ) {
            i = 1;
        }
        if ((*itr)->info == fim) {
            fim_no = *itr;
            i = 2;
        }
    }
    if (i == 1) { throw NoInexistente<N>(inicio);}
    if (i == 2) { throw NoInexistente<N>(fim);}
    Aresta<N,A> ar1(fim_no, val);
    typename vector<No<N, A> *>::const_iterator itr3 = nos.begin();
    for (itr3; itr3 != nos.end(); itr3++) {
        typename vector<Aresta<N,A>>::iterator itr2 = (*itr3)->arestas.begin();
        for (itr2 ; itr2 != (*itr3)->arestas.end(); itr2++) {
            if (itr2->destino->info == fim) { throw ArestaRepetida<N>(inicio, fim);}
        }
        if ((*itr3)->info == inicio) {
            (*itr3)->arestas.push_back(ar1);
        }
    }
    return *this;
}


