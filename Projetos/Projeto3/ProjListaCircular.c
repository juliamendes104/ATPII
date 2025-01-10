#include <stdio.h>
#include <stdlib.h>

typedef struct pessoadalista {
  int I, K, O;
  struct pessoadalista *prox;
} Lista;

Lista *novo(int iden, int k, int o);
void insere(Lista **h, Lista *elem);
int resolve(Lista *h, int k);
void removeCirc(Lista **h, int i);

int main(void) {
  int N, i, iden, k, o;
  Lista *h = NULL, *novoelem;

  scanf("%d", &N);
  for (i = 1; i <= N; i++) {
    //iden = i;
    scanf("%d %d", &k, &o);
    novoelem = novo(i, k, o);
    insere(&h, novoelem);
    //cria o no e o insere na lista
  }

  if(h!=NULL){
    printf("%d\n", resolve(h, h->K));
  }
  else{
    printf("Lista vazia.");
  }

  return 0;
}

Lista *novo(int iden, int k, int o) {
  Lista *aux = malloc(sizeof(Lista));
  aux->I = iden;
  aux->K = k;
  aux->O = o;
  aux->prox = aux;
  return aux;
}
void insere(Lista **h, Lista *elem) {
  Lista *atual = *h, *antes = *h;
  if (!atual) { // lista vazia
    *h = elem;
    return;
  }
  if ((*h)->prox == (*h)) { // apenas um elemento na lista
    elem->prox = atual;
    atual->prox = elem;
    if (elem->I < atual->I) { // se o identificador do elemento for menor que o identificador da cabeça
      *h = elem;
    }
    return;
  }
  while (antes->prox != (*h) && atual->I < elem->I) {
    antes = atual;
    atual = atual->prox;
  }
  if (atual == *h && elem->I < atual->I) { // elemento é menor que a cabeca e portanto nao entrou no while
    antes = atual->prox;
    while (antes->prox != atual) { // enquanto nao chegar ao ultimo elemento antes da cabeca
      antes = antes->prox;
    }
    antes->prox = elem;
    elem->prox = *h;
    *h = elem;
    return;
  } else {//elemento vai ser inserido no meio ou no final
    antes->prox = elem;
    elem->prox = atual;
    return;
  }
}

int resolve(Lista *h, int k) {
  Lista *aux = h, *atual = h;
  Lista *armazenaelem;
  int i, op, iden;
  
  if (h->prox == h) {//apenas um elemento na lista
    return (h->I);
  }
  while (h->prox != h) {//enquanto não houver apenas um elemento na lista
    for (i=0; i < (k-1); i++) {
      atual = atual->prox;
    }
    k = atual->K;
    op = atual->O;
    switch (op) {
    case 0:
      armazenaelem = novo(atual->I, atual->K, 0); // cria um novo no copia do elemento
      iden = atual->I;
      atual = atual->prox;//uma posicao a frente
      removeCirc(&h, iden);
      break;
    case 1:
      insere(&h, armazenaelem);//insere de forma crescente
      armazenaelem = novo(atual->I, atual->K, 0);
      iden = atual->I;
      atual = atual->prox;
      removeCirc(&h, iden);
      break;
    }
  }
  return (h->I);
}
void removeCirc(Lista **h, int iden) {
  Lista *aux = *h, *antes = *h;
  /*if (*h == NULL) {
    printf("Lista vazia");
    return;
  }*/
  while (aux->prox != *h && iden > aux->I) {
    antes = aux;
    aux = aux->prox;
  }
  if (iden == aux->I) {
    if (aux == *h) { // o elemento a ser removido é o primeiro
      antes = aux->prox;
      while (antes->prox != *h) {
        antes = antes->prox;
      }
      antes->prox = aux->prox;
      *h = aux->prox;
      free(aux);
      return;
    } else { // o elemento a ser removido é o ultimo ou esta no meio
      antes->prox = aux->prox;
      free(aux);
      return;
    }
 }
}
