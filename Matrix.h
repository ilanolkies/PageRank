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

#define tolerancia 0.000001

class Matrix {

public:
    Matrix(); //Construyo una "matriz" de 0x0

    Matrix(uint h, uint w); //Nueva matriz "Llena de ceros" de altura h, ancho w.

    Matrix(const Matrix &orig) = default; //default copy constructor

    Matrix& operator=(const Matrix &orig) = default; //default operador de asignacion

    ~Matrix() = default; //destructor por defecto

    size_t cantFilas() const;

    size_t cantColumnas() const;

    void asign(uint f, uint c, const double value); //Si el valor a asignar puede o no ser 0, usar esta función (y no operator[]).

    const double at(uint f, uint c) const; //útil si queres leer la posición sin asignar un 0 (operator[] crea el nodo sin importar si no asignas nada).

    double& operator[](pair<uint,uint> p); //Usar solo si se quieren hacer muchas asignaciones distintas de 0.
    // Cuidado, no usar para asignar ceros, usar asignar en tal caso.

    map<uint, double>& operator[](uint i){ return m[i]; }; //Devuelve una referencia a la i-esima fila.

    Matrix operator+(Matrix const &B);

    Matrix operator*(const Matrix &B);

    vector<double> operator*(const vector<double> &v);

    void operator*(double valor);

    pair<vector<double>,short> EG(vector<double> b);
private:
    vector<map<uint, double> > m; //La matriz va a tener un vector vertical que contiene las filas
    size_t width;

    void resta_de_filas(uint fila_a_modificar, double escalar, uint fila_para_restar);

    // ostream& operator << (ostream &o, Matrix &B);

    void mostrar_matriz_por_consola(Matrix& m, string nombre_de_la_matriz);

    void mostrar_vector_por_consola(vector<double>& v, string nombre_del_vector);

    Matrix vector2matrix(vector<double>& v, uint cant_filas);

};


#endif //TP1_Matrix_H