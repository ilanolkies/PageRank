#include "VectorOperations.h"

double sum(vector<double> v) {
    sort(v.begin(), v.end()); // Order to get a more precise sum calculation

    double s = 0;

    for (int i=0; i<v.size(); i++)
        s += v[i];

    return s;
}

void devide(vector<double> &v, double n) {
    for (int i=0; i<v.size(); i++)
        v[i] = v[i]/n;
}

void normalize(vector<double> &ranking) {
    double s = sum(ranking);
    devide(ranking, s);
}
