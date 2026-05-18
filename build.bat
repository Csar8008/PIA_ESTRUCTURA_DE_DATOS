@echo off
gcc .\src\dijkstra.h .\src\dijkstra.c .\src\grafo.c .\src\grafo.h .\src\main.c -o .\bin\programa
.\bin\programa.exe
@pause