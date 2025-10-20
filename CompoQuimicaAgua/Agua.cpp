#include "Agua.h"
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

// Constructores
agua::agua() : Vol(1.0), compo{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tipoCafe(America), ing{0.0, 0.0} {}

agua::agua(const std::string &filename) : agua() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::invalid_argument("No se pudo abrir el archivo.");
    }
    file >> *this;
}

// Sobrecarga de operadores
std::istream& operator>>(std::istream& is, agua& a) {
    std::string line;
    std::string key;
    std::string val_str;

    while (std::getline(is, line)) {
        std::stringstream ss(line);
        if (std::getline(ss, key, ':')) {
            std::getline(ss, val_str);

            // Trim leading/trailing whitespace from value
            size_t first = val_str.find_first_not_of(" \t\n\r");
            if (std::string::npos != first) {
                val_str = val_str.substr(first);
            }
            size_t last = val_str.find_last_not_of(" \t\n\r");
            if (std::string::npos != last) {
                val_str = val_str.substr(0, last + 1);
            }

            if (key == "type") {
                if (val_str == "AM") a.tipoCafe = agua::America;
                else if (val_str == "AF") a.tipoCafe = agua::Africa;
                else if (val_str == "AS") a.tipoCafe = agua::Asia;
            } else if (key == "vol") {
                a.Vol = std::stod(val_str);
            } else if (key == "rs") {
                a.compo.residuo = std::stod(val_str);
            } else if (key == "bc") {
                a.compo.bicarbonatos = std::stod(val_str);
            } else if (key == "cloruros") {
                a.compo.cloruros = std::stod(val_str);
            } else if (key == "ca") {
                a.compo.ca = std::stod(val_str);
            } else if (key == "mg") {
                a.compo.mg = std::stod(val_str);
            } else if (key == "na") {
                a.compo.na = std::stod(val_str);
            }
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const agua& a) {
    os << "Ingredientes a añadir:" << std::endl;
    os << "  Bicarbonato de Sodio: " << a.ing.bicarbonato_sodio << " mg/L" << std::endl;
    os << "  Sulfato de Magnesio: " << a.ing.sulfato_magnesio << " mg/L" << std::endl;
    return os;
}

// Métodos
agua::ingredientes agua::calcular() {
    composicion objetivo{};

    switch (tipoCafe) {
        case America:
        case Africa:
            objetivo.residuo = 80;
            objetivo.bicarbonatos = 30;
            objetivo.cloruros = 15;
            objetivo.ca = 8;
            objetivo.mg = 15;
            objetivo.na = 15;
            break;
        case Asia:
            objetivo.residuo = 120;
            objetivo.bicarbonatos = 50;
            objetivo.cloruros = 15;
            objetivo.ca = 15;
            objetivo.mg = 10;
            objetivo.na = 15;
            break;
        default:
            throw std::invalid_argument("Tipo de cafe no valido");
    }


    // Calculando la proporción de bicarbonatos y de sodio en el bicarbonato de sodio, y de magnesio en el sulfato
    // de magnesio se consiguen los números 1.38 y 10.14 respectivamente.

    this->ing.bicarbonato_sodio = (objetivo.bicarbonatos - compo.bicarbonatos) * 1.38 * this->Vol;
    this->ing.sulfato_magnesio = (objetivo.mg - compo.mg) * 10.14 * this->Vol;

    // si el agua ya tiene concentraciones superiores a las deseadas no se añade nada

    if(this->ing.bicarbonato_sodio < 0) this->ing.bicarbonato_sodio = 0;
    if(this->ing.sulfato_magnesio < 0) this->ing.sulfato_magnesio = 0;

    return this->ing;
}