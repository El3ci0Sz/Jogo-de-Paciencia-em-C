#ifndef DADOS_MESA_H
#define DADOS_MESA_H
#include "Lista_De_Cartas.h"

typedef struct{
    TlistadeCartas Baralho;
    TlistadeCartas Descarte;
    TlistadeCartas Base[4];
    TlistadeCartas Tableau[7];
    int Pontuacao;
}Dados_Mesa;

void Inicializar_Mesa(Dados_Mesa * Mesa);
void Carregar_Baralho_Aleatorio(Dados_Mesa*Mesa);
void Carregar_Baralho(Dados_Mesa*Mesa,Cartas cartas);
void Preparar(Dados_Mesa*Mesa);
int Verificar_Vitoria(Dados_Mesa*Mesa);
void Exibir_Mesa(Dados_Mesa*Mesa);
void Comprar_Carta(Dados_Mesa*Mesa);
int DB(Dados_Mesa*Mesa);
int DT(Dados_Mesa*Mesa, int coluna);
int TB(Dados_Mesa*Mesa,int coluna);
int BT(Dados_Mesa*Mesa,int base, int coluna);
int TT(Dados_Mesa*Mesa, int qntcartas, int indobt, int indrec);
int OJogo(Dados_Mesa*Mesa);
void Instrucoes(void);

#endif // DADOS_MESA_H