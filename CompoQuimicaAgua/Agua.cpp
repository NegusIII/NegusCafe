#include "Agua.h"
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

// Constructores
agua::agua() : Vol(1.0), compo({0,0,0,0,0,0,0}), tipoCafe(America), ing({0,0}) {}

agua::agua(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::invalid_argument("No se pudo abrir el archivo.");
    }
    file >> *this;
}

// Sobrecarga de operadores
std::istream& operator>>(std::istream& is, agua& a) {
    std::string line;
    while (std::getline(is, line)) {
        std::stringstream ss(line);
        std::string key;
        char colon = '\0';
        ss >> key;

        // Check for colon and remove it
        if (!key.empty() && key.back() == ':') {
            key.pop_back();
        } else {
             // If no colon, try to read it separately, might be space-separated
            ss >> colon;
             if (colon != ':') {
                // If it wasn't a colon, put it back in the stream if it's not a space
                if(colon != '\0') ss.putback(colon);
             }
        }


        if (key == "tipo") {
            std::string val;
            ss >> val;
            if (val == "AM") a.tipoCafe = agua::America;
            else if (val == "AF") a.tipoCafe = agua::Africa;
            else if (val == "AS") a.tipoCafe = agua::Asia;
        } else if (key == "vol") {
            ss >> a.Vol;
        } else if (key == "residuo") {
            ss >> a.compo.residuo;
        } else if (key == "bicarbonatos") {
            ss >> a.compo.bicarbonatos;
        } else if (key == "cloruros") {
            ss >> a.compo.cloruros;
        } else if (key == "ca") {
            ss >> a.compo.ca;
        } else if (key == "mg") {
            ss >> a.compo.mg;
        } else if (key == "na") {
            ss >> a.compo.na;
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
            objetivo.residuo = 80;
            objetivo.bicarbonatos = 30;
            objetivo.cloruros = 15;
            objetivo.ca = 8;
            objetivo.mg = 15;
            objetivo.na = 15;
            break;
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
            break;
    }

    // Cálculos. Empezamos calculando los mg/L de cada uno de los elementos. Luego se multiplica por el volumen

    this->ing.bicarbonato_sodio = (objetivo.bicarbonatos - compo.bicarbonatos)*10.14;
    this->ing.sulfato_magnesio = (objetivo.mg - compo.mg)*1.38;
}
