//
// Created by Martin Valente on 21/04/2026.
//

#include "ColaEstatica.h"

#include "ColaEstatica.h"

void crearCola(tCola* p)
{
    p->pri = TAM - 90;          //Para recordar que puede iniciar en cualquier lugar menor que TAM
    p->ult = TAM - 90;          //La cola es circular, puede empezar en cualquier lado a diferencia de la Pila
    p->tamDisp = TAM;
}

int ponerEnCola(tCola* p, const void* d, size_t tamDato)
{
    int ini, fin;      //Se trata de posiciones del dato a insertar por si debemos partirlo

    if((tamDato + sizeof(size_t)) > p->tamDisp)        //En cada posición se guarda el dato y el tamaño del dato
        return SIN_MEMORIA;                            //Si p->tamDisp nos dice que hay espacio para guardar todo

    if((ini = MINIMO(TAM - p->ult, sizeof(size_t))) > 0)
        memcpy(p->cola + p->ult, &tamDato, ini);

    if((fin = sizeof(size_t) - ini) !=0)
        memcpy(p->cola, ((char*)&tamDato) + ini, fin);

    p->ult = !fin ? p->ult + sizeof(size_t) : fin;

    //Acá recién empezamos a guardar el dato
    if((ini = MINIMO(TAM - p->ult, tamDato)) > 0)
        memcpy(p->cola + p->ult, d, ini);

    if((fin = tamDato - ini) != 0)
        memcpy(p->cola, d + ini, fin);

    p->ult = !fin ? p->ult + tamDato : fin;
    p->tamDisp -= (tamDato + sizeof(size_t));


    return TODO_OK;
}


int sacoDeCola(tCola* p, void* d, size_t tamDato)       //tamDato es el espacio que tengo para copiar
{
    size_t tamInfoCola;
    int ini, fin;

    if(p->tamDisp == TAM)
        return COLA_VACIA;

    if((ini = MINIMO(TAM - p->pri, sizeof(size_t))) > 0)
        memcpy(&tamInfoCola, p->cola + p->pri, ini);

    if((fin = sizeof(size_t) - ini) > 0)                    //Indica dato particionado
        memcpy(((char*)&tamInfoCola) + ini, p->cola, fin);

    p->pri = fin ? fin : p->pri + sizeof(size_t);

    if((ini = MINIMO(TAM - p->pri, tamInfoCola)) > 0)
        memcpy(d, p->cola + p->pri, MINIMO(ini, tamDato));

    if((fin = tamInfoCola - ini) > 0 && tamDato - ini > 0)
        memcpy(d + ini, p->cola, MINIMO(fin, tamDato - ini));


    p->pri = fin ? fin : tamInfoCola + p->pri;
    p->tamDisp += sizeof(size_t) + tamInfoCola;

    return TODO_OK;
}


int esColaLlena(const tCola* p, size_t tamDato)
{
    return (tamDato + sizeof(size_t)) > p->tamDisp;
}


int esColaVacia(const tCola* p)
{
    return p->tamDisp ==TAM;
}


int verFrenteDeColaEst(tColaEst* pc, void* pd, size_t tamDato)
{
    size_t tamInfoCola;

    int ini, fin;

    if((ini = MINIMO(TAM - pc->pri, sizeof(size_t))) > 0)
        memcpy(&tamInfoCola, pc->cola + pc->pri, ini);

    if((fin = sizeof(size_t) - ini) != 0)
        memcpy((char*)&tamInfoCola + ini, pc->cola, fin);

    //No quiero mover pc->pri ya que no voy a quitar el elemento de la cola
    //Empiezo con los datos

    if((ini = MINIMO(TAM - pc->pri, tamInfoCola)) > 0)
        memcpy(pd, (char*)pc->cola + pc->pri, MINIMO(ini, tamDato));

    if((fin = tamInfoCola - ini) != 0 && tamDato - ini > 0)
        memcpy((char*)pd + ini, pc->cola, MINIMO(fin, tamDato - ini));

    //No se modifican ni pc->pri ni pc->ult ni pc->tamDips ya que no se quita el elemento

    return TODO_OK

}
