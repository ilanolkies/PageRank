#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "El programa debe cumplir el siguiente formato: ./tp1 archivo p" << std::endl;
        return 1;
    }

    // Execution parameters
    string input_file = argv[1];
    float p = atof(argv[2]);

    // Read input file
    ifstream file(input_file);


    if (!file.is_open()) {
        cout << "No ha sido posible leer el archivo " << input_file << "\n";
        return 1;
    }

    string line;

    getline(file, line);
    int n = stoi(line);

    getline(file, line);
    int m = stoi(line);

    while (getline(file, line))
        cout << line;

    file.close();

    return 0;
}
