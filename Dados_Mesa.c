#include "Dados_Mesa.h"
//Esta funcao inicializa todas as listas nescessarias para que o jogo aconteça, também zera a pontuaçao
// do jogo
void Inicializar_Mesa(Dados_Mesa * Mesa){
    Mesa->Pontuacao = 0;
    FListavazia(&Mesa->Descarte);
    FListavazia(&Mesa->Baralho);
    int i=0,j=0;
    while(i<7){
        FListavazia(&Mesa->Tableau[i]);
        i++;
    }
    while(j<4){
        FListavazia(&Mesa->Base[j]);
        j++;
    }
}
//Esta funcao cria 52 cartas de um baralho, com seu valor, naipe, e posiçao(no caso todas viradas para baixo)
// Adiciona na lista de carta, depois as embaralha
void Carregar_Baralho_Aleatorio(Dados_Mesa*Mesa){
    char nome[4] = {'o','e','c','p'};
    int j,k;
    for(k=1; k<14;k++){
        for(j=0; j<4; j++){
            Cartas carta;
            Inicializacarta(&carta,nome[j],k,0);
            Adiciona_cartatopo(&Mesa->Baralho,carta);
        }
    }
    EmbaralharL(&Mesa->Baralho);
}
//Atencao//
//Nao sei esta funcao esta certa, pois na especificacao pede para que a ordem das cartas passadas continue a mesma
// entao talvez tenha de fazer uma funcao diferente
void Carregar_Baralho(Dados_Mesa*Mesa,Cartas cartas){
    Adiciona_cartatopo(&Mesa->Baralho,cartas);
}
//Essa funçao pega as cartas a inicializada do Baralho e preenche as 7 Listas do Tableau, e Altera
// A posiçao das cartas do topo para virada para cima.
void Preparar(Dados_Mesa*Mesa){
    int i;
    for(i=1;i<8;i++){
        Transferir_carta(&Mesa->Tableau[i-1],&Mesa->Baralho,i);
        Alterarposicao(Retornar_cartatopo(&Mesa->Tableau[i-1]));
    }
}
int Verificar_Vitoria(Dados_Mesa*Mesa){
    int condicao = 0;
    for(int i =0;i<4;i++){
        if(Retornar_TamanhoL(&Mesa->Base[i]) == 13){
             condicao ++;
        }
    }
    if(condicao == 4){
        printf("Voce gannhou!!!!");
        return 1;
    }
    else{
        return 0;
    }
}
//Esta funçao usa da funcao Exibir_Lista e Exibir cartas dos outros TADs, para exibir cada uma das listas
// para formar a mesa do jogo
void Exibir_Mesa(Dados_Mesa*Mesa){
    Printa_N(&Mesa->Baralho);
    Printa_N(&Mesa->Descarte);
    printf("    ");
    for(int i =0;i<4;i++){
        Printa_N(&Mesa->Base[i]);
    }
    printf("\n");
    int i =0;
    while(i<7){
        printf("\n%d-",i+1);
        Exibirlista(&Mesa->Tableau[i],0);
        i ++;
    }

    printf("                    [Pontuacao:%d]\n",Mesa->Pontuacao);
}
//Esta funçao, tem 2 funcionalidades, a primeira é mover a carta do topo do Baralho para o topo do Descarte
// E a segunda é mover todas as cartas do descarte para o Baralho novamente.
void Comprar_Carta(Dados_Mesa*Mesa){
    if(Verificalvazia(&Mesa->Baralho) == 1){
        Transferir_carta(&Mesa->Baralho, &Mesa->Descarte,Retornar_TamanhoL(&Mesa->Descarte));
        Apontador pAux = Mesa->Baralho.primeiro->pProx;
        while(pAux != NULL){
            Alterarposicao(&pAux->cartas);
            pAux = pAux->pProx;
        }
        Mesa->Pontuacao -= 50;
    }

    else{
        Transferir_carta(&Mesa->Descarte,&Mesa->Baralho,1);
        Alterarposicao(Retornar_cartatopo(&Mesa->Descarte));
    }
}
//modificaçoes caso o i seja nulo//
int DB(Dados_Mesa*Mesa){
    if(Verificalvazia(&Mesa->Descarte)==1){
        return 1;
    }

    int i = 0;
    while(i<4){
        if(Verificalvazia(&Mesa->Base[i])==1){
            if(Verifica_mesmo_naipe(NULL, Retornar_cartatopo(&Mesa->Descarte)) == 0){
                Transferir_carta(&Mesa->Base[i],&Mesa->Descarte,1);
                Mesa->Pontuacao += 10;
                return 0;
            }
        }
        else if(Verifica_mesmo_naipe(Retornar_cartatopo(&Mesa->Base[i]), Retornar_cartatopo(&Mesa->Descarte))==0){
            Transferir_carta(&Mesa->Base[i],&Mesa->Descarte,1);
            Mesa->Pontuacao += 10;
            return 0;
        }
        i++;
    }
    return 1;
}
int DT(Dados_Mesa*Mesa,int coluna){
    if(Verificalvazia(&Mesa->Descarte)==1){
        return 1;
    }
    if(Verificalvazia(&Mesa->Tableau[coluna])==1){
        if(Verifica_naipe_diferente(NULL, Retornar_cartatopo(&Mesa->Descarte))==0){
            Transferir_carta(&Mesa->Tableau[coluna],&Mesa->Descarte,1);
            Mesa->Pontuacao += 5;
            return 0;
        }
    }
    if(Verifica_naipe_diferente(Retornar_cartatopo(&Mesa->Tableau[coluna]), Retornar_cartatopo(&Mesa->Descarte))==0){
            Transferir_carta(&Mesa->Tableau[coluna], &Mesa->Descarte, 1);
            Mesa->Pontuacao += 5;
            return 0;
        }

}

int TB(Dados_Mesa*Mesa, int coluna){
    if(Verificalvazia(&Mesa->Tableau[coluna])==1){
        return 1;
    }

    int i = 0;
    while(i<4){
        if(Verificalvazia(&Mesa->Base[i])==1){
            if(Verifica_mesmo_naipe(NULL, Retornar_cartatopo(&Mesa->Tableau[coluna])) == 0) {
                Transferir_carta(&Mesa->Base[i], &Mesa->Tableau[coluna], 1);
                Mesa->Pontuacao += 10;
            }

            if(Retornarposicao(Retornar_cartatopo(&Mesa->Tableau[coluna])) == 0){
                Alterarposicao(Retornar_cartatopo(&Mesa->Tableau[coluna]));
                    Mesa->Pontuacao += 5;
                }
            return 0;
        }
    if(Verifica_mesmo_naipe(Retornar_cartatopo(&Mesa->Base[i]), Retornar_cartatopo(&Mesa->Tableau[coluna])) == 0){
        Transferir_carta(&Mesa->Base[i],&Mesa->Tableau[coluna],1);

        if(Retornarposicao(Retornar_cartatopo(&Mesa->Tableau[coluna])) == 0){
            Alterarposicao(Retornar_cartatopo(&Mesa->Tableau[coluna]));
            Mesa->Pontuacao += 5;
        }
        Mesa->Pontuacao += 10;
        return 0;
        }
    i++;
    }
    return 1;
}
////Se der problema colocar o else if, no lugar do if///
int BT(Dados_Mesa*Mesa,int base, int coluna){
    if(Verificalvazia(&Mesa->Base[base]) == 1){
        return 1;
    }
    if(Verificalvazia(&Mesa->Tableau[coluna])==1){
        if(Verifica_naipe_diferente(NULL, Retornar_cartatopo(&Mesa->Base[base]))==0){
            Transferir_carta(&Mesa->Tableau[coluna],&Mesa->Base[base],1);
            Mesa->Pontuacao -= 15;
            return 0;
        }
    }
    if(Verifica_naipe_diferente(Retornar_cartatopo(&Mesa->Tableau[coluna]), Retornar_cartatopo(&Mesa->Base[base]))==0){
        Transferir_carta(&Mesa->Tableau[coluna],&Mesa->Base[base],1);
        Mesa->Pontuacao -= 15;
        return 0;
    }
    else{
        return 1;
    }


}
int TT(Dados_Mesa*Mesa, int qntcartas, int Mandar, int Receber){
    if(Verificalvazia(&Mesa->Tableau[Mandar])==1){
        return 1;
    }
    if(qntcartas > Retornar_TamanhoL(&Mesa->Tableau[Mandar])){
        return 1;
    }
    if(Verificalvazia(&Mesa->Tableau[Receber])==1){
        if(Verifica_naipe_diferente(NULL, Retornar_cartaposicao(&Mesa->Tableau[Mandar],Retornar_TamanhoL(&Mesa->Tableau[Mandar]) - qntcartas +1))==0){
            TlistadeCartas ListaAux;
            FListavazia(&ListaAux);
            Transferir_carta(&ListaAux,&Mesa->Tableau[Mandar],qntcartas);
            Transferir_carta(&Mesa->Tableau[Receber],&ListaAux, qntcartas);

            if(Retornarposicao(Retornar_cartatopo(&Mesa->Tableau[Mandar])) == 0){
                Alterarposicao(Retornar_cartatopo(&Mesa->Tableau[Mandar]));
                Mesa->Pontuacao += 5;
            }
            return 0;
        }
    }
        if(Verifica_naipe_diferente(Retornar_cartatopo(&Mesa->Tableau[Receber]), Retornar_cartaposicao(&Mesa->Tableau[Mandar],Retornar_TamanhoL(&Mesa->Tableau[Mandar]) - qntcartas +1))==0){
            TlistadeCartas ListaAux;
            FListavazia(&ListaAux);
            Transferir_carta(&ListaAux,&Mesa->Tableau[Mandar],qntcartas);
            Transferir_carta(&Mesa->Tableau[Receber],&ListaAux, qntcartas);
            if(Retornarposicao(Retornar_cartatopo(&Mesa->Tableau[Mandar])) == 0){
                Alterarposicao(Retornar_cartatopo(&Mesa->Tableau[Mandar]));
                Mesa->Pontuacao += 5;
            }
            return 0;
        }

}

void Instrucoes(void){
    printf("Intrucoes:\n");
    printf("Digite 0, se quiser encerrar o jogo\n");
    printf("CC = Digite 1, para comprar uma carta\n");
    printf("DB = Digite 2, para mover do Descarte para Base\n");
    printf("DT = Digite 3, para mover do Descarte para uma coluna do Tableau\n");
    printf("TB = Digite 4, para mover de uma Coluna do Tableau para Base\n");
    printf("BT = Digite 5, para mover de uma Base para uma coluna do Tableau\n");
    printf("TT = Digite 6, para Mover de uma coluna do Tableau para outra\n\n");
}

int OJogo(Dados_Mesa*Mesa){
    printf("Selecione o tipo de Jogo:\n(1) Interativo  -  (2) Arquivo\n");
    int tipo;
    scanf("%d",&tipo);
    if(tipo == 1 || tipo == 2 ){
    }
    else{
        printf("Valor Invalido!!, escolha entre 1 e 2\n");
    }
    if(tipo == 1){
       int condicao = 0;
       Instrucoes();
       Inicializar_Mesa(Mesa);
        Carregar_Baralho_Aleatorio(Mesa);
        Preparar(Mesa);
        printf("\n");
        int coluna,coluna1,Base,cartas,a,b;
        char Movimento;
        while(1){
            Exibir_Mesa(Mesa);
            printf("Qual movimento deseja realizar?\n{CC}1 {DB}2 {DT}3 {TB}4 {BT}5 {TT}6 {Encerrar}0 {Instrucoes}7\n");
            scanf("%d",&Movimento);
            switch(Movimento){
                case 1:
                    Comprar_Carta(Mesa);
                    break;
                case 2:
                    DB(Mesa);
                    break;
                case 3:
                    printf("Digite qual coluna do Tableau 1-7\n");
                    scanf("%d",&coluna1);
                    DT(Mesa,coluna1-1);
                    break;
                case 4:
                    printf("Digite qual coluna do Tableau 1-7\n");
                    scanf("%d",&coluna);
                    TB(Mesa,coluna-1);
                    break;
                case 5:
                    printf("Digite qual coluna do Tableau 1-7\n");
                    scanf("%d",&coluna-1);
                    printf("Digite qual Base 1-4\n");
                    scanf("%d",&Base);
                    BT(Mesa,Base -1 ,coluna-1);
                    break;
                case 6:
                    printf("Digite a quantidade de cartas:\n");
                    scanf("%d",&cartas);
                    printf("Coluna de que vai tirar:\n");
                    scanf("%d",&a);
                    printf("Coluna  que vai receber:\n");
                    scanf("%d",&b);
                    TT(Mesa,cartas,a-1,b-1);
                    break;
                case 7:
                    Instrucoes();
                    break;
            }
            if(Movimento == 0){
                printf("Encerrado\n");
                break;
            }
            if(Verificar_Vitoria(Mesa)==1){
                printf("Parabén você Ganhou!!!\nSua pontuacao final eh:%d\n",Mesa->Pontuacao);
                break;
            }
       }



    }
    if(tipo == 2){

    }
}

