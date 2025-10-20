#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "Agua.h"

using namespace std;

/*EJECUTAR:
cmake-build-debug/CompoQuimicaAgua /home/ed/Escritorio/cafe/aguas/agua.cafe && cp ingredientes /home/ed/Escritorio/cafe/aguas/
*/

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <filename.cafe>" << endl;
        return 1;
    }

    string filename = argv[1];
    if (filename.length() <= 5 || filename.substr(filename.length() - 5) != ".cafe") {
        cerr << "Error: El archivo debe tener la extensión .cafe" << endl;
        return 1;
    }

    agua _agua(filename);
    _agua.calcular();

    ofstream outputFile("ingredientes");
    if (!outputFile) {
        cerr << "Error al crear el archivo de salida" << endl;
        return 1;
    }

    outputFile << _agua;
    outputFile.close();

    cout << "Ingredientes calculados." << endl;

    return 0;
}
