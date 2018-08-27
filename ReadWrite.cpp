#include "ReadWrite.h"
#include <iostream>
#include <fstream>

Matrix matrixFromFile(string input_file) {
    fstream input(input_file, ios_base::in);

    int paginas, links;
    input >> paginas >> links;

    Matrix matrix(paginas, paginas);

    int i, j;

    for (int k = 0; k < links; k++) {
        input >> i >> j;
        matrix.asign(j - 1, i - 1, 1);
    }

    input.close();

    return matrix;
}

void escribirRanking(string nombreArchivo, vector<double> ranking, double probabilidadDeSaltar) {
    ofstream salida(nombreArchivo, ios_base::out);

    salida << probabilidadDeSaltar << '\n';

    for (vector<double>::iterator it = ranking.begin(); it != ranking.end(); ++it)
        salida << *it << '\n';

    salida.close();
}
