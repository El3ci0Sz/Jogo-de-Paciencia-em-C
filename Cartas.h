#ifndef CARTAS_H
#define CARTAS_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Biblioteca string.h, para poder usar a funçao strcpy//

//Estrutura para Cartas, posicao 0 = pra baixo, posicao 1 = pra cima. //
//Naipes = c,e,o e p//
typedef struct Cartas{
    char NAIPE;
    int VALOR;
    int posicao;
} Cartas;

//Funcao para criar a carta//

void Inicializacarta(Cartas* carta,char NAIPE,int VALOR, int posicao);

//Retornar a variavel solicitada//
char Retornarnaipe(Cartas *carta);
int Retornarvalor(Cartas *carta);
int Retornarposicao(Cartas *carta);

//Altera a posicao//
void Alterarposicao(Cartas* carta);

//Funcoes de verificacao e printe//
int Verifica_mesmo_naipe(Cartas* carta1, Cartas* carta2);
int Verifica_naipe_diferente(Cartas* carta1,Cartas* carta2);
void Exibir(Cartas *carta);

#endif // CARTAS_H


