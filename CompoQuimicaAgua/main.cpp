#include <iostream>
#include <fstream>
#include <string>
#include "Agua.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <filename.cafe>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    if (filename.length() <= 5 || filename.substr(filename.length() - 5) != ".cafe") {
        std::cerr << "Error: El archivo debe tener la extensión .cafe" << std::endl;
        return 1;
    }

    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return 1;
    }

    agua aguaDeCafe;
    inputFile >> aguaDeCafe;
    inputFile.close();

    aguaDeCafe.calcular();

    std::ofstream outputFile("ingredientes");
    if (!outputFile) {
        std::cerr << "Error al crear el archivo de salida 'ingredientes'" << std::endl;
        return 1;
    }

    outputFile << aguaDeCafe;
    outputFile.close();

    std::cout << "Los ingredientes se han calculado y guardado en el archivo 'ingredientes'." << std::endl;

    return 0;
}
