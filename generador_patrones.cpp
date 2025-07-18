#include "generador_patrones.h"
#include <algorithm>
#include <random>

std::vector<std::string> generarPatronesAleatorios(const std::string &texto,
                                     int numPatrones, int longitudMin, int longitudMax){
    std::vector<std::string> patrones;
    if (texto.empty() || numPatrones <= 0 || longitudMin <= 0 || longitudMax > texto.size())
    {
        return patrones;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distLongitud(longitudMin, longitudMax);
    std::uniform_int_distribution<> distPosicion(0, texto.size() - longitudMin);

    for (int i = 0; i < numPatrones; ++i)
    {
        int longitud = distLongitud(gen);
        int posicion = distPosicion(gen);

        // Asegurar que no exceda los límites del texto
        // Cada patrón generado es una subcadena del texto original, por lo que todos
        //sus caracteres existen en el texto.
        longitud = std::min(longitud, static_cast<int>(texto.size() - posicion));
        patrones.push_back(texto.substr(posicion, longitud));
    }

    return patrones;
}