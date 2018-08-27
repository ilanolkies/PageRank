#ifndef PAGERANK_UTIL_CPP
#define PAGERANK_UTIL_CPP

#include <string>
#include "MatrizRala.h"

MatrizRala leerMatriz(string nombreArchivo);
void escribirRanking(string nombreArchivo, vector<double> ranking, double probabilidadDeSaltar);


#endif