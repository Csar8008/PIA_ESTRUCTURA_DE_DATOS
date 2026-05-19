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
        system("pause");
        return 1;
    }

    int i, opcion, origen, destino, tipo, opcionEditar, tiempo;
    double costo;
    char ciudad[30];

    do
    {

        printf("\n\033[1;36m==========================================\n");
        printf("         SISTEMA DE RUTAS DE VUELOS    ");
        printf("\n==========================================\033[0m\n");

        printf("\n  1]. Mostrar tabla de vuelos disponibles\n");
        printf("  2]. Calcular rutas                     \n");
        printf("  3]. Ajustes     \n");
        printf("  4]. Historial de rutas                 \n");
        printf("  0]. Salir           \033[0m                   \n");
        printf("\n\033[1;36m==========================================\n");
        printf("\nOpcion: ");
        printf("\033[1;36m");
        opcion = solicitarEntero(0, 4);
        printf("\033[0m");
        switch (opcion)
        {

        case 1:
            system("cls");
            mostrarVuelos(vuelos);
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            printf("\033[1;32m=====================================\n");
            printf("          CALCULAR RUTAS\n");
            printf("=====================================\033[0m\n");
            printf("\nCiudades disponibles:\n");

            for (i = 0; i < vuelos->vertices; i++)
            { // muestra los destinos
                printf("%d. %s\n", i, vuelos->etiquetas[i]);
            }

            printf("\n\033[1;32mSELECCIONE LA CIUDAD DE ORIGEN:\033[0m ");
            origen = solicitarEntero(0, (vuelos->vertices) - 1);

            printf("\033[1;32mSELECCIONE LA CIUDAD DESTINO\033[0m: ");
            destino = solicitarEntero(0, (vuelos->vertices) - 1);

            system("cls");
            mostrarTodosLosCaminos(vuelos, origen, destino);
            system("pause");
            system("cls");
            printf("\nRECURSO A OPTIMIZAR EN EL VIAJE:\n");
            printf("  1] Menor tiempo\n");
            printf("  2] Menor costo\n");
            printf("  0] Cancelar\n");
            printf("Opcion: "); // muestra el mejor camino en base a las necesidades del usuario
            tipo = solicitarEntero(0, 2);
            if(tipo == 0){
                system("cls");
                break;
            }
            system("cls");
            dijkstra(vuelos, origen, destino, tipo);
            system("pause");
            system("cls");
            break;

        case 3:
            system("cls");
            printf("\nQue accion desea realizar?\n");
            printf("1. Modificar o agregar los valores de una ruta\n");
            printf("2. Eliminar una ruta entre ciudades\n");
            printf("3. Agregar una ciudad a la matriz\n");
            printf("4. Eliminar una ciudad de la matriz\n");
            printf("5. Ver matriz de vuelos\n");
            printf("0. Salir\n");
            printf("\nOpcion: ");
            opcionEditar = solicitarEntero(0, 5);
            system("cls");
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
            else if(opcionEditar == 5)
            {
                system("cls");
                imprimirMatriz(vuelos);
                system("pause");
                system("cls");
                break;
            }
            system("cls");
            break; 
        case 4:
                mostrarHistorial();
                break;
        case 0:
            system("cls");
            printf("\nSaliendo...\n");
            Sleep(3000);
            break;
        }
    } while (opcion != 0);

    liberarGrafo(vuelos); // libera espacio del grafo

    return 0;
}