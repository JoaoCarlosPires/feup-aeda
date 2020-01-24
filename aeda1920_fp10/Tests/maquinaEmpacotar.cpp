#include "maquinaEmpacotar.h"
#include <sstream>


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}

unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
	vector<Objeto>::iterator itr = objs.begin();
	while (itr != objs.end()) {
	    if ((*itr).getPeso() <= capacidadeCaixas) {
	        objetos.push(*itr);
	        itr = objs.erase(itr);
	    } else {
	        itr++;
	    }
	}
    return objetos.size();
}

Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {

	vector<Caixa> caixas_aux;
	while(!caixas.empty()) {
	    Caixa cx = caixas.top();
	    caixas.pop();
	    if (cx.getCargaLivre() >= obj.getPeso()) {
            for (unsigned i=0; i<caixas_aux.size(); i++) //repoe na fila de caixas as caixas retiradas da frente.
                caixas.push(caixas_aux[i]);
	        return cx;
	    } else {
            caixas_aux.push_back(cx);
	    }
	}
    for (int i = 0; i < caixas_aux.size(); i++) {
        caixas.push(caixas_aux[i]);
    }
    return Caixa(capacidadeCaixas);
}


unsigned MaquinaEmpacotar::empacotaObjetos() {
    while(!objetos.empty()) {
        Objeto o1 = objetos.top();
        objetos.pop();
        Caixa c1 = procuraCaixa(o1);
        c1.addObjeto(o1);
        caixas.push(c1);
        cout << "Objeto de peso " << o1.getPeso() << " -> caixa " << c1.getID() << endl;
    }
	return caixas.size();
}


string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
    stringstream to_return;
    if(objetos.empty()) to_return << "Nao ha objetos!" << endl;
	else {
    HEAP_OBJS buffer = objetos;
	while(!buffer.empty()) {
	    to_return << buffer.top() << endl;
	    buffer.pop();
	}
    }
	return to_return.str();
}


Caixa MaquinaEmpacotar::caixaMaisObjetos() const {

	if (caixas.empty()) {
	    throw MaquinaSemCaixas();
	} else {
        Caixa cx;
	    HEAP_CAIXAS aux = caixas;
        cx = aux.top();
	    aux.pop();
	    while(!aux.empty()) {
	        if (aux.top().getSize() > cx.getSize()) {
	            cx = aux.top();
	        }
	        aux.pop();
	    }
	return cx;
    }
}