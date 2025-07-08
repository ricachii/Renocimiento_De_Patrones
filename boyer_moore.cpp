#include "boyer_moore.h"
#include <unordered_map>
#include <iostream>

std::vector<int> boyerMooreSearch(const std::string &texto, const std::string &patron)
{
    std::vector<int> resultados;
    int n = texto.size();
    int m = patron.size();

    if (m == 0 || n < m)
        return resultados;

    std::unordered_map<char, int> badCharShift;
    for (int i = 0; i < m; ++i)
    {
        badCharShift[patron[i]] = i;
    }

    int i = 0;
    while (i <= n - m)
    {
        int j = m - 1;

        while (j >= 0 && patron[j] == texto[i + j])
            --j;

        if (j < 0)
        {
            resultados.push_back(i);
            i += (i + m < n) ? m - badCharShift[texto[i + m]] : 1;
        }
        else
        {
            char mismatched = texto[i + j];
            int shift = j - (badCharShift.count(mismatched) ? badCharShift[mismatched] : -1);
            i += std::max(1, shift);
        }
    }

    return resultados;
}
