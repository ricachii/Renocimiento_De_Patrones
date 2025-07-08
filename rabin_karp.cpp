#include "rabin_karp.h"
#include <cmath>
#include <iostream>

const int d = 256; // Tamaño del alfabeto (ASCII)
const int q = 101; // Número primo para hashing

std::vector<int> rabinKarpSearch(const std::string &texto, const std::string &patron)
{
    std::vector<int> ocurrencias;
    int n = texto.size();
    int m = patron.size();

    if (m > n)
        return ocurrencias;

    int hash_patron = 0, hash_texto = 0;
    int d = 256; // Número de caracteres posibles (ASCII)
    int q = 101; // Un número primo para hacer la modulación
    int h = 1;

    // Calcular h = d^(m-1) % q
    for (int i = 0; i < m - 1; ++i)
        h = (h * d) % q;

    // Calcular hash del patrón y el primer bloque del texto
    for (int i = 0; i < m; ++i)
    {
        hash_patron = (d * hash_patron + patron[i]) % q;
        hash_texto = (d * hash_texto + texto[i]) % q;
    }

    // Deslizar la ventana de texto sobre el patrón
    for (int i = 0; i <= n - m; ++i)
    {
        if (hash_patron == hash_texto)
        {
            // Verificar carácter por carácter
            if (texto.substr(i, m) == patron)
                ocurrencias.push_back(i);
        }

        // Calcular el hash del siguiente bloque
        if (i < n - m)
        {
            hash_texto = (d * (hash_texto - texto[i] * h) + texto[i + m]) % q;
            if (hash_texto < 0)
                hash_texto = (hash_texto + q);
        }
    }

    return ocurrencias;
}
