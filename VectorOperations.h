#ifndef PAGERANK_VECTOROPERATIONS_H
#define PAGERANK_VECTOROPERATIONS_H

#include <vector>

using namespace std;

double sum(vector<double> v);
void devide(const vector<double> &v, double num);
void normalize(vector<double> &ranking);

#endif //PAGERANK_VECTOROPERATIONS_H
