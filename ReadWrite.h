#ifndef PAGERANK_READWRTIE_CPP
#define PAGERANK_READWRTIE_CPP

#include <string>
#include "Matrix.h"

Matrix matrixFromFile(string input_file);

void escribirRanking(string nombreArchivo, vector<double> ranking, double probabilidadDeSaltar);

#endif
