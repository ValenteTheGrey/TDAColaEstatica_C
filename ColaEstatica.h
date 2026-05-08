//
// Created by Martin Valente on 21/04/2026.
//

#ifndef COLAESTATICA_COLAESTATICA_H
#define COLAESTATICA_COLAESTATICA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100
#define TODO_OK 0
#define SIN_MEMORIA 1
#define COLA_VACIA 2

#define MINIMO(a,b) ((a)<(b) ? (a) : (b))

typedef struct{
    char cola[TAM];
    size_t pri;
    size_t ult;
    size_t tamDisp;
}tCola;

void crearCola(tCola* pc);
int ponerEnCola(tCola* pc, const void* pd, size_t tamDato);
int sacoDeCola(tCola* pc, void* pd, size_t tamDato);
int esColaLlena(const tCola* pc, size_t tamDato);
int esColaVacia(const tCola* pc);
int verFrenteDeCola(tCola* pc, void* pd, size_t tamDato);
void vaciarCola(tCola* pc);

#endif //COLAESTATICA_COLAESTATICA_H
