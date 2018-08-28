#include "MatrixOperations.h"

Matrix diagonal(Matrix &m) {
    Matrix d(m.rows(), m.columns());
    double acum[m.columns()];

    for (uint i = 0; i < m.columns(); ++i)
        acum[i] = 0;

    for (unsigned int i = 0; i < m.rows(); ++i)
        for (auto it = m[i].begin(); it != m[i].end(); ++it)
            acum[it->first] += it->second;

    for (uint i = 0; i < d.rows(); ++i)
        d.asign(i, i, (acum[i] != 0 ? 1 / acum[i] : 0));

    return d;
}

Matrix Identity(int n) {
    Matrix I(n, n);

    for (uint i = 0; i < n; i++)
        I.asign(i, i, 1);

    return I;
}
