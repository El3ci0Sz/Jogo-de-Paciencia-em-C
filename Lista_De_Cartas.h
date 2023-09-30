#ifndef LISTA_DE_CARTAS_H
#define LISTA_DE_CARTAS_H

#include "Cartas.h"
#include <time.h>

typedef struct No* Apontador;
typedef struct No{
    Cartas cartas;
    struct No* pProx;
}Nocarta;

typedef struct{
    Apontador primeiro;
    Apontador ultimo;
    int tamanho;
}TlistadeCartas;

void FListavazia (TlistadeCartas* Listacarta);
int Retornar_TamanhoL(TlistadeCartas*Listacarta);
int Verificalvazia(TlistadeCartas* Listacarta);
Cartas* Retornar_cartatopo(TlistadeCartas* Listacarta);
Cartas* Retornar_cartaposicao(TlistadeCartas* Listacarta, int posicao);
void Adiciona_cartatopo(TlistadeCartas* Listacarta,Cartas cartas);
int Retira_cartatopo(TlistadeCartas *Listacarta);
int Transferir_carta(TlistadeCartas *Listacarta1,TlistadeCartas*Listacarta2, int qntcartas);
void Embaralhar_L(TlistadeCartas *Listacarta);
int Exibirlista(TlistadeCartas *Listacarta,int uma_ou_todas);
void Printa_N(TlistadeCartas *Listacarta);

//Funçoes Auxiliares//
void Trocar(Cartas Vetor[], int i,int j);
void Embaralhar(Cartas Vetor[], int n);

#endif // LISTA_DE_CARTAS_H
