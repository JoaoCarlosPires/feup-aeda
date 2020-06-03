#include "veiculo.h"
#include <iostream>

using namespace std;

Veiculo::Veiculo(string mc, int m, int a) : marca(mc), mes(m), ano(a) {
}

Motorizado::Motorizado(string mc, int m, int a, string c, int cil) : Veiculo(mc, m, a), combustivel(c), cilindrada(cil) {
}

Automovel::Automovel(string mc, int m, int a, string c, int cil) : Motorizado(mc, m, a, c, cil){
}

int Automovel::info() const {
    Motorizado::info();
    return 5;
}

Camiao::Camiao(string mc, int m, int a, string c, int cil, int cm) : Motorizado(mc, m, a, c, cil), carga_maxima(cm) {
}

int Camiao::info() const {
    Motorizado::info();
    cout << "Carga Maxima: " << carga_maxima << endl;
    return 6;
}

Bicicleta::Bicicleta(string mc, int m, int a, string t) : Veiculo(mc, m, a), tipo(t) {
}

int Bicicleta::info() const {
    cout << "Marca: " << marca << endl;
    cout << "Mes: " << mes << endl;
    cout << "Ano: " << ano << endl;
    cout << "Tipo: " << tipo << endl;
    return 4;
}

float Bicicleta::calcImposto() const {
    return 0;
}

string Motorizado::getCombustivel() const {
    return combustivel;
}

int Motorizado::info() const {
    cout << "Marca: " << marca << endl;
    cout << "Mes: " << mes << endl;
    cout << "Ano: " << ano << endl;
    cout << "Combustivel: " << combustivel << endl;
    cout << "Cilindrada: " << cilindrada << endl;
    return 5;
}

float Motorizado::calcImposto() const {
    if (getAno() > 1995) {
        if (getCombustivel() == "gasolina") {
            if (cilindrada <= 1000) {
                return 14.56;
            } else if (1000<cilindrada && cilindrada<=1300) {
                return 29.06;
            } else if (1300<cilindrada && cilindrada <=1750) {
                return 45.15;
            } else if(1750<cilindrada && cilindrada<=2600) {
                return 113.98;
            } else if (2600<cilindrada && cilindrada<=3500) {
                return 181.17;
            } else {
                return 320.89;
            }
        } else {
            if (cilindrada <= 1500) {
                return 14.56;
            } else if (1500<cilindrada && cilindrada<=2000) {
                return 29.06;
            } else if (2000<cilindrada && cilindrada <=3000) {
                return 45.15;
            } else {
                return 113.98;
            }
        }
    } else {
        if (getCombustivel() == "gasolina") {
            if (cilindrada <= 1000) {
                return 8.10;
            } else if (1000<cilindrada && cilindrada<=1300) {
                return 14.56;
            } else if (1300<cilindrada && cilindrada <=1750) {
                return 22.65;
            } else if(1750<cilindrada && cilindrada<=2600) {
                return 54.89;
            } else if (2600<cilindrada && cilindrada<=3500) {
                return 87.13;
            } else {
                return 148.37;
            }
        } else {
            if (cilindrada <= 1500) {
                return 8.10;
            } else if (1500<cilindrada && cilindrada<=2000) {
                return 14.56;
            } else if (2000<cilindrada && cilindrada <=3000) {
                return 22.65;
            } else {
                return 54.89;
            }
        }
    }
}

string Veiculo::getMarca() const {
    return marca;
}

int Veiculo::getAno() const {
    return ano;
}

int Veiculo::info() const {
    cout << "Marca: " << marca << endl;
    cout << "Mes: " << mes << endl;
    cout << "Ano: " << ano << endl;
    return 3;
}

bool Veiculo::operator<(const Veiculo &v) const {
    if (v.getAno() == ano) {
        return v.mes > mes;
    } else {
        return v.getAno() > ano;
    }
}
