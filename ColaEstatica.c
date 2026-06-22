//
// Created by Martin Valente on 21/04/2026.
//

#include "ColaEstatica.h"

#include "ColaEstatica.h"

void crearCola(tCola* pc)
{
    pc->pri = TAM - 90;          //Para recordar que puede iniciar en cualquier lugar menor que TAM
    pc->ult = TAM - 90;          //La cola es circular, puede empezar en cualquier lado a diferencia de la Pila
    pc->tamDisp = TAM;
}

int ponerEnCola(tCola* pc, const void* pd, size_t tamDato)
{
    int ini, fin;      //Se trata de posiciones del dato a insertar por si debemos partirlo

    if((tamDato + sizeof(size_t)) > pc->tamDisp)        //En cada posición se guarda el dato y el tamaño del dato
        return SIN_MEMORIA;                            //Si p->tamDisp nos dice que hay espacio para guardar todo

    if((ini = MINIMO(TAM - pc->ult, sizeof(size_t))) > 0)
        memcpy(pc->cola + pc->ult, &tamDato, ini);

    if((fin = sizeof(size_t) - ini) !=0)
        memcpy(pc->cola, ((char*)&tamDato) + ini, fin);

    pc->ult = !fin ? pc->ult + sizeof(size_t) : fin;

    //Acá recién empezamos a guardar el dato
    if((ini = MINIMO(TAM - pc->ult, tamDato)) > 0)
        memcpy(pc->cola + pc->ult, pd, ini);

    if((fin = tamDato - ini) != 0)
        memcpy(pc->cola, pd + ini, fin);

    pc->ult = !fin ? pc->ult + tamDato : fin;
    pc->tamDisp -= (tamDato + sizeof(size_t));


    return TODO_OK;
}


int sacoDeCola(tCola* pc, void* pd, size_t tamDato)       //tamDato es el espacio que tengo para copiar
{
    size_t tamInfoCola;
    int ini, fin;

    if(pc->tamDisp == TAM)
        return COLA_VACIA;

    if((ini = MINIMO(TAM - pc->pri, sizeof(size_t))) > 0)
        memcpy(&tamInfoCola, pc->cola + pc->pri, ini);

    if((fin = sizeof(size_t) - ini) > 0)                    //Indica dato particionado
        memcpy(((char*)&tamInfoCola) + ini, pc->cola, fin);

    pc->pri = fin ? fin : pc->pri + sizeof(size_t);

    if((ini = MINIMO(TAM - pc->pri, tamInfoCola)) > 0)
        memcpy(pd, pc->cola + pc->pri, MINIMO(ini, tamDato));

    if((fin = tamInfoCola - ini) > 0 && tamDato - ini > 0)
        memcpy(pd + ini, pc->cola, MINIMO(fin, tamDato - ini));


    pc->pri = fin ? fin : tamInfoCola + pc->pri;
    pc->tamDisp += sizeof(size_t) + tamInfoCola;

    return TODO_OK;
}


int esColaLlena(const tCola* pc, size_t tamDato)
{
    return (tamDato + sizeof(size_t)) > pc->tamDisp;
}


int esColaVacia(const tCola* pc)
{
    return pc->tamDisp ==TAM;
}


int verFrenteDeCola(tCola* pc, void* pd, size_t tamDato)
{
    size_t tamInfoCola;

    int ini, fin;
    size_t priAux;

    if(pc->tamDisp == TAM)
        return COLA_VACIA;

    if((ini = MINIMO(TAM - pc->pri, sizeof(size_t))) > 0)
        memcpy(&tamInfoCola, pc->cola + pc->pri, ini);

    if((fin = sizeof(size_t) - ini) != 0)
        memcpy((char*)&tamInfoCola + ini, pc->cola, fin);

    //No quiero mover pc->pri ya que no voy a quitar el elemento de la cola. Uso un auxiliar.
    priAux = fin ? fin : pc->pri + sizeof(size_t);
    
    //Empiezo con los datos

    if((ini = MINIMO(TAM - priAux, tamInfoCola)) > 0)
        memcpy(pd, (char*)pc->cola + priAux, MINIMO(ini, tamDato));

    if((fin = tamInfoCola - ini) != 0 && tamDato - ini > 0)
        memcpy((char*)pd + ini, pc->cola, MINIMO(fin, tamDato - ini));

    //No se modifican ni pc->pri ni pc->ult ni pc->tamDisp ya que no se quita el elemento

    return TODO_OK;

}


void vaciarCola(tCola* pc)
{
    pc->pri = TAM - 90;
    pc->ult = TAM - 90;
    pc->tamDisp = TAM;      //En verdad solo con esto alcanza
}
