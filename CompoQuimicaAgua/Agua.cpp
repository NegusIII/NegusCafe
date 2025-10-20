#include "Agua.h"
#include <fstream>
#include <string>
#include <sstream>

std::istream& operator>>(std::istream& is, agua& a) {
    std::string line;
    while (std::getline(is, line)) {
        std::stringstream ss(line);
        std::string key;
        char colon;
        ss >> key;
        // Remove trailing colon if present
        if (!key.empty() && key.back() == ':') {
            key.pop_back();
        } else {
            // If there's no colon after the key, maybe it's separated by a space
            ss >> colon;
        }

        if (key == "type") {
            std::string val;
            ss >> val;
            if (val == "AM") a.tipoCafe = agua::America;
            else if (val == "AF") a.tipoCafe = agua::Africa;
            else if (val == "AS") a.tipoCafe = agua::Asia;
        } else if (key == "vol") {
            ss >> a.Vol;
        } else if (key == "rs") {
            ss >> a.compo.residuo;
        } else if (key == "bc") {
            ss >> a.compo.bicarbonatos;
        } else if (key == "cl") {
            ss >> a.compo.cloruros;
        } else if (key == "ca") {
            ss >> a.compo.ca;
        } else if (key == "mg") {
            ss >> a.compo.mg;
        } else if (key == "na") {
            ss >> a.compo.na;
        } else if (key == "s") {
            ss >> a.compo.s;
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const agua& a) {
    os << "Ingredientes a añadir:" << std::endl;
    os << "  Bicarbonato de Sodio: " << a.ing.bicarbonato_sodio << " mg" << std::endl;
    os << "  Sulfato de Magnesio: " << a.ing.sulfato_magnesio << " mg" << std::endl;
    return os;
}
