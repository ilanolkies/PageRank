#ifndef PAGERANK_MATRIX_H
#define PAGERANK_MATRIX_H

#include <map>
#include <vector>
#include <cmath>
#include <list>
#include <utility>
#include <sstream>
#include <iostream>


using namespace std;

#define tolerance 0.000001

class Matrix {

public:
    Matrix();

    Matrix(uint h, uint w);

    Matrix(const Matrix &orig) = default;

    Matrix& operator=(const Matrix &orig) = default;

    ~Matrix() = default;

    size_t rows() const;

    size_t columns() const;

    void asign(uint f, uint c, const double value);

    const double at(uint f, uint c) const;

    double& operator[](pair<uint,uint> p);

    map<uint, double>& operator[](uint i){ return m[i]; };

    void operator+(Matrix const &B);

    Matrix operator*(const Matrix &B);

    vector<double> operator*(const vector<double> &v);

    void operator*(double valor);

    pair<vector<double>,short> GaussianElimination(vector<double> b);
private:
    vector<map<uint, double> > m;
    size_t width;

    void resta_de_filas(uint fila_a_modificar, double escalar, uint fila_para_restar);

    void mostrar_matriz_por_consola(Matrix& m, string nombre_de_la_matriz);

    void mostrar_vector_por_consola(vector<double>& v, string nombre_del_vector);

    Matrix vector2matrix(vector<double>& v, uint cant_filas);

};


#endif //TP1_Matrix_H