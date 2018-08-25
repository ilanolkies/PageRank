#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "El programa debe cumplir el siguiente formato: ./tp1 archivo p" << std::endl;
        return 1;
    }

    return 0;
}
