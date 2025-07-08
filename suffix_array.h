#ifndef SUFFIX_ARRAY_H
#define SUFFIX_ARRAY_H

#include <vector>
#include <string>

std::vector<int> construirSuffixArray(const std::string &texto);
std::vector<int> buscarPatronSA(const std::string &texto, const std::string &patron, const std::vector<int> &sa);

#endif
