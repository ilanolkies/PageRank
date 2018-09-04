//
// Created by christian on 29/08/18.
//

#ifndef PAGERANK_MEDICIONES_H
#define PAGERANK_MEDICIONES_H

#include "Matrix.h"
#include "rdtsc.h"
#include "ReadWrite.h"
#include "MatrixOperations.h"
#include <algorithm>

using namespace std;


class Mediciones {

public:
    Mediciones();

    unsigned long medir(Matrix &m, vector<double> &b);
    vector<unsigned long>& medir(const string &path, float p);
    Matrix readMatrix(const string &input_file);
    Matrix getMatrix(Matrix &W, float p);

private:
    int CANTIDAD_MEDICIONES = 20;
    vector<unsigned long> mediciones;

};


#endif //PAGERANK_MEDICIONES_H
