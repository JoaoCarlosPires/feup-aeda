#include <iostream>
#include <string>
#include <fstream>
#include "dicionario.h"
#include "bst.h"

using namespace std;

BST<PalavraSignificado> Dicionario::getPalavras() const {
	return palavras;
}

bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const {
     return palavra < ps1.palavra;
}

bool PalavraSignificado::operator == (const PalavraSignificado &ps1) const {
    return palavra == ps1.palavra;
}

void Dicionario::lerDicionario(ifstream &fich)
{
    string pal, sig;
    while(!fich.eof()) {
        getline(fich,pal);
        getline(fich,sig);
        PalavraSignificado new_pal(pal, sig);
        palavras.insert(new_pal);
    }
}


string Dicionario::consulta(string palavra) const
{
    PalavraSignificado p1(palavra,"");
    PalavraSignificado px=palavras.find(p1);
    PalavraSignificado pNotFound("","");
    if (px==pNotFound)
    {
        BSTItrIn<PalavraSignificado> it(palavras);
        string palAntes="",signifAntes="";
        while (!it.isAtEnd() && it.retrieve()<p1)
        {
            palAntes=it.retrieve().getPalavra();
            signifAntes=it.retrieve().getSignificado();
            it.advance();
        }
        string palApos="",signifApos="";
        if (!it.isAtEnd())
        {
            palApos=it.retrieve().getPalavra();
            signifApos=it.retrieve().getSignificado();
        }
        throw PalavraNaoExiste(palAntes,signifAntes,palApos,signifApos);
    }
    else
        return px.getSignificado();
}


bool Dicionario::corrige(string palavra, string significado)
{
    iteratorBST<PalavraSignificado> itr = palavras.begin();
    for (itr ; itr != palavras.end(); itr++) {
        if ((*itr).getPalavra() == palavra) (*itr).setSignificado(significado); return true;
    }
    palavras.insert(PalavraSignificado(palavra, significado));
    return false;
}


void Dicionario::imprime() const
{
    iteratorBST<PalavraSignificado> itr = palavras.begin();
    for (itr ; itr != palavras.end(); itr++) {
        cout << (*itr).getPalavra() << endl;
        cout << (*itr).getSignificado() << endl;
    }
}

