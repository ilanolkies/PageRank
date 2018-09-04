#include "Mediciones.h"

Mediciones::Mediciones() {
    mediciones = vector<unsigned long>();
}


unsigned long Mediciones::medir(Matrix &m, vector<double> &b) {
    unsigned long delta = 0;

    for (int i = 0; i < CANTIDAD_MEDICIONES; i++) {
        unsigned long start, end;
        RDTSC_START(start);

        m.GaussianElimination(b);

        RDTSC_STOP(end);
        delta += end - start;
    }
    return delta / CANTIDAD_MEDICIONES;
}

Matrix Mediciones::readMatrix(const string &input_file) {
    Matrix W = matrixFromFile(input_file);
    return W;
}

Matrix Mediciones::getMatrix(Matrix &W, float p) {
    Matrix D = diagonal(W),
           I = Identity(W.rows());

    Matrix WD = W*D;
    WD * (-p);
    WD + I;

    return WD;
}

vector<unsigned long>& Mediciones::medir(const string &path, float p) {
    vector<string> grafos = vector<string>();
    listarDirectorio(path, grafos);
    sort(grafos.begin(), grafos.end());

    for (vector<string>::iterator it = grafos.begin(); it != grafos.end(); ++it) {
        string grafo = *it;
        Matrix W = readMatrix(grafo);

        vector<double> e(W.rows(), 1);

        Matrix WD = getMatrix(W, p);
        unsigned long medicion = medir(WD, e);
        mediciones.push_back(medicion);
    }
    return mediciones;
}