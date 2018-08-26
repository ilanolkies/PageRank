#include "MatrizRala.h"

#include <cmath>
#include <list>
#include <utility>
#include <sstream>
#include <iostream>

MatrizRala::MatrizRala() : width(0) {}

MatrizRala::MatrizRala(uint h, uint w) : m(h, map<uint,double>()) , width(w) {}

size_t MatrizRala::cantFilas() const {return m.size();}

size_t MatrizRala::cantColumnas() const {return width;}

void MatrizRala::asignar(uint f, uint c, const double value) {
    if (abs(value) < tolerancia) {
        m[f].erase(c);
    } else if (f < m.size() and c < width) {
        m[f][c] = value;
    }
}

const double MatrizRala::at(uint f, uint c) const {
    double result;
    if(m[f].count(c) == 0) {
        result = 0;
    } else {
        result = m[f].at(c);
    }
    return result;
}

double& MatrizRala::operator[](pair<uint, uint> p) {
    if (p.first < m.size() and p.second < width) {
        return m[p.first][p.second];
    }
    return m[0][0];//agregue esto solo para devolver algo en caso de que se invoque mal
}

MatrizRala MatrizRala::operator+(MatrizRala const &B) {
    if(cantFilas() == B.cantFilas() and cantColumnas() == B.cantColumnas()) {
        MatrizRala result(cantFilas(), cantColumnas());
        map<uint, double>::const_iterator it1 = m[0].begin();
        map<uint, double>::const_iterator it2 = B.m[0].begin();
        uint f = 0;
        while (f < cantFilas()) {
            while(it1 != m[f].end() or it2 != B.m[f].end()) {
                if (it2 == B.m[f].end() or (it1 != m[f].end() and it1->first < it2->first)){
                    result.asignar(f, it1->first, it1->second); // B tiene un valor nulo, solo coloco el valor de A.
                    it1++;
                } else if (it1 == m[f].end() or (it2 != B.m[f].end() and it1->first > it2->first)) {
                    result.asignar(f, it2->first, it2->second); // A tiene un valor nulo, solo coloco el valor de B.
                    it2++;
                } else {
                    result.asignar(f, it1->first, it1->second + it2->second); //Ambas matrices tienen valores no nulos.
                    it1++;
                    it2++;
                }
            }
            f++; //voy a la siguiente fila
            it1 = m[f].begin(); //acomodo los iteradores para la nueva fila.
            it2 = B.m[f].begin();
        }
        return result;
    } else {
        MatrizRala result; //no se puede operar, devuelvo matriz 0x0.
        return result;
    }
}

MatrizRala MatrizRala::operator*(const MatrizRala &B){
    if(cantColumnas() == B.cantFilas()) {
        MatrizRala result(cantFilas(), B.cantColumnas());
        for(uint i = 0; i < cantFilas(); ++i) { //Recorro las filas de A.
            for (auto it1 = m[i].cbegin(); it1 != m[i].cend(); ++it1) { //Recorro la i-ésima fila de A.
                for(auto it2 = B.m[it1->first].begin(); it2 != B.m[it1->first].end(); ++it2) {  //Si el it1 esta en columna j, recorro la fila j de B.
                    double sumando = it1->second * it2->second;  //"sumando" es a_ik*b_kj donde i = "i", k = "it1->first" y j = "it2->first".
                    auto it_res = result.m[i].find(it2->first); //Me fijo que hay en res_ij (= a_i1*b_1j + ... + a_i(k-1)*b_(k-1)j )
                    if(it_res == result.m[i].end()) //Si no estaba definido (era 0)...
                        result.m[i][it2->first] = sumando;  //lo defino como a_ik*b_kj.
                    else{   //Si sí estaba definido (no era 0)...
                        if(it_res->second - sumando == 0)   //pero al sumarle a_ik*b_kj va a dar 0...
                            result.m[i].erase(it_res);      //lo borro (vale 0);
                        else                                //y si no va a dar 0...
                            it_res->second += sumando;      //le sumo a_ik*b_kj.
                    }
                }
            }
        }
        return result;
    } else {
        return MatrizRala(); //No está definida la multiplicación.
    }
}

vector<double> MatrizRala::operator*(const vector<double>& v){
    MatrizRala vect_como_matriz(v.size(), 1);

    for(uint i = 0; i <v.size(); ++i) vect_como_matriz.asignar(i, 0, v[i]);

    vect_como_matriz = (*this)*vect_como_matriz;
    vector<double> res(cantFilas());

    for(uint i = 0; i < res.size(); ++i) res[i] = vect_como_matriz.at(i, 0);

    return res;
}

void MatrizRala::operator*(double valor) {
    double acum = 0;
    for (unsigned int f = 0; f<cantFilas(); f++) {
        map<uint, double>::iterator row_iterator = m[f].begin();
        while (row_iterator != m[f].end()) {
            if (valor != 0) {
                row_iterator->second *= valor;
            } else {
                m[f].erase(row_iterator);
            }
            row_iterator++;
        }
    }
}


/*
 * Funciones para mostrar la matriz
 */

string convertirAString(double num) {
    stringstream ss (stringstream::in | stringstream::out);
    ss << num;
    string cadena = ss.str();
    return cadena;
}

int cantidadDeDigitosMaxima(MatrizRala &M) {
    uint maximo = 0;
    uint cantDigitos = 1;
    for (unsigned int i=0; i < M.cantFilas(); i++) {
        for (auto it=M[i].cbegin(); it != M[i].cend(); ++it) {
            cantDigitos = convertirAString(it->second).length();
            if (maximo < cantDigitos)
                maximo = cantDigitos;
        }
    }
    return maximo;
}

string agregarEspacios(double valor, int cantidadMaxima) {
    string ret = convertirAString(valor);
    cantidadMaxima = cantidadMaxima - ret.length();
    for (int i=0; i < cantidadMaxima+1; i++) {
        ret = " " + ret;
    }
    return ret;
}

std::ostream& operator << (std::ostream &o, MatrizRala &B) {
    int cantDigitos = cantidadDeDigitosMaxima(B);
    for (unsigned int i = 0; i < B.cantFilas(); i++) {
        for (unsigned int j = 0; j < B.cantColumnas(); j++) {
            o << agregarEspacios(B.at(i, j), cantDigitos);
        }
        o << "\n";
    }
    return o;
}

void mostrar_matriz_por_consola(MatrizRala& m, string nombre_de_la_matriz){
    int cantDigitos = cantidadDeDigitosMaxima(m);
    std::cout << std::endl << nombre_de_la_matriz << " =  |";
    for(uint i = 0; i < m.cantFilas()*m.cantColumnas(); ++i){
        std::cout << agregarEspacios(m.at(i/m.cantColumnas(), i%m.cantColumnas()), cantDigitos);
        if(i%m.cantColumnas() < m.cantColumnas()-1)
            std::cout << ",  ";
        else {
            std::cout << "|" << std::endl;
            if(i != m.cantFilas()*m.cantColumnas()-1){
                string espacios = "";
                for(uint i = 0; i < nombre_de_la_matriz.size(); ++i) espacios += " ";
                std::cout << espacios << "    |";
            }
        }
    }
}

void mostrar_vector_por_consola(vector<double>& v, string nombre_del_vector){
    std::cout << std::endl << nombre_del_vector << " = [";
    for(uint i = 0; i < v.size()-1; ++i) std::cout << v[i] << ", ";
    if(!v.empty()) std::cout << v[v.size()-1] << "]";
}

MatrizRala vector2matrix(vector<double>& v, uint cant_filas){
    if(v.size()%cant_filas == 0){
        uint cant_columnas = v.size()/cant_filas;
        MatrizRala Res(cant_filas, cant_columnas);
        for(uint i = 0; i < v.size(); ++i) Res.asignar(i/cant_columnas, i%cant_columnas, v[i]);
        return Res;
    }
    return MatrizRala();
}
