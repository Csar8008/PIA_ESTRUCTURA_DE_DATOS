#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>

struct peso
{                    // estructura que de pesos del grafo
    int tiempoVuelo; // El tiempo se almacena como minutos, pero se muestra como horas, procurar utilizar (double) (grafo->matriz[i][j].tiempoVuelo / 60.0) para mostrar el tiempo
    double costoVuelo;
};

typedef struct peso Peso;

// Doble puntero de peso para almacenar la matriz bidimensional dinamica
// Doble puntero de etiquetas para almacenar el arreglo de cadenas dinamicas
// Vertices almacena la cantidad de vertices del grafo
struct grafo
{
    Peso **matriz;
    char **etiquetas;
    int vertices;
};

typedef struct grafo Grafo;

int validarFormatoArchivo(FILE *archivo);

Grafo *inicializarGrafo(int tam);

void liberarGrafo(Grafo *grafoEliminar);

void imprimirMatriz(Grafo *grafo);

Grafo *importarGrafo();

#endif