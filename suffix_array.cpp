#include "suffix_array.h"
#include <algorithm>
#include <string>
#include <vector>
#include <string_view>
#include <iostream>

// Función para calcular el uso de memoria del Suffix Array
size_t calcularMemoria(const std::vector<int> &sa)
{
    return sizeof(int) * sa.size();
}
// Construcción del Suffix Array
std::vector<int> construirSuffixArray(const std::string &texto)
{
    int n = texto.size();
    std::vector<int> sa(n), rank(n), temp_rank(n);

    // Inicializa el suffix array y los rangos
    for (int i = 0; i < n; ++i)
    {
        sa[i] = i;
        rank[i] = texto[i];
    }

    for (int k = 1; k < n; k *= 2)
    {
        auto cmp = [&](int i, int j)
        {
            if (rank[i] != rank[j])
                return rank[i] < rank[j];
            int ri = (i + k < n) ? rank[i + k] : -1;
            int rj = (j + k < n) ? rank[j + k] : -1;
            return ri < rj;
        };
        std::sort(sa.begin(), sa.end(), cmp);

        temp_rank[sa[0]] = 0;
        for (int i = 1; i < n; ++i)
        {
            temp_rank[sa[i]] = temp_rank[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        rank = temp_rank;
    }

    return sa;
}

// Búsqueda binaria de patrón en el texto usando Suffix Array
std::vector<int> buscarPatronSA(const std::string &texto, const std::string &patron, const std::vector<int> &sa)
{
    std::vector<int> ocurrencias;
    int n = texto.size();
    int m = patron.size();

    // Verifica que el patrón no sea más largo que el texto
    if (m > n)
        return ocurrencias;

    // Búsqueda binaria para encontrar la primera ocurrencia
    int l = 0, r = n - 1;
    int first = -1;
    std::string_view texto_view(texto);
    std::string_view patron_view(patron);

    while (l <= r)
    {
        int mid = (l + r) / 2;
        std::string_view suf = texto_view.substr(sa[mid], m);

        int cmp = suf.compare(patron_view);

        if (cmp == 0)
        {
            first = mid;
            r = mid - 1; // Continuamos buscando hacia la izquierda para la primera ocurrencia
        }
        else if (cmp < 0)
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }

    if (first == -1)
        return ocurrencias; // No se encontró el patrón

    // Buscar todas las ocurrencias consecutivas hacia la derecha
    for (int i = first; i < n && texto_view.substr(sa[i], m) == patron_view; ++i)
    {
        ocurrencias.push_back(sa[i]);
    }

    return ocurrencias;
}
