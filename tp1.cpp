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
            I = Identity(W.rows());

    Matrix WD = W*D;
    WD * (-p);
    WD + I;

    vector<double> e(W.rows(), 1);

    pair<vector<double>,short> ranking = WD.GaussianElimination(e);

    normalize(ranking.first);

    for (int i = 0; i < ranking.first.size(); ++i) {
        cout << ranking.first[i] << "\n";
    }

    return 0;
}
