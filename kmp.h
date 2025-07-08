#pragma once
#include <vector>
#include <string>

// Busca todas las ocurrencias de 'patron' en 'texto' usando el algoritmo KMP
// Retorna un vector con las posiciones donde se encontró el patrón
std::vector<int> kmpSearch(const std::string &texto, const std::string &patron);
