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
    FILE *grafoArchivo = fopen("src/EjemploGrafoVuelos.txt", "r");
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