#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include "rabin_karp.h"
#include "kmp.h"
#include "boyer_moore.h"
#include "suffix_array.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std::chrono;

std::string obtenerDocumento(int posicion, const std::string &rutaJson)
{
    std::ifstream file(rutaJson);
    json j;
    file >> j;

    for (const auto &doc : j["documentos"])
    {
        int inicio = doc["inicio"];
        int fin = doc["fin"];
        if (posicion >= inicio && posicion <= fin)
        {
            return doc["nombre"];
        }
    }

    return "No encontrado";
}

int main()
{
    std::ifstream archivo("data/texto_concatenado.txt");
    std::string texto((std::istreambuf_iterator<char>(archivo)), std::istreambuf_iterator<char>());

    std::string patron;
    std::cout << "Ingresa el patron a buscar: ";
    std::getline(std::cin, patron);

    int opcion;
    std::cout << "\n¿Qué algoritmo quieres usar?\n";
    std::cout << "1. Rabin-Karp\n";
    std::cout << "2. Knuth-Morris-Pratt (KMP)\n";
    std::cout << "3. Boyer-Moore\n";
    std::cout << "4. Suffix Array (estructura de datos)\n";
    std::cout << "Opcion: ";
    std::cin >> opcion;

    std::vector<int> resultados;
    long long suma_tiempos = 0;
    std::vector<int> sa; // Para Suffix Array

    if (opcion == 4)
    {
        std::cout << "Construyendo Suffix Array...\n";
        sa = construirSuffixArray(texto);
    }

    // Bucle de 20 repeticiones para obtener el tiempo promedio
    for (int i = 0; i < 20; ++i)
    {
        auto inicio = high_resolution_clock::now();

        if (opcion == 1)
            resultados = rabinKarpSearch(texto, patron);
        else if (opcion == 2)
            resultados = kmpSearch(texto, patron);
        else if (opcion == 3)
            resultados = boyerMooreSearch(texto, patron);
        else if (opcion == 4)
            resultados = buscarPatronSA(texto, patron, sa);

        auto fin = high_resolution_clock::now();
        suma_tiempos += duration_cast<microseconds>(fin - inicio).count();
    }

    long long promedio = suma_tiempos / 20;
    std::cout << "\nTiempo promedio: " << promedio << " microsegundos\n";
    std::cout << "Ocurrencias: " << resultados.size() << "\n";

    // Mostrar los resultados
//    for (int pos : resultados)
  //  {
    //    std::string doc = obtenerDocumento(pos, "data/documentos.json");
      //  std::cout << "Posicion: " << pos << " → Documento: " << doc << "\n";
    //}

    // Medir el uso de memoria solo al final, después de completar las búsquedas
    size_t memoriaUso = 0;
    if (opcion == 1)
    {
        memoriaUso = sizeof(int) * resultados.size(); // En caso de usar Rabin-Karp
    }
    else if (opcion == 2)
    {
        memoriaUso = sizeof(int) * resultados.size(); // En caso de usar KMP
    }
    else if (opcion == 3)
    {
        memoriaUso = sizeof(int) * resultados.size(); // En caso de usar Boyer-Moore
    }
    else if (opcion == 4)
    {
        memoriaUso = sizeof(int) * sa.size(); // En caso de usar Suffix Array
    }

    // Imprimir la memoria solo una vez al final
    std::cout << "Memoria usada: " << memoriaUso << " bytes\n";

    // Guardar resultados en el CSV de rendimiento
    std::ofstream out("resultados/rendimiento_busquedas.csv", std::ios::app);
    if (out.is_open())
    {
        std::string nombre_algoritmo =
            (opcion == 1) ? "Rabin-Karp" : (opcion == 2) ? "KMP"
                                       : (opcion == 3)   ? "Boyer-Moore"
                                       : (opcion == 4)   ? "Suffix Array"
                                                         : "Desconocido";

        out << patron << "," << nombre_algoritmo << "," << promedio << "," << resultados.size() << "\n";
        out.close();
        std::cout << "Resultado guardado en resultados/rendimiento_busquedas.csv\n";
    }
    else
    {
        std::cerr << "No se pudo abrir el archivo CSV para escribir.\n";
    }

    // Guardar en el archivo de uso de memoria
    std::ofstream outMemoria("resultados/uso_memoria.csv", std::ios::app);
    if (outMemoria.is_open())
    {
        std::string nombre_algoritmo =
            (opcion == 1) ? "Rabin-Karp" : (opcion == 2) ? "KMP"
                                       : (opcion == 3)   ? "Boyer-Moore"
                                       : (opcion == 4)   ? "Suffix Array"
                                                         : "Desconocido";

        outMemoria << patron << "," << nombre_algoritmo << "," << memoriaUso << "\n";
        outMemoria.close();
        std::cout << "Memoria registrada en resultados/uso_memoria.csv\n";
    }
    else
    {
        std::cerr << "No se pudo abrir el archivo CSV para el uso de memoria.\n";
    }

    return 0;
}
