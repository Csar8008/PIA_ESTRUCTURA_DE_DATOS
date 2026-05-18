#include <stdio.h>
#include <windows.h>
#include "grafo.h"
#include "dijkstra.h"
#include "utils.h"

int main()
{

    Grafo *vuelos = importarGrafo(); // crear el grafo a partir del archivo

    if (vuelos == NULL)
    { // validar que el grafo exista
        printf("Error al cargar el grafo\n");
        return 1;
    }

    int opcion, origen, destino, tipo;

    do
    {

        printf("\n=================================\n");
        printf("   SISTEMA DE RUTAS DE VUELOS\n");
        printf("=================================\n");

        printf("\n1. Mostrar matriz de vuelos\n");
        printf("2. Calcular rutas\n");
        printf("0. Salir\n");

        printf("\nOpcion: ");
        scanf("%d", &opcion);
        opcion = solicitarEntero(0,2);

        switch (opcion)
        {

        case 1:
            imprimirMatriz(vuelos);
            break;

        case 2:

            printf("\nCiudades disponibles:\n");

            for (int i = 0; i < vuelos->vertices; i++)
            { // muestra los destinos
                printf("%d. %s\n", i, vuelos->etiquetas[i]);
            }

            printf("\nOrigen: ");
            origen = solicitarEntero(0, (vuelos->vertices) - 1);

            printf("Destino: ");
            destino = solicitarEntero(0, (vuelos->vertices) - 1);

            printf("\n1. Mostrando todos los caminos posibles\n"); // muestra los caminos
            mostrarTodosLosCaminos(vuelos, origen, destino);
            printf("\nCriterio de optimizacion:\n");
            printf("1. Menor tiempo\n");
            printf("2. Menor costo\n");
            printf("Opcion: "); // muestra el mejor camino en base a las necesidades del usuario
            tipo = solicitarEntero(1, 2);
            dijkstra(vuelos, origen, destino, tipo);

            break;

        case 0:
            printf("\nSaliendo...\n");
            Sleep(3000);
            break;

        default:
            printf("\nOpcion invalida\n");
        }
    } while (opcion != 0);

    liberarGrafo(vuelos); // libera espacio del grafo

    return 0;
}