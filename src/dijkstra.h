#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "grafo.h"

// Devuelve el índice del nodo con menor distancia no visitado
int obtenerMinimo(double *distancias, int *visitados, int vertices);

// Imprime la ruta reconstruida desde el arreglo de anteriores
void imprimirRuta(int *anteriores, int actual, Grafo *grafo);

// Algoritmo de Dijkstra
// criterio = 1 -> tiempo
// criterio = 2 -> costo
void dijkstra(Grafo *grafo, int origen, int destino, int criterio);

void mostrarTodosLosCaminos(Grafo *g, int origen, int destino);

void eliminarCiudad(Grafo *grafoEliminar, int indice);

void guardarHistorial(Grafo *grafo,int origen,int destino,double costo,double tiempo);

void mostrarHistorial();

void mostrarVuelos(Grafo *grafo);


#endif