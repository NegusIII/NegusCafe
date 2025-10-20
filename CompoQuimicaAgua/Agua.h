//
// Created by ed on 20/10/25.
//

#ifndef COMPOQUIMICAAGUA_AGUA_H
#define COMPOQUIMICAAGUA_AGUA_H

#include <string>
#include <iostream>


class agua {

private:

    /**
     * @brief tipo de facé para el que se quiere usar el agua.
     *
     * @details el tipo Africa está basado en el perfil de sabor de un Etiopía Yirgacheffe, el de América en un Geisha de
     * Honduras, y el de Asia en uno del sureste de China.
     */
    enum cafe {
        Africa,
        America,
        Asia
    };


    // Litros de agua que mezclar
    double Vol;

    // ppm (mg/L) de cada elemento en el agua
    struct composicion{

        double residuo;
        double bicarbonatos;
        double cloruros;
        double ca;
        double mg;
        double na;
    };

    // Ingredientes necesarios para añadir al agua
    struct ingredientes {

        double bicarbonato_sodio;
        double sulfato_magnesio;
    };

    composicion compo;
    cafe tipoCafe;
    ingredientes ing;


public:

    // Constructores de la clase agua:

    /**
     * @brief constructor por defecto
     *
     * @details construye un objeto de la clase agua con 1L de agua y 0ppm de cada elemento para un café de America
     *
     */
    agua();

    /**
     * @brief constructor dada la ficha de composición química base del agua
     *
     * @param filename nombre del archivo que contiene la información del agua
     */
    agua(const std::string &filename);


    // Métodos de la clase agua:


    /**
     *
     * @brief calcula el producto final
     *
     * @return ingredientes necesarios para conseguir la extracción óptima
     */
    ingredientes calcular();

    // Sobrecarga de operadores << y >>
    friend std::istream& operator>>(std::istream& is, agua& a);
    friend std::ostream& operator<<(std::ostream& os, const agua& a);
};

#endif //COMPOQUIMICAAGUA_AGUA_H
