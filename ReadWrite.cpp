#include "ReadWrite.h"

Matrix matrixFromFile(string input_file) {
    fstream input(input_file, ios_base::in);

    int paginas, links;
    input >> paginas >> links;

    Matrix matrix(paginas, paginas);

    int i, j;

    for (int k = 0; k < links; k++) {
        input >> i >> j;
        matrix.asign(j - 1, i - 1, 1);
    }

    input.close();

    return matrix;
}

void escribirRanking(string nombreArchivo, vector<double> ranking, double probabilidadDeSaltar) {
    ofstream salida(nombreArchivo, ios_base::out);

    salida << probabilidadDeSaltar << '\n';

    for (vector<double>::iterator it = ranking.begin(); it != ranking.end(); ++it)
        salida << *it << '\n';

    salida.close();
}

void listarDirectorio(const string& directorio, vector<string>& v) {
    string nomArch;
    DIR* dirp = opendir(directorio.c_str());
    struct dirent * dp;
    if (dirp == NULL) {
        throw runtime_error("no se encontro directorio " + directorio + "!");
    }
    while ((dp = readdir(dirp)) != NULL) {
        string nomArch = dp->d_name;
        if (nomArch.compare(".") != 0 && nomArch.compare("..") != 0)
            v.push_back(directorio + "/" + nomArch);
    }
    closedir(dirp);
}

void escribirVector(string nombreArchivo, vector<unsigned long> &vector) {
    ofstream salida(nombreArchivo, ios_base::out);
    for (auto it = vector.begin() ; it != vector.end(); ++it) {
        string clase_str = "";
        clase_str += to_string(*it) + "\t";
        salida << clase_str << endl;
    }
    salida.close();
}