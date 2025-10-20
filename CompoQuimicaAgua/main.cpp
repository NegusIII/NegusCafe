#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "Agua.h"

/*EJECUTAR:
cmake-build-debug/CompoQuimicaAgua /home/ed/Escritorio/cafe/aguas/agua.cafe && cp ingredientes /home/ed/Escritorio/cafe/aguas/
*/

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

    try {
        agua aguaDeCafe(filename);
        aguaDeCafe.calcular();

        std::ofstream outputFile("ingredientes");
        if (!outputFile) {
            std::cerr << "Error al crear el archivo de salida" << std::endl;
            return 1;
        }

        outputFile << aguaDeCafe;
        outputFile.close();

        std::cout << "Ingredientes calculados." << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
