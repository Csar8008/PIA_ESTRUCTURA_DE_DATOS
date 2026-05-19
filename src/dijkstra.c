#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "dijkstra.h"

#define INFINITO 999999999

int obtenerMinimo(double *distancias, int *visitados, int vertices)
{ // buscar el vertice no visitado con menor distancia
    double min = INFINITO;
    int indice = -1;

    for (int i = 0; i < vertices; i++)
    {
        if (!visitados[i] && distancias[i] < min)
        {
            min = distancias[i];
            indice = i;
        }
    }

    return indice;
}

void imprimirRuta(int *anteriores, int actual, Grafo *grafo)
{

    if (actual == -1)
        return;

    imprimirRuta(anteriores, anteriores[actual], grafo);

    if (anteriores[actual] != -1)
        printf(" -> ");

    printf("%s", grafo->etiquetas[actual]);
}

void dijkstra(Grafo *grafo, int origen, int destino, int criterio)
{

    int n = grafo->vertices;

    double *distancias = malloc(n * sizeof(double));
    int *visitados = calloc(n, sizeof(int));
    int *anteriores = malloc(n * sizeof(int));

    if (!distancias || !visitados || !anteriores)
    {
        printf("Error de memoria\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        distancias[i] = INFINITO;
        visitados[i] = 0;
        anteriores[i] = -1;
    }

    distancias[origen] = 0;

    for (int i = 0; i < n - 1; i++)
    {

        int u = obtenerMinimo(distancias, visitados, n);

        if (u == -1) // si no encuentra un nodo termina
            break;

        visitados[u] = 1; // marca el vertice como visitado

        for (int v = 0; v < n; v++)
        {

            if (!visitados[v] && grafo->matriz[u][v].tiempoVuelo > 0)
            { // si el nodo no ha sido visitado y el peso es mayor a 0

                double peso;

                if (criterio == 1)
                    peso = grafo->matriz[u][v].tiempoVuelo; // si el criterio es tiempo calcula el tiempo
                else
                    peso = grafo->matriz[u][v].costoVuelo; // de lo ocntrario calcula el costo

                if (distancias[u] + peso < distancias[v])
                {                                         // si la nueva ruta es mejor
                    distancias[v] = distancias[u] + peso; // actualiza distancia
                    anteriores[v] = u;                    // guarda de donde vino
                }
            }
        }
    }

    if (distancias[destino] == INFINITO)
    { // si la distancia del origen a un vertice es infinito es porque no existe ruta
        printf("\nNo existe ruta.\n");

        free(distancias);
        free(visitados);
        free(anteriores);

        return;
    }

    if (criterio == 1)
    {
        printf("\n\033[1;32m===== MEJOR RUTA (MENOR TIEMPO) =====\033[0m\n\n");
    }else if (criterio == 2)
    {
        printf("\n\033[1;32m===== MEJOR RUTA (MENOR COSTO) =====\033[0m\n\n");
    }
    
    imprimirRuta(anteriores, destino, grafo); // imprime los nodos por los que paso

    printf("\n");

    double costoTotal = 0;
    int tiempoTotal = 0;

    int actual = destino;

    while (anteriores[actual] != -1)
    { // suma mientras haya vertices anteriores

        int anterior = anteriores[actual];

        tiempoTotal += grafo->matriz[anterior][actual].tiempoVuelo; // suma el total de tiempo
        costoTotal += grafo->matriz[anterior][actual].costoVuelo;   // suma el total de costo

        actual = anterior;
    }

    printf("\nTiempo total: %.2f horas\n", tiempoTotal / 60.0);
    printf("Costo total: $%.2f\n", costoTotal);
    guardarHistorial(grafo,origen,destino,costoTotal,tiempoTotal / 60.0);
    free(distancias);
    free(visitados);
    free(anteriores);
}

// funcion para mostrar todos los caminos posibles usando recorrido por profundidad

void dfsCaminos(Grafo *g, int actual, int destino, int visitado[], int path[], int nivel, int tiempoAcum, double costoAcum)
{
    visitado[actual] = 1;
    path[nivel] = actual;
    nivel++;

    if (actual == destino)
    {

        printf("\nCamino: ");

        for (int i = 0; i < nivel; i++)
        {
            printf("%s", g->etiquetas[path[i]]);
            if (i < nivel - 1)
                printf(" -> ");
        }

        printf("\nTiempo: %.2f horas", tiempoAcum / 60.0);
        printf("\nCosto: $%.2f\n", costoAcum);
    }
    else
    {

        for (int i = 0; i < g->vertices; i++)
        {

            if (!visitado[i] &&
                g->matriz[actual][i].tiempoVuelo > 0)
            {

                dfsCaminos(g,i,destino,visitado,path,nivel,tiempoAcum + g->matriz[actual][i].tiempoVuelo,costoAcum + g->matriz[actual][i].costoVuelo);
            }
        }
    }

    visitado[actual] = 0;
}

void mostrarTodosLosCaminos(Grafo *g, int origen, int destino)
{

    int visitado[100] = {0};
    int path[100];

    printf("\n\033[1;32m==========MOSTRANDO TODAS LAS POSIBLES RUTAS PARA LLEGAR:===========\033[0m\n");

    dfsCaminos(g, origen, destino, visitado, path, 0, 0, 0.0);
}

void guardarHistorial(Grafo *grafo,int origen,int destino,double costo,double tiempo){

    FILE *archivo = fopen("src/historial.txt", "a");

    if (archivo == NULL) {
        printf("No se pudo abrir el historial\n");
        return;
    }

    fprintf(
        archivo,
        "%s -> %s | Tiempo: %.2f h | Costo: $%.2f\n",
        grafo->etiquetas[origen],
        grafo->etiquetas[destino],
        tiempo,
        costo
    );

    fclose(archivo);
}

void mostrarHistorial() {
    system("cls");
    FILE *archivo = fopen("src/historial.txt", "r");

    if (archivo == NULL) {

        printf("\nNo hay historial disponible.\n");
        return;
    }

    char linea[200];

    printf("\n\033[1;36m=========================== HISTORIAL ===========================\033[0m\n\n");

    while (fgets(linea, sizeof(linea), archivo)) {

        printf("%s\n", linea);
    }
    system("pause");
    system("cls");
    fclose(archivo);
}