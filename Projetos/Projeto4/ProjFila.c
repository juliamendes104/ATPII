#include <stdio.h>
#include <stdlib.h>

int *atendente;

typedef struct pessoafila{
int I, O, C;
struct pessoafila *prox;
}Fila;

Fila *novo(int iden, int o, int c);
void insere(Fila **h, Fila **t, Fila *elem);
void atendimento(Fila **h, Fila **t, int livre);
Fila *remover(Fila **h, Fila **t);

int main(void) {
  int N, M, i, j, iden, o, c, menor, livre=0;
  Fila *h= NULL, *t = NULL, *novoelem;

  scanf("%d %d", &N, &M);
  atendente = malloc(M * sizeof(int));//alocacao da variavel global
  for(i=0;i<N;i++){//loops para inserir as pessoas na fila
    scanf("%d %d %d", &iden, &o, &c);
    novoelem = novo(iden, o, c);
    insere(&h, &t, novoelem);
  }
  for(i=0;i<M;i++){
    atendente[i] = 0;
  }

  menor = atendente[0];
  while(h!=NULL){//enquanto a fila nao estiver vazia
    for(j=0;j<M;j++){//loop para encontrar um caixa livre
      if(atendente[j] < menor){
        menor=atendente[j];
        livre = j;
      }
    }
    atendimento(&h,&t,livre);
    menor = atendente[livre];
  }
  for(i=0;i<M;i++){
    printf("%d ", atendente[i]);
  }

  return 0;
}
Fila *novo(int iden, int o, int c){
  Fila *aux = malloc(sizeof(Fila));
  aux->I = iden;
  aux->O = o;
  aux->C = c;
  aux->prox = NULL;
  return aux;
}
void insere(Fila **h, Fila **t, Fila *elem){
  Fila *aux = *h, *antes = *h, *atual;
  if(*h==NULL){//fila vazia
    *h = *t = elem;
    return;
  }
  while(aux->prox!=NULL && aux->O < elem->O){
    antes = aux;
    aux = aux->prox;
  }
  if(aux==*h){//fila com um elemento ou menor que o primeiro
    if(aux->O > elem->O || aux->O == elem->O && aux->I > elem->I){//instante do elemento menor do que o primeiro ou instantes iguais com identificacao do elemento menor
        elem->prox = aux;
        *h = elem;
      }
    else if(aux->O < elem->O || aux->O == elem->O && aux->I < elem->I){//instante do elemento maior que o do primeiro ou instantes iguais com identificacao do elemento maior
      atual = aux;
      while(atual && atual->O == elem->O && atual->I<elem->I){
        aux = atual;
        atual = atual->prox;
      }
      elem->prox = aux->prox;
        aux->prox = elem;
        if(aux==*t){
          *t = elem;
          }
    }
    
  }
  else{
    if(aux->O > elem->O || aux->O == elem->O && aux->I > elem->I){
     antes->prox = elem;
     elem->prox = aux;
    }
    else if(aux->O < elem->O || aux->O == elem->O && aux->I < elem->I){
     elem->prox = aux->prox;
     aux->prox = elem;
      if(aux==*t){
      *t = elem;
      }
    }
  }
  return;
}
Fila *remover(Fila **h, Fila **t){
  Fila *aux;
  if(*h==NULL){
    return NULL;
  }
  aux = *h;
  if(*h!=*t){//condicao caso tenha mais de uma pessoa na fila
    *h = (*h)->prox;
  }
  else{
    *h=*t=NULL;
  }
  return aux;
}
void atendimento(Fila **h, Fila **t, int livre){
  Fila *aux;
  int sub;
  aux = remover(h,t);
  if(aux==NULL){
    return;
  }
  if(aux->O <= atendente[livre]){//condicao caso a pessoa ja esteja na fila na hora do atendimento
    atendente[livre] += aux->C;
  }
  else{
    sub = aux->O - atendente[livre];
    atendente[livre] += sub + aux->C;
  }
}
