#include "Lista_De_Cartas.h"

//A funçao cria uma lista encadeada vazia,tendo apenas a "cabeça" ela aloca um espaço na memoria, faz com que o apotador ultimo, aponte para a cabeça, e faz com que depois da primeira celula não tenha nenhuma, definindo primeiro->prox como NULL  //
void FListavazia (TlistadeCartas* Listacarta){
    Listacarta->primeiro = (Apontador) malloc(sizeof(Nocarta));
    Listacarta->ultimo = Listacarta->primeiro;
    Listacarta->primeiro->pProx = NULL;
    Listacarta->tamanho = 0;
}

//Esta funçao percorre toda a lista contando seu tamanho,e no final retorna o tamanho da lista//
int Retornar_TamanhoL(TlistadeCartas*Listacarta){
    int count = 0;
    Apontador pAux = Listacarta->primeiro->pProx;
    if(pAux == NULL){
        return 0;
    }
    while(pAux != NULL){
        count ++;
        pAux = pAux->pProx;
    }
    return count;
}

//Essa funçao retorna 1, se a lista estiver vazia e 0, se a lista não estiver vazia//
int Verificalvazia(TlistadeCartas* Listacarta){
    if(Listacarta->primeiro->pProx == NULL){
        return 1;
    }
    else{
    return 0;
    }
}

//Se a lista não estiver vazia, esta função Retorna a carta que esta na primeira celula, que esta na primeira posição(Listacarta->primeiro->pProx) da lista encadeada//
Cartas* Retornar_cartatopo(TlistadeCartas* Listacarta){
    Apontador pAux = Listacarta->primeiro;
    while(pAux->pProx != NULL){
        pAux = pAux->pProx;
    }
    Listacarta->ultimo = pAux;
    return &pAux->cartas;
}

//Se a posicao da carta requisitada não for maior do que o quantidade de cartas no baralho, esta fucao, retornara uma quarta de uma determinada posicao
//Há um apontador auxiliar, que percorrera a lista elemento por elemento ate chegar na posicao desejada.
Cartas* Retornar_cartaposicao(TlistadeCartas* Listacarta, int posicao){
    if(posicao > Retornar_TamanhoL(Listacarta)){
        return NULL;
    }
    Apontador Noaux = Listacarta->primeiro->pProx;
    int count = 1;
    while(count < posicao){
        Noaux= Noaux->pProx;
        count++;
    }
    return &Noaux->cartas;
}

//Como o nosso topo ficou definido como começando do primeiro elemento da lista, a nova carta devera estar
// Na posição 1 da lista(Listacarta->primeiro->pProx), dito isto a funçao aloca um espaço na memoria para uma carta
// Recebe os dado de uma carta como parametro, e depois coloca a carta na primeira posicao da lista,e aumentando em 1 o tamanho da lista.
void Adiciona_cartatopo(TlistadeCartas* Listacarta,Cartas cartas){
    Apontador pAux = Listacarta->primeiro;
    while(pAux->pProx != NULL){
        pAux = pAux->pProx;
    }
    pAux->pProx = (Apontador) malloc(sizeof(Nocarta));
    Listacarta->ultimo = pAux->pProx;
    Listacarta->ultimo->cartas = cartas;
    Listacarta->ultimo->pProx = NULL;
    Listacarta->tamanho ++;
}

//Como dito antes o topo é o começo da lista, então.Se a lista nao estiver vazia, esta fução retira a primeira celula da Lista, tirando assim
// também a carta que estava armazenada na mesma, no final desocupando o espaço dela na memoria com free, e diminuindo em 1 o tamanho da lista
int Retira_cartatopo(TlistadeCartas *Listacarta) {
    if (Verificalvazia(Listacarta) == 1) {
        return 1;

    }
    Apontador pAux = Listacarta->primeiro;
    if (pAux->pProx == NULL) {
        free(pAux);
        pAux = NULL;
        return 0;
    } else {
        while (pAux->pProx->pProx != NULL) {
            pAux = pAux->pProx;
        }
    }
    free(pAux->pProx);
    pAux->pProx = NULL;
    return 0;
  }


//Listacarta2 que vai ser tirado as cartas, Listacarta1 que vai receber as cartas, int quantidade de cartas a serem retiradas//
int Transferir_carta(TlistadeCartas *Listacarta1,TlistadeCartas*Listacarta2, int qntcartas){
    int i = 0;
    if(qntcartas > Retornar_TamanhoL(Listacarta2)){
        return 1;
    }
    while(i < qntcartas){
        Adiciona_cartatopo(Listacarta1,*Retornar_cartatopo(Listacarta2));
        Retira_cartatopo(Listacarta2);
        i++;
    }
    return 0;
}


//Esta funcao embaralha as cartas, isto é muda a posição de cada uma para posições aleatorias, usando um Vetor auxiliar
// E também um algoritimo para fazer o embaralhamento


void EmbaralharL(TlistadeCartas *Listacarta) {
    Cartas Vetor_Auxiliar[Retornar_TamanhoL(Listacarta)];
    int i;
    Apontador pAux = Listacarta->primeiro->pProx;
    for (i = 0; i < Retornar_TamanhoL(Listacarta); i++) {
        Vetor_Auxiliar[i] = pAux->cartas;
        pAux = pAux->pProx;
    }

    srand(time(NULL));
    Embaralhar(Vetor_Auxiliar, Retornar_TamanhoL(Listacarta));
    pAux = Listacarta->primeiro->pProx;
    for (i = 0; i < Retornar_TamanhoL(Listacarta); i++) {
        pAux->cartas = Vetor_Auxiliar[i];              //Nesta parte eu utilizei de//
        pAux = pAux->pProx;                            // Duas funções que fazem parte do//
    }                                                  // "Algoritimo de fisher_yates"//
}

//Caso a lista esteja vaiza a função ira printar "A Lista esta Vazia", caso não, a duas alternativas
// Se o parametro int for 0, exibira a carta do topo, se for 1, exibira todas as cartas da lista
int Exibirlista(TlistadeCartas *Listacarta,int uma_ou_todas){
    if(Listacarta->primeiro->pProx == NULL){
        return 1;
    }
    else if(uma_ou_todas == 1){
        Exibir(&Listacarta->primeiro->pProx->cartas);
        return 0;
    }
    else if(uma_ou_todas == 0){
        int count = 0;
        Apontador pAux = Listacarta->primeiro->pProx;
        while(count < Retornar_TamanhoL(Listacarta)){
            Exibir(&pAux->cartas);
            pAux = pAux->pProx;
            count ++;
        }
    return 0;
    }

    return 1;
}


//Algoritimo de fisher_yates//
//Esta primerio funcao troca os elementos de um vetor de posicao, usando um auxiliar
// e valores(para posicao) dados na funçao embaralhar;
void Trocar(Cartas Vetor[], int i,int j){
    Cartas auxiliar = Vetor[i];
    Vetor[i] = Vetor[j];
    Vetor[j] = auxiliar;
}

//Esta funcao recebe um vetor de cartas, mais o tamanho deste vetor, e "embaralha"/gera posicaos aleatorias
// para servir de parametro para a funcao trocar
void Embaralhar(Cartas Vetor[], int n){
    int i;
    for(i = 0;i <= n - 2;i++){
        int j = i  + rand() % (n-i);
        Trocar(Vetor,i,j);
    }
}
void Printa_N(TlistadeCartas *Listacarta){
    if(Verificalvazia(Listacarta) == 1){
        printf("[N]");
    }
    else{
        Exibir(Retornar_cartatopo(Listacarta));
    }
}