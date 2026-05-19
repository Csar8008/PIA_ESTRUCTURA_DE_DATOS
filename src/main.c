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

    int i, opcion, origen, destino, tipo, opcionEditar, tiempo;
    double costo;
    char ciudad[30];

    do
    {

        printf("\n=================================\n");
        printf("   SISTEMA DE RUTAS DE VUELOS\n");
        printf("=================================\n");

        printf("\n1. Mostrar matriz de vuelos\n");
        printf("2. Calcular rutas\n");
        printf("3. Modificar matriz de adyacencia\n");
        printf("0. Salir\n");

        printf("\nOpcion: ");
        opcion = solicitarEntero(0, 3);

        switch (opcion)
        {

        case 1:
            imprimirMatriz(vuelos);
            break;

        case 2:

            printf("\nCiudades disponibles:\n");

            for (i = 0; i < vuelos->vertices; i++)
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

        case 3:
            printf("\nQue accion desea realizar?\n");
            printf("1. Modificar o agregar los valores de una ruta\n");
            printf("2. Eliminar una ruta entre ciudades\n");
            printf("3. Agregar una ciudad a la matriz\n");
            printf("4. Eliminar una ciudad de la matriz\n");
            printf("0. Salir\n");
            printf("\nOpcion: ");
            opcionEditar = solicitarEntero(0, 4);

            if (opcionEditar == 1 || opcionEditar == 2)
            {
                printf("\nCiudades disponibles:\n");
                for (i = 0; i < vuelos->vertices; i++)
                {
                    printf("%d. %s\n", i, vuelos->etiquetas[i]);
                }
                printf("\nOrigen: ");
                int orig = solicitarEntero(0, vuelos->vertices - 1);
                printf("Destino: ");
                int dest = solicitarEntero(0, vuelos->vertices - 1);

                if (orig == dest)
                {
                    printf("\nError. El origen y destino no pueden ser el mismo.\n");
                }
                else if (opcionEditar == 1)
                {
                    printf("Ingrese el nuevo tiempo (en minutos): ");
                    tiempo = solicitarEntero(1, 9999);
                    printf("Ingrese el nuevo costo: ");
                    costo = solicitarFlotante(0.1, 99999.0);
                    modificarRuta(vuelos, orig, dest, tiempo, costo);
                }
                else
                {
                    eliminarRuta(vuelos, orig, dest);
                }
            }
            else if (opcionEditar == 3)
            {
                printf("\nIngrese el nombre de la nueva ciudad: ");
                fflush(stdin);
                fgets(ciudad, 30, stdin);
                ciudad[strcspn(ciudad, "\n")] = 0; 
                agregarCiudad(vuelos, ciudad);
            }
            else if (opcionEditar == 4)
            {
                printf("\nCiudades disponibles:\n");
                for (i = 0; i < vuelos->vertices; i++)
                {
                    printf("%d. %s\n", i, vuelos->etiquetas[i]);
                }
                printf("\nIndique el numero de la ciudad a eliminar: ");
                origen = solicitarEntero(0, vuelos->vertices - 1);
                eliminarCiudad(vuelos, origen);
            }
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