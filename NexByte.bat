@echo off
mkdir bin
gcc .\src\dijkstra.h .\src\dijkstra.c .\src\grafo.c .\src\grafo.h .\src\main.c .\src\utils.c .\src\utils.h -o .\bin\programa
start .\bin\programa.exe
