#include "Cartas.h"

//criação da carta e atribuição de seu valor e naipe//
void Inicializacarta(Cartas* carta,char NAIPE,int VALOR,int posicao){
    carta -> posicao = posicao;
    carta -> NAIPE = NAIPE;
    carta -> VALOR = VALOR;
}

//Retorna o naipe de determinada carta//
char Retornarnaipe(Cartas *carta){
    return carta->NAIPE;
}
//Retorna o valor de determinada carta//
int Retornarvalor(Cartas *carta){
    return carta->VALOR;
}
//Retorna a posição de determinada carta//
int Retornarposicao(Cartas *carta){
    return carta->posicao;
}
//função que altera entre as posições entre 1 ou 0//
void Alterarposicao(Cartas* carta){
    if(carta->posicao == 0 ){
        carta->posicao = 1;
    }
    else{
        carta->posicao = 0;
    }
}
//função que verifica se a carta é valida para por na base, 0 para verdadeiro e 1 para falso//
int Verifica_mesmo_naipe(Cartas* carta1, Cartas* carta2){
    if(carta2 == NULL){
        return 1;
    }
    else if(carta1 == NULL && Retornarvalor(carta2) == 1){
        return 0;
    }
    else if(carta1==NULL && Retornarvalor(carta2) != 1 ){
    return 1;
    }

    else if(carta1->NAIPE == carta2->NAIPE && carta2->VALOR == (carta1->VALOR)+1){
        return 0;
    }
    else{
        return 1;
    }

}
//função que verifica se a carta pode ser colocado em sequencia no tableau, 0 para verdadeiro e 1 para falso//
int Verifica_naipe_diferente(Cartas* carta1,Cartas* carta2){
    if(carta2 == NULL){
        return 1;
    }
    else if(carta1 == NULL && Retornarvalor(carta2) == 13){
        return 0;
    }
    else if(carta1==NULL && Retornarvalor(carta2) != 13 ){
        return 1;
    }
    else if(carta1 -> NAIPE == carta2->NAIPE){
        return 1;
    }
    else{
        switch(carta2->NAIPE){
            case 'o':
                if(carta1->NAIPE == 'c'){
                    return 1;
                }
                if(Retornarvalor(carta2) == Retornarvalor(carta1)-1){
                    return 0;
                }
                else{
                    return 1;
                }
            case 'c':
                if(carta1->NAIPE == 'o'){
                    return 1;
                }
                if(Retornarvalor(carta2) == Retornarvalor(carta1)-1){
                    return 0;
                }
                else{
                    return 1;
                }
            case 'p':
                if(carta1->NAIPE == 'e'){
                    return 1;
                }
                if(Retornarvalor(carta2) == Retornarvalor(carta1)-1){
                    return 0;
                }
                else{
                    return 1;
                }
            case 'e':
                if(carta1->NAIPE == 'p'){
                    return 1;
                }
                if(Retornarvalor(carta2) == Retornarvalor(carta1)-1){
                    return 0;
                }
                else{
                    return 1;
                }
        }
    }
}
//função que exibe a carta//
void Exibir(Cartas *carta){
    if(carta->posicao == 1){
    printf("[%c%d]", carta->NAIPE,carta->VALOR);
    }
    else{
        printf("[@]");
    }
}
