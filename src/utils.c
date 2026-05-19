#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"

int solicitarEntero(int limiteInferior, int limiteSuperior)
{
    char aux[100];
    int bandera, longitud, i, temp;

    do
    {
        bandera = 1;

        fflush(stdin);
        fgets(aux, 100, stdin);
        longitud = strlen(aux);
        fflush(stdin);

        for (i = 0; i < longitud; i++)
        {
            if (aux[i] == '\n')
                break;

            if (isdigit(aux[i]) || aux[i] == '-')
            {
                bandera = 1;

                if (aux[i] == '-' && (i != 0 || longitud < 3))
                    bandera = 0;
            }
            else
            {
                bandera = 0;
            }

            if (bandera == 0)
            {
                printf("Error validando el dato, favor de ingresarlo de nuevo: ");
                break;
            }
        }

        if (bandera != 0 && longitud > 1)
        {
            temp = atoi(aux);
            if (limiteInferior != limiteSuperior)
            {
                if (temp < limiteInferior || temp > limiteSuperior)
                {
                    bandera = 0;
                    printf("Error, valor fuera de rango, favor de ingresarlo de nuevo: ");
                }
            }
        }

        if (longitud <= 1)
        {
            printf("Error, cadena vacia, favor de ingresar una cadena valida: ");
            bandera = 0;
        }

    } while (bandera == 0);

    return temp;
}

double solicitarFlotante(double limiteInferior, double limiteSuperior)
{
    char aux[100];
    int bandera, longitud, i, banderaDigitoIzquierda, banderaDigitoDerecha;
    double temp;

    do
    {
        banderaDigitoIzquierda = 1;
        banderaDigitoDerecha = 0;
        bandera = 1;

        fflush(stdin);
        fgets(aux, 100, stdin);
        longitud = strlen(aux);
        fflush(stdin);

        for (i = 0; i < longitud; i++)
        {
            if (aux[i] == '\n')
                break;

            if (banderaDigitoIzquierda == banderaDigitoDerecha)
            {
                banderaDigitoDerecha = 1;
            }

            if (isdigit(aux[i]) || aux[i] == '-' || aux[i] == '.')
            {
                bandera = 1;

                if (aux[i] == '-')
                {
                    if (i != 0 || longitud < 3)
                        bandera = 0;
                }

                if (aux[i] == '.')
                {
                    if (i == 1 && aux[0] == '-')
                    {
                        bandera = 0;
                    }
                    else if (banderaDigitoIzquierda == 1)
                    {
                        banderaDigitoIzquierda = 0;
                    }
                    else
                    {
                        bandera = 0;
                    }
                }
            }
            else
            {
                bandera = 0;
            }

            if (bandera == 0)
            {
                printf("Error validando el dato, favor de ingresarlo de nuevo: ");
                break;
            }
        }

        if (bandera != 0 && longitud > 1)
        {
            temp = atof(aux);
            if (limiteInferior != limiteSuperior)
            {
                if (temp < limiteInferior || temp > limiteSuperior)
                {
                    bandera = 0;
                    printf("Error, valor fuera de rango, favor de ingresarlo de nuevo: ");
                }
            }
        }

        if (banderaDigitoIzquierda == banderaDigitoDerecha && bandera != 0)
        {
            printf("Error validando el numero, ingrese uno de nuevo por favor: ");
            bandera = 0;
        }

        if (longitud <= 1)
        {
            printf("Error, cadena vacia, favor de ingresar una cadena valida: ");
            bandera = 0;
        }

    } while (bandera == 0);

    return temp;
}

