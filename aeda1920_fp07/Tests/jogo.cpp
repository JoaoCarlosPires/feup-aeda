#include "jogo.h"
#include <sstream>

ostream &operator << (ostream &os, Circulo &c1)
{
    string estado;
    if (c1.getEstado() == true) {
        estado = "true";
    } else {
        estado = "false";
    }
    os << c1.getPontuacao() << "-" << estado << "-" << c1.getNVisitas() << "\n";
	return os;
}

BinaryTree<Circulo> Jogo::iniciaJogo(int pos, int niv, vector<int> &pontos, vector<bool> &estados)
{
    Circulo c1(pontos[pos],estados[pos]);
    if (niv==0) return BinaryTree<Circulo>(c1);
    BinaryTree<Circulo> filhoEsq=iniciaJogo(2 * pos + 1, niv - 1, pontos, estados);
    BinaryTree<Circulo> filhoDir=iniciaJogo(2 * pos + 2, niv - 1, pontos, estados);
    return BinaryTree<Circulo>(c1, filhoEsq, filhoDir);
}

Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados)
{
    jogo = iniciaJogo(0, niv, pontos, estados);
}


string Jogo::escreveJogo()
{
    BTItrLevel<Circulo> it(jogo);
    stringstream to_return("");
    while(!it.isAtEnd()) {
        to_return << it.retrieve();
        it.advance();
    }
    return to_return.str();
}


int Jogo::jogada()
{
	BTItrLevel<Circulo> itr(jogo);
	int pontuacao_final;
	int next_pos = 0;
	int actual_pos = 0;
	while(!itr.isAtEnd()) {
        actual_pos = next_pos;
        pontuacao_final = itr.retrieve().getPontuacao();
	    if (itr.retrieve().getEstado() == false) {
	        next_pos = 2*actual_pos+1;
	    } else {
	        next_pos = 2*actual_pos+2;
	    }
	    itr.retrieve().mudaEstado();
	    itr.retrieve().incNVisitas();
	    for (int i = actual_pos; i < next_pos; i++) {
	        if (!itr.isAtEnd()) {
	        itr.advance();
            } else {
	            break;
	        }
	    }

	}
	return pontuacao_final;
}


int Jogo::maisVisitado()
{
    int maisV = -1;
    BTItrLevel<Circulo> it(jogo);
    it.advance();
    while(!it.isAtEnd()) {
        if (it.retrieve().getNVisitas() > maisV) {
            maisV = it.retrieve().getNVisitas();
        }
        it.advance();
    }
	return maisV;

}

