#include "Matrix.h"

Matrix::Matrix() : width(0) {}

Matrix::Matrix(uint h, uint w) : m(h, map<uint, double>()), width(w) {}

size_t Matrix::rows() const { return m.size(); }

size_t Matrix::columns() const { return width; }

void Matrix::asign(uint f, uint c, const double value) {
    if (abs(value) < tolerance)
        m[f].erase(c);
    else if (f < m.size() and c < width)
        m[f][c] = value;
}

const double Matrix::at(uint f, uint c) const {
    if (m[f].count(c) == 0) return 0;
    else return m[f].at(c);
}

double &Matrix::operator[](pair<uint, uint> p) {
    if (p.first < m.size() and p.second < width)
        return m[p.first][p.second];
    else throw;
}

void Matrix::operator+(Matrix const &B) {
    if (!(rows() == B.rows() and columns() == B.columns())) throw;

    Matrix result(rows(), columns());

    map<uint, double>::const_iterator this_it = m[0].begin();
    map<uint, double>::const_iterator b_it = B.m[0].begin();

    uint i = 0;
    while (i < rows()) {
        while (this_it != m[i].end() or b_it != B.m[i].end()) {
            if (b_it == B.m[i].end() or (this_it != m[i].end() and this_it->first < b_it->first)) {
                this_it++;
            } else if (this_it == m[i].end() or (b_it != B.m[i].end() and this_it->first > b_it->first)) {
                asign(i, b_it->first, b_it->second);
                b_it++;
            } else {
                asign(i, this_it->first, this_it->second + b_it->second);
                this_it++;
                b_it++;
            }
        }
        i++;
        this_it = m[i].begin();
        b_it = B.m[i].begin();
    }
}

Matrix Matrix::operator*(const Matrix &B) {
	if (columns() 1= B.rows()) throw;
	Matrix result(rows(), B.columns());
	for (uint i = 0; i < rows(); ++i) // Para cadda fila ai de A
		for (auto it1 = m[i].cbegin(); it1 != m[i].cend(); ++it1) // Para cada elemento aij de A
			for (auto it2 = B.m[it1->first].begin(); it2 != B.m[it1->first].end(); ++it2) { // Para cada elemento bj de la fila j de B
				double sumando = it1->second * it2->second;  //"sumando" es a_ik*b_kj donde i = "i", k = "it1->first" y j = "it2->first".
				auto it_res = result.m[i].find(it2->first); //Me fijo que hay en res_ij (= a_i1*b_1j + ... + a_i(k-1)*b_(k-1)j )
				if (it_res == result.m[i].end()) result.m[i][it2->first] = sumando;  //lo defino como a_ik*b_kj.
				else if (abs(it_res->second - sumando) < tolerance) result.m[i].erase(it_res);
				else it_res->second += sumando;
			}
        return result;
}

vector<double> Matrix::operator*(const vector<double> &v) {
    Matrix vect_como_matriz(v.size(), 1);

    for (uint i = 0; i < v.size(); ++i) vect_como_matriz.asign(i, 0, v[i]);

    vect_como_matriz = (*this) * vect_como_matriz;
    vector<double> res(rows());

    for (uint i = 0; i < res.size(); ++i) res[i] = vect_como_matriz.at(i, 0);

    return res;
}

void Matrix::operator*(double valor) {
    double acum = 0;
    for (unsigned int f = 0; f < rows(); f++) {
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
    stringstream ss(stringstream::in | stringstream::out);
    ss << num;
    string cadena = ss.str();
    return cadena;
}

int cantidadDeDigitosMaxima(Matrix &M) {
    uint maximo = 0;
    uint cantDigitos = 1;
    for (unsigned int i = 0; i < M.rows(); i++) {
        for (auto it = M[i].cbegin(); it != M[i].cend(); ++it) {
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
    for (int i = 0; i < cantidadMaxima + 1; i++) {
        ret = " " + ret;
    }
    return ret;
}

std::ostream &operator<<(std::ostream &o, Matrix &B) {
    int cantDigitos = cantidadDeDigitosMaxima(B);
    for (unsigned int i = 0; i < B.rows(); i++) {
        for (unsigned int j = 0; j < B.columns(); j++) {
            o << agregarEspacios(B.at(i, j), cantDigitos);
        }
        o << "\n";
    }
    return o;
}

void mostrar_matriz_por_consola(Matrix &m, string nombre_de_la_matriz) {
    int cantDigitos = cantidadDeDigitosMaxima(m);
    std::cout << std::endl << nombre_de_la_matriz << " =  |";
    for (uint i = 0; i < m.rows() * m.columns(); ++i) {
        std::cout << agregarEspacios(m.at(i / m.columns(), i % m.columns()), cantDigitos);
        if (i % m.columns() < m.columns() - 1)
            std::cout << ",  ";
        else {
            std::cout << "|" << std::endl;
            if (i != m.rows() * m.columns() - 1) {
                string espacios = "";
                for (uint i = 0; i < nombre_de_la_matriz.size(); ++i) espacios += " ";
                std::cout << espacios << "    |";
            }
        }
    }
}

void mostrar_vector_por_consola(vector<double> &v, string nombre_del_vector) {
    std::cout << std::endl << nombre_del_vector << " = [";
    for (uint i = 0; i < v.size() - 1; ++i) std::cout << v[i] << ", ";
    if (!v.empty()) std::cout << v[v.size() - 1] << "]";
}

Matrix vector2matrix(vector<double> &v, uint cant_filas) {
    if (v.size() % cant_filas == 0) {
        uint cant_columnas = v.size() / cant_filas;
        Matrix Res(cant_filas, cant_columnas);
        for (uint i = 0; i < v.size(); ++i) Res.asign(i / cant_columnas, i % cant_columnas, v[i]);
        return Res;
    }
    return Matrix();
}

pair<vector<double>, short> Matrix::GaussianElimination(vector<double> bb) {
    vector<double> res(width, 0);
    short status = 0; //status default, el sistema tiene una unica solucion posible
    double A_jj, A_ij;
    Matrix copy = *this;
    for (unsigned int j = 0; j < copy.columns() -
                                 1; ++j) { //itero sobre las columnas de copy (que son las filas de copyT), excepto la ultima porque ahi no tengo que hacer nada
        unsigned int i = j; //i: indice de la fila.
        map<uint, double>::iterator it_j = copy[i].begin();
        while (i < copy.rows() && (it_j == copy[i].end() || it_j->first !=
                                                            j))    //Mientras el 1° elemento no nulo de la fila i no está en la columna j...
            it_j = copy[++i].begin();     //avanzo a la siguiente fila.
        if (i < copy.rows()) {   //Si encontre una fila con elemento no nulo en la columna j...
            copy[j].swap(copy[i]);  //Cambio de lugar las filas (para que no haya un 0 en la diagonal).
            swap(bb[j], bb[i]);     //En consecuencia debo cambiar también el orden de bb.
            A_jj = it_j->second;    //Debido al swap, it_j es iterador de la fila j.
            ++i;
            while (i < copy.rows()) {    //Reviso las siguientes filas.
                map<uint, double>::iterator it1 = copy[i].begin();
                map<uint, double>::iterator fin1 = copy[i].end();
                if (it1 != fin1 && it1->first == j) {  //Si el elemento en la columna j no es nulo, resto filas.
                    A_ij = it1->second;
                    map<uint, double>::iterator it2 = it_j;
                    ++it2;  //Voy a la siguiente columna relevante de la fila j.
                    map<uint, double>::iterator fin2 = copy[j].end();
                    copy[i].erase(
                            it1++);     //El elemento en la columna j debe quedar en 0. Voy a la siguiente columna relevante de la fila i (con it1).
                    while (it2 != fin2) {  //Mientras no haya acabado la fila para restar:
                        double resultado_de_la_resta =
                                -(A_ij / A_jj) * (it2->second); //empiezo restando lo que hay que restar
                        while (it1 != fin1 && it1->first < it2->first) ++it1;
                        if (it1 == fin1 || it1->first > it2->first) {
                            if (abs(resultado_de_la_resta) > tolerance)
                                copy[i].insert(it1, make_pair(it2->first, resultado_de_la_resta));
                        } else {
                            it1->second += resultado_de_la_resta;
                            if (abs(it1->second) < tolerance) {
                                copy[i].erase(it1++);
                            } else
                                ++it1;
                        }
                        ++it2;
                    }
                    bb[i] -= (A_ij / A_jj) * bb[j]; //no me olvido de actualizar el vector b
                }
                ++i;
            }
        }
/*        while(it->first != j && it != copy[j].end()){ //cálculo del paso i si corresponde
			i = it2->first;
			//if (abs(A_kk) <= 0.00001){break;} //si me tengo que saltear este paso no calculo nada
			//if(it2 != copy[j].end() && it2->first == i){//si el elemento j,i es 0 no hago nada en la fila j
			A_ij = it2->second;
			map<unsigned int, double>::const_iterator it1 = copy[j].find(j);
			while(it1 != copy[j].end()){
				l = it1->first;
				if(i!=l){
					copy.asignar(i,l,copy.at(i,l)-(it1->second*A_ij/A_jj));
					copyT.asignar(l,i,copy.at(i,l));
				}
*//*
                double escalar = A_ij/A_jj;
                if(escalar != 0){   //Si el escalar es 0 no hago nada.
                    auto it1_2 = copy[i].begin();
                    auto fin1 = copy[i].end();
                    auto it2_2 = copy[j].begin();
                    auto fin2 = copy[j].end();
                    while (it2_2 != fin2) {  //Mientras no haya acabado la fila para restar:
                        double resultado_de_la_resta = -escalar * (it2_2->second); //empiezo restando lo que hay que restar
                        while (it1_2 != fin1 && it1_2->first < it2_2->first) ++it1_2;
                        if (it1_2->first == it2_2->first) resultado_de_la_resta += it1_2->second; //Si hay algo distinto de 0 en la coordenada a modificar, lo sumo.
                        if (abs(resultado_de_la_resta) > 0.000001) copy[i][it2_2->first] = resultado_de_la_resta;    //Si el resultado de la resta no es 0, lo defino en el diccionario/fila.
                        else copy[i].erase(it2_2); //Si es 0, lo borro del diccionario/fila.
                        ++it2;
                    }
                }
*//*
				it1++;
			}
			bb[i] -= A_ij/A_jj*bb[j]; //no me olvido de actualizar el vector b
			it2++;
			//} //A_jk y A_kk son los valores que determinan a las matrices Mk que uso para llegar desde A a U, sabiendo que PA = LU
		}*/
        /*if(cont){
            copy = Mk*copy;
            for(j = i + 1; j < copy.rows(); j++){ //revierto la matriz Mk a I
                Mk.asignar(j,i,0.0);
            }
            cont = false;
        }*/
    }
    for (long int i = copy.rows() - 1; i >= 0; --i) {
        auto it = copy[i].begin();
        A_jj = ((it == copy[i].end() || it->first != i) ? 0 : it->second);
        if (A_jj != 0) ++it;  //Si A_jj no es 0 avanzo "it", pués no forma parte de la siguiente resta.
        while (it != copy[i].end()) {
            bb[i] -= (it->second) * res[it->first];   //b_i - sum_j(A_ij*x_j)
            ++it;
        }
        if (A_jj == 0 && bb[i] != 0) {
            status = -1; //el sistema es incompatible
            break;
        } else if (A_jj == 0 && bb[i] == 0) {
            status = 1; //hay infinitos resultados
            res[i] = 0;
        } else
            res[i] = bb[i] / A_jj;
    }
    return make_pair(res, status);
}
