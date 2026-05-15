## Sistema de Gestión de Vuelos con Grafos

Proyecto desarrollado en lenguaje C para la representación y análisis de rutas aéreas mediante grafos dirigidos y ponderados.

## Descripción

El programa permite importar un grafo desde un archivo de texto, donde cada vértice representa una ciudad o destino y cada arista representa un vuelo con dos pesos asociados:

- Tiempo de vuelo
- Costo del vuelo

El sistema puede:

- Leer y validar archivos de entrada
- Construir dinámicamente el grafo
- Mostrar la matriz de adyacencia
- Calcular rutas óptimas utilizando el algoritmo de Dijkstra
- Buscar rutas según:
  - Menor tiempo de vuelo
  - Menor costo económico
  - 
## Estructura del Proyecto

main.c    
grafo.c
grafo.h
EjemploGrafoVuelos.txt
README.md

## Archivos

### `main.c`

Contiene el flujo principal del programa y la interacción general con el usuario.

### `grafo.h`

Define:

- Estructuras del grafo
- Tipos de datos
- Prototipos de funciones

### `grafo.c`

Implementa:

- Inicialización del grafo
- Liberación de memoria
- Validación del archivo
- Importación del grafo
- Impresión de la matriz de adyacencia


### `EjemploGrafoVuelos.txt`

Archivo de entrada con la información del grafo.

---

## Formato del Archivo

El archivo debe seguir el siguiente formato:

```txt
2
{
0, 0.0
90, 120.0
}
{
240, 100.0
0, 0.0
}
[
Destino 1
Destino 2
]
```

### Explicación

- El primer número representa la cantidad de vértices.
- Cada bloque entre `{}` representa una fila de la matriz de adyacencia.
- Cada elemento contiene:
  - Tiempo de vuelo en minutos
  - Costo del vuelo
- El bloque `[]` contiene las etiquetas o nombres de los destinos.

---

## Compilación

Compilar utilizando GCC:

```bash
gcc *.c -o vuelos.exe
```

---

## Ejecución

En Windows CMD:

```bash
vuelos.exe
```

---

## Requisitos

- GCC (MinGW o equivalente)
- Sistema operativo compatible con C estándar

---
