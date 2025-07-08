===========================================
PROYECTO: Detección de Patrones en Archivos
===========================================

REQUISITOS:
-----------
- Tener instalado g++ (MinGW en Windows)
- Librería json.hpp incluida en /include (ya está en este proyecto)

CARPETAS IMPORTANTES:
----------------------
- /data          → contiene las subcarpetas de documentos, el texto concatenado y el JSON
- /include       → contiene json.hpp
- /resultados    → se guardan los archivos .csv con resultados
- /.vscode       → configuración de compilación automática en VSCode

ARCHIVOS CLAVE:
---------------
- concatenar.cpp       → Une todos los archivos en un solo texto y genera documentos.json
- main.cpp             → Permite ejecutar búsquedas con distintos algoritmos y mide rendimiento
- rabin_karp.cpp/.h    → Algoritmo de búsqueda Rabin-Karp
- kmp.cpp/.h           → Algoritmo de búsqueda Knuth-Morris-Pratt
- boyer_moore.cpp/.h   → Algoritmo de búsqueda Boyer-Moore
- suffix_array.cpp/.h  → Búsqueda con estructura de datos Suffix Array
- json.hpp             → Librería para manejo de JSON

--------------------------------------------------------
🚀 USO DEL PROYECTO (paso a paso desde consola o terminal)
--------------------------------------------------------

1.  COMPILAR EL PROYECTO
-------------------------
Desde consola:
> g++ -O3 main.cpp rabin_karp.cpp kmp.cpp boyer_moore.cpp suffix_array.cpp -Iinclude -o programa.exe

Desde VSCode:
> Ctrl + Shift + B (requiere tasks.json)

2.  GENERAR TEXTO CONCATENADO Y JSON
-------------------------------------
> g++ concatenar.cpp -std=c++17 -Iinclude -o concatenar.exe
> ./concatenar.exe

Esto crea:
- data/texto_concatenado.txt
- data/documentos.json

📌 Solo debes ejecutar esto una vez, o cuando cambies los archivos en /data

3.  EJECUTAR BÚSQUEDA
----------------------
> ./programa.exe

Se te pedirá:
- El patrón a buscar (puede ser cualquier palabra o fragmento)
- El algoritmo a usar:
  1. Rabin-Karp
  2. KMP (Knuth-Morris-Pratt)
  3. Boyer-Moore
  4. Suffix Array (estructura de datos)

El programa mostrará:
- Tiempo promedio de ejecución (20 repeticiones)
- Ocurrencias encontradas
- Documento en el que aparece cada una
- La cantidad de memoria que ocupa

Y guardará en:
- resultados/rendimiento_busquedas.csv el rendimiento correspondiente a cada algoritmo
- resultados/uso_memoria.csv el uso de memoria correspondiente a cada algoritmo

Ejemplo de línea en el CSV de rendimiento:
patrón, algoritmo, tiempo en milisegundos, cantidad de concurrencias
datos,KMP,253402,5

Ejemplo de línea en el CSV de memoria:

patrón, algoritmo, bytes que ocupa en memoria
logica ,Suffix Array,20819472


Integrantes:
Nicolás Ricciardi R. 
José Alarcón A. 
Gabriel Garrido Baeza 

