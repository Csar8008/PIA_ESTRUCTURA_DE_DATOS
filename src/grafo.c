#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo.h"

int validarFormatoArchivo(FILE *archivo)
{
    if (archivo == NULL)
        return 0;

    int cantidad, i, j;
    char caracter;
    char buffer[50];

    if (fscanf(archivo, "%d", &cantidad) != 1 || cantidad <= 0)
        return 0;

    int tiempoValidacion;
    double costoValidacion;

    for (i = 0; i < cantidad; i++)
    {
        if (fscanf(archivo, " %c", &caracter) != 1 || caracter != '{')
            return 0;

        for (j = 0; j < cantidad; j++)
        {
            if (fscanf(archivo, " %d , %lf ", &tiempoValidacion, &costoValidacion) != 2)
                return 0;
            if (tiempoValidacion < 0 || costoValidacion < 0)
                return 0;
        }

        if (fscanf(archivo, " %c", &caracter) != 1 || caracter != '}')
            return 0;
    }

    if (fscanf(archivo, " %c", &caracter) != 1 || caracter != '[')
        return 0;

    for (i = 0; i < cantidad; i++)
    {
        if (fscanf(archivo, " %[^\n]", buffer) != 1 || buffer[0] == ']')
            return 0;
    }

    if (fscanf(archivo, " %c", &caracter) != 1 || caracter != ']')
        return 0;

    rewind(archivo);
    return 1;
}

// Reserva la memoria que se va a utilizar en el grafo, de argumentos tiene el tamaño del grafo para poder reservar tanto espacio en memoria y devuelve el puntero al grafo
Grafo *inicializarGrafo(int tam)
{
    int i, j;
    Grafo *grafoInit = (Grafo *)malloc(sizeof(Grafo));

    grafoInit->vertices = tam;

    grafoInit->etiquetas = (char **)malloc(grafoInit->vertices * sizeof(char *));
    for (i = 0; i < grafoInit->vertices; i++)
    {
        grafoInit->etiquetas[i] = (char *)malloc(30 * sizeof(char));
        sprintf(grafoInit->etiquetas[i], "");
    }

    grafoInit->matriz = (Peso **)malloc(grafoInit->vertices * sizeof(Peso *));
    for (i = 0; i < grafoInit->vertices; i++)
    {
        grafoInit->matriz[i] = (Peso *)malloc(grafoInit->vertices * sizeof(Peso));
        for (j = 0; j < grafoInit->vertices; j++)
        {
            grafoInit->matriz[i][j].tiempoVuelo = 0;
            grafoInit->matriz[i][j].costoVuelo = 0.0;
        }
    }

    return grafoInit;
}

// Libera el grafo, liberando paso por paso toda la memoria reservada
void liberarGrafo(Grafo *grafoEliminar)
{
    int i;

    for (i = 0; i < grafoEliminar->vertices; i++)
    {
        free(grafoEliminar->matriz[i]);
        free(grafoEliminar->etiquetas[i]);
    }
    free(grafoEliminar->matriz);
    free(grafoEliminar->etiquetas);
    free(grafoEliminar);
}

// Importa el grado desde el archivo, este ya esta validado desde llamar a la funcion validarFormatoArchivo, devuelve el puntero al grafo
Grafo *importarGrafo()
{
    int i, j, tam;
    char buffer[50];
    FILE *grafoArchivo = fopen("EjemploGrafoVuelos.txt", "r");
    Grafo *grafoTemp = NULL;

    if (!validarFormatoArchivo(grafoArchivo))
    {
        printf("\nError leyendo el archivo, no se asignara ningun valor\n");
        fclose(grafoArchivo);
        return NULL;
    }

    fgets(buffer, 10, grafoArchivo);
    tam = atoi(buffer);

    grafoTemp = inicializarGrafo(tam);

    grafoTemp->vertices = tam;

    for (i = 0; i < tam; i++)
    {
        fscanf(grafoArchivo, " { ");

        for (j = 0; j < tam; j++)
        {
            fscanf(grafoArchivo, " %d , %lf ", &grafoTemp->matriz[i][j].tiempoVuelo,
                   &grafoTemp->matriz[i][j].costoVuelo);
        }

        fscanf(grafoArchivo, " } ");
    }

    fscanf(grafoArchivo, " [ ");

    for (i = 0; i < tam; i++)
    {
        if (fscanf(grafoArchivo, " %[^\n]", buffer) == 1)
        {
            strcpy(grafoTemp->etiquetas[i], buffer);
        }
    }

    fclose(grafoArchivo);
    return grafoTemp;
}

// Imprime la matriz de adyacencia con sus etiquetas, en caso de que haya conexion, imprime los pares de valores, en caso contrario, imprime -
// Utiliza sprintf para guardar lo que se imprime en cada celda en una cadena para poder formatearse con facilidad
void imprimirMatriz(Grafo *grafo)
{
    if (grafo == NULL)
        return;

    int ancho = 18, i;
    char celda[50];

    printf("%-*s", ancho, "");
    for (i = 0; i < grafo->vertices; i++)
    {
        printf("| %-*.*s ", ancho - 2, ancho - 2, grafo->etiquetas[i]);
    }
    printf("|\n");

    for (i = 0; i <= grafo->vertices; i++)
    {
        for (int j = 0; j < ancho + 1; j++)
            printf("-");
    }
    printf("\n");

    for (i = 0; i < grafo->vertices; i++)
    {
        printf("%-*.*s", ancho, ancho, grafo->etiquetas[i]);

        for (int j = 0; j < grafo->vertices; j++)
        {
            if (grafo->matriz[i][j].tiempoVuelo == 0 && grafo->matriz[i][j].costoVuelo == 0.0)
            {
                sprintf(celda, "-");
            }
            else
            {
                sprintf(celda, "{%.2lf, %.1lf}",
                        (double)(grafo->matriz[i][j].tiempoVuelo / 60.0),
                        grafo->matriz[i][j].costoVuelo);
            }
            printf("| %-*s ", ancho - 2, celda);
        }
        printf("|\n");
    }
    printf("\n");
}

// Modificar o agregar valores a una ruta existente
void modificarRuta(Grafo *grafoModificar, int origen, int destino, int tiempo, double costo)
{
    grafoModificar->matriz[origen][destino].tiempoVuelo = tiempo;
    grafoModificar->matriz[origen][destino].costoVuelo = costo;
    printf("\nRuta actualizada correctamente\n");
}

// Eliminar una ruta (tanto el costo como el tiempo se convierten a cero)
void eliminarRuta(Grafo *grafoEliminar, int origen, int destino)
{
    grafoEliminar->matriz[origen][destino].tiempoVuelo = 0;
    grafoEliminar->matriz[origen][destino].costoVuelo = 0.0;
    printf("\nRuta eliminada correctamente\n");
}

// Agregar una nueva ciudad (Se escala la matriz y las etiquetas)
void agregarCiudad(Grafo *grafoModificar, char *nombreCiudad)
{
    int vertices, i;
    vertices = grafoModificar->vertices;
    grafoModificar->vertices++; 

    grafoModificar->etiquetas = (char **)realloc(grafoModificar->etiquetas, grafoModificar->vertices * sizeof(char *));
    grafoModificar->etiquetas[vertices] = (char *)malloc(30 * sizeof(char));
    strcpy(grafoModificar->etiquetas[vertices], nombreCiudad);

    grafoModificar->matriz = (Peso **)realloc(grafoModificar->matriz, grafoModificar->vertices * sizeof(Peso *));

    for (i = 0; i < vertices; i++)
    {
        grafoModificar->matriz[i] = (Peso *)realloc(grafoModificar->matriz[i], grafoModificar->vertices * sizeof(Peso));
        grafoModificar->matriz[i][vertices].tiempoVuelo = 0; // Inicializamos en 0 la nueva celda
        grafoModificar->matriz[i][vertices].costoVuelo = 0.0;
    }

    grafoModificar->matriz[vertices] = (Peso *)malloc(grafoModificar->vertices * sizeof(Peso));
    for (i = 0; i < grafoModificar->vertices; i++)
    {
        grafoModificar->matriz[vertices][i].tiempoVuelo = 0;
        grafoModificar->matriz[vertices][i].costoVuelo = 0.0;
    }
    printf("\nCiudad agregada correctamente a la matriz\n");
}

// Eliminar una ciudad (Se reduce la matriz y las etiquetas)
void eliminarCiudad(Grafo *grafoEliminar, int indice)
{
    int vertices, i, j;
    if (grafoEliminar->vertices <= 1)
    {
        printf("\nError. No se puede eliminar la unica ciudad existente\n");
        return;
    }

    vertices = grafoEliminar->vertices;

    free(grafoEliminar->etiquetas[indice]);
    for (i = indice; i < vertices - 1; i++)
    {
        grafoEliminar->etiquetas[i] = grafoEliminar->etiquetas[i + 1];
    }
    grafoEliminar->etiquetas = (char **)realloc(grafoEliminar->etiquetas, (vertices - 1) * sizeof(char *));

    free(grafoEliminar->matriz[indice]);

    for (i = indice; i < vertices - 1; i++)
    {
        grafoEliminar->matriz[i] = grafoEliminar->matriz[i + 1];
    }

    for (i = 0; i < vertices - 1; i++)
    {
        for (j = indice; j < vertices - 1; j++)
        {
            grafoEliminar->matriz[i][j] = grafoEliminar->matriz[i][j + 1];
        }
        grafoEliminar->matriz[i] = (Peso *)realloc(grafoEliminar->matriz[i], (vertices - 1) * sizeof(Peso));
    }

    grafoEliminar->matriz = (Peso **)realloc(grafoEliminar->matriz, (vertices - 1) * sizeof(Peso *));

    grafoEliminar->vertices--;
    printf("\nCiudad eliminada correctamente\n");
}