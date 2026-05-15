#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo.h"

#define INFINITO 9999999

int main() {
    Grafo *vuelos = importarGrafo();

    if (vuelos != NULL) {
        imprimirMatriz(vuelos);
        liberarGrafo(vuelos);
        system("pause");
    }

    return 0;
}



