#include "kmp.h"
#include <iostream>
#include <vector>
#include <string_view>

std::vector<int> kmpSearch(const std::string &texto, const std::string &patron)
{
    std::vector<int> resultados;
    int m = patron.size();
    int n = texto.size();

    if (m == 0 || n == 0 || m > n)
        return resultados;

    std::vector<int> lps(m, 0); // Longest Prefix Suffix
    int j = 0;

    // Preprocesamiento del patrón para crear la tabla LPS
    for (int i = 1; i < m; i++)
    {
        while (j > 0 && patron[i] != patron[j])
        {
            j = lps[j - 1];
        }
        if (patron[i] == patron[j])
        {
            j++;
        }
        lps[i] = j;
    }

    j = 0;
    for (int i = 0; i < n; i++)
    {
        while (j > 0 && texto[i] != patron[j])
        {
            j = lps[j - 1];
        }

        if (texto[i] == patron[j])
        {
            j++;
        }

        if (j == m)
        {
            resultados.push_back(i - m + 1);
            j = lps[j - 1];
        }
    }

    return resultados;
}
