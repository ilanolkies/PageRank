#ifndef PAGERANK_READWRTIE_CPP
#define PAGERANK_READWRTIE_CPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Matrix.h"
#include "dirent.h"

Matrix matrixFromFile(string input_file);

void escribirRanking(string nombreArchivo, vector<double> ranking, double probabilidadDeSaltar);
void listarDirectorio(const string& directorio, vector<string>& v);
void escribirVector(string nombreArchivo, vector<unsigned long> &vector);

#endif
