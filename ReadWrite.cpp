#include "ReadWrite.h"
#include <iostream>
#include <fstream>

MatrizRala leerMatriz(string nombreArchivo) {
    fstream entrada(nombreArchivo, ios_base::in);

    int cantidadTotalDePaginas;
    int cantidadTotalDeLinks;

    entrada >> cantidadTotalDePaginas >> cantidadTotalDeLinks;

    MatrizRala ret(cantidadTotalDePaginas, cantidadTotalDePaginas);

    int i, j;

    for (int k = 0; k<cantidadTotalDeLinks; k++) {
        entrada >> i >> j;
        ret.asignar(j-1, i-1, 1);
    }

    entrada.close();

    return ret;
}

void escribirRanking(string nombreArchivo, vector<double> ranking, double probabilidadDeSaltar) {
    ofstream salida(nombreArchivo, ios_base::out);

    salida << probabilidadDeSaltar << '\n';

    for (vector<double>::iterator it = ranking.begin() ; it != ranking.end(); ++it)
        salida << *it << '\n';

    salida.close();
}
