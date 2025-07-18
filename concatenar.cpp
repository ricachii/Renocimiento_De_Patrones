#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

struct Documento
{
    std::string nombre;
    size_t inicio;
    size_t fin;
};

// Función para eliminar espacios en blanco de una cadena
std::string eliminarEspacios(const std::string &str) {
    std::string result;
    std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                 [](char c) { return !std::isspace(static_cast<unsigned char>(c)); });
    return result;
}

int main()
{
    std::string carpeta = "data/";
    std::ofstream salida("data/texto_concatenado.txt");
    json j;
    j["documentos"] = json::array();

    size_t offset = 0;
    int contador_archivos = 0;

    for (const auto &entry : fs::recursive_directory_iterator(carpeta))
    {
        // Omite texto_concatenado.txt y documentos.json
        if (entry.path().filename() == "texto_concatenado.txt" || entry.path().filename() == "documentos.json")
        {
            continue;
        }

        if (fs::is_regular_file(entry.path()))
        {
            std::ifstream entrada(entry.path(), std::ios::binary);
            std::string contenido((std::istreambuf_iterator<char>(entrada)), std::istreambuf_iterator<char>());

            std::string contenido_sin_espacios = eliminarEspacios(contenido);
            
            salida << contenido_sin_espacios << "$";
            size_t nuevo_offset = offset + contenido_sin_espacios.size();

            j["documentos"].push_back({{"nombre", entry.path().filename().string()},
                                       {"inicio", offset},
                                       {"fin", nuevo_offset}});

            std::cout << "📄 Concatenado: " << entry.path() << std::endl;

            offset = nuevo_offset + 1;
            contador_archivos++;
        }
    }

    salida.close();

    std::ofstream json_out("data/documentos.json");
    json_out << j.dump(4); // indentado bonito
    json_out.close();

    std::cout << "✅ Concatenación y generación de JSON completa.\n";
    std::cout << "📦 Total de archivos concatenados: " << contador_archivos << std::endl;

    return 0;
}
