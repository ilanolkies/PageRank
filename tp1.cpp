#include <iostream>
#include <fstream>
#include <string>
#include "MatrizRala.h"
#include "ReadWrite.h"
#include <vector>

using namespace std;

MatrizRala getMatrizDiagonal(MatrizRala &W) {
    MatrizRala ret(W.cantFilas(), W.cantColumnas());
    double acum[W.cantColumnas()];

    for(uint i = 0; i < W.cantColumnas(); ++i)
        acum[i] = 0;

    for (unsigned int i=0; i<W.cantFilas(); ++i)
        for(auto it = W[i].begin(); it != W[i].end(); ++it)
            acum[it->first] += it->second;

    for(uint i = 0; i < ret.cantFilas(); ++i)
        ret.asignar(i, i, (acum[i] != 0 ? 1/acum[i] : 0));

    return ret;
}

MatrizRala getMatrizIdentidad(uint tamano) {
    MatrizRala ret(tamano, tamano);
    for (uint i=0; i<tamano; i++) {
        ret.asignar(i, i, 1);
    }
    return ret;
}

double sumar(vector<double> v) {
    std::sort(v.begin(), v.end());      //Lo ordeno porque se van a sumar solo números positivos, y sumarlos en orden es
    double suma = 0;                    //la forma más precisa de calcular la suma exacta.
    for (int i=0; i<v.size(); i++)
        suma += v[i];
    return suma;
}

vector<double> dividir(vector<double> v, double num) {
    vector<double> ret(v.size());
    for (int i=0; i<v.size(); i++)
        ret[i] = v[i]/num;
    return ret;
}

vector<double> normalizar(pair<vector<double>,short> ranking) {
    vector<double> rk = ranking.first;
    double num = sumar(rk);
    vector<double> rkNorm = dividir(rk, num);
    return rkNorm;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "El programa debe cumplir el siguiente formato: ./tp1 archivo p" << std::endl;
        return 1;
    }

    // Execution parameters
    string input_file = argv[1];
    float p = atof(argv[2]);

    MatrizRala W = leerMatriz(input_file);

    MatrizRala D = getMatrizDiagonal(W);

    MatrizRala WD = W*D;

    WD * (-p);

    MatrizRala I = getMatrizIdentidad(W.cantFilas());

    MatrizRala I_pWD = I + WD;

    vector<double> b(W.cantFilas(), 1);

    pair<vector<double>,short> ranking = I_pWD.EG(b);

    vector<double> rn = normalizar(ranking);

    for (int i = 0; i < rn.size(); ++i) {
        cout << rn[i] << "\n";
    }

    return 0;
}
