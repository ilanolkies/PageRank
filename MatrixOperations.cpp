#include "MatrixOperations.h"

Matrix diagonal(Matrix &m) {
    Matrix d(m.cantFilas(), m.cantColumnas());
    double acum[m.cantColumnas()];

    for (uint i = 0; i < m.cantColumnas(); ++i)
        acum[i] = 0;

    for (unsigned int i = 0; i < m.cantFilas(); ++i)
        for (auto it = m[i].begin(); it != m[i].end(); ++it)
            acum[it->first] += it->second;

    for (uint i = 0; i < d.cantFilas(); ++i)
        d.asign(i, i, (acum[i] != 0 ? 1 / acum[i] : 0));

    return d;
}

Matrix Identity(int n) {
    Matrix I(n, n);

    for (uint i = 0; i < n; i++)
        I.asign(i, i, 1);

    return I;
}
