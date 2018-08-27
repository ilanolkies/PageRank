
#ifndef TP1_MATRIZRALA_H
#define TP1_MATRIZRALA_H

#include <map>
#include <vector>
#include <cmath>
#include <list>
#include <utility>
#include <sstream>
#include <iostream>


using namespace std;

#define tolerancia 0.000001

class MatrizRala {

public:
    MatrizRala(); //Construyo una "matriz" de 0x0

    MatrizRala(uint h, uint w); //Nueva matriz "Llena de ceros" de altura h, ancho w.

    MatrizRala(const MatrizRala &orig) = default; //default copy constructor

    MatrizRala& operator=(const MatrizRala &orig) = default; //default operador de asignacion

    ~MatrizRala() = default; //destructor por defecto

    size_t cantFilas() const;

    size_t cantColumnas() const;

    void asignar(uint f, uint c, const double value); //Si el valor a asignar puede o no ser 0, usar esta función (y no operator[]).

    const double at(uint f, uint c) const; //útil si queres leer la posición sin asignar un 0 (operator[] crea el nodo sin importar si no asignas nada).

    double& operator[](pair<uint,uint> p); //Usar solo si se quieren hacer muchas asignaciones distintas de 0.
    // Cuidado, no usar para asignar ceros, usar asignar en tal caso.

    map<uint, double>& operator[](uint i){ return m[i]; }; //Devuelve una referencia a la i-esima fila.

    MatrizRala operator+(MatrizRala const &B);

    MatrizRala operator*(const MatrizRala &B);

    vector<double> operator*(const vector<double> &v);

    void operator*(double valor);

    pair<vector<double>,short> EG(vector<double> b);

private:
    vector<map<uint, double> > m; //La matriz va a tener un vector vertical que contiene las filas
    size_t width;

    void resta_de_filas(uint fila_a_modificar, double escalar, uint fila_para_restar);

    // ostream& operator << (ostream &o, MatrizRala &B);

    void mostrar_matriz_por_consola(MatrizRala& m, string nombre_de_la_matriz);

    void mostrar_vector_por_consola(vector<double>& v, string nombre_del_vector);

    MatrizRala vector2matrix(vector<double>& v, uint cant_filas);

};


#endif //TP1_MATRIZRALA_H