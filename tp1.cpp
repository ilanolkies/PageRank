#include <iostream>
#include <fstream>
#include <string>
#include "Matrix.h"
#include "MatrixOperations.h"
#include "VectorOperations.h"
#include "ReadWrite.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "El programa debe cumplir el siguiente formato: ./tp1 archivo p" << std::endl;
        return 1;
    }

    string input_file = argv[1];
    float p = atof(argv[2]);

    Matrix W = matrixFromFile(input_file),
            D = diagonal(W),
            I = Identity(W.cantFilas());

    Matrix WD = W*D;
    WD * (-p);
    Matrix I_pWD = I + WD;

    vector<double> e(W.cantFilas(), 1);

    pair<vector<double>,short> ranking = I_pWD.EG(e);

    normalize(ranking.first);

    for (int i = 0; i < ranking.first.size(); ++i) {
        cout << ranking.first[i] << "\n";
    }

    return 0;
}
