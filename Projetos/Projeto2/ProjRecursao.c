#include <stdio.h>

int count;
int tamanho=0;
int maiorele=0;
int result[100];
int p=0;

//prototipos das funcoes
void ordenacao(int *conjunto,int M);
void decompor(int *conjunto, int M, int intei, int ind, int *comb, int tcomb, int maior);

int main(void) {
  int N, M, *conjunto, *intei, i, k, *comb;

  scanf("%d %d", &N, &M);
  //alocacao de memoria
  conjunto = malloc(M * sizeof(int));
  intei = malloc(N * sizeof(int));
  comb = malloc(M * sizeof(int));

  //loop para armazenar valores no vetor dos conjuntos
  for(i=0;i<M;i++){
    scanf("%d", &conjunto[i]);
  }
  //loop para armazenar valores no vetor dos inteiros
  for(i=0;i<N;i++){
    scanf("%d", &intei[i]);
  }
  ordenacao(conjunto, M);//chamada da funcao

  //loop para passar um inteiro de cada vez para a funcao
  for(i=0;i<N;i++){
    count=0;//inicializa o contador para cada inteiro

    //inicializa o vetor de combinacoes em 0
    for(k=0;k<M;k++){
    comb[k] =0;
  }
    decompor(conjunto, M, intei[i], 0, comb, 0, 0);//chamada da funcao
    //saida
    printf("%d ", count);
    for(k=0;k<tamanho;k++){
      printf("%d ", result[k]);
    }
    printf("\n");
    //inicializa o vetor result
    for(k=0;k<100;k++){
      result[k]=0;
    }
    //inicializa as variaveis globais
    maiorele=0;
    tamanho=0;
  }
  return 0;
}

//ordenacao ordena o vetor dos conjuntos
void ordenacao(int *conjunto, int M){
  int i, j, aux; 
  
  for (i=0;i<M-1;i++){
    for (j=i+1;j<M;j++) { 
      if(conjunto[j] < conjunto[i]){ 
        aux = conjunto[i];
        conjunto[i] = conjunto[j];
        conjunto[j] = aux;
      } 
    }
  } 
}

void decompor(int *conjunto, int M, int intei, int ind, int *comb, int tcomb, int maior){
  int i, prev;
  if(intei==0){
    count++;//contador das combinacoes
    if((tcomb>tamanho) || (tcomb==tamanho && maior>maiorele)){//se o tamanho do vetor de combinacao é o maior ou o elemento do vetor de combinacao é o maior
      //for para armazenar os valores de combinacao no vetor resultado
      for(p=0;p<tcomb;p++){
        result[p]=comb[p];
      }
      maiorele= maior;
      tamanho = tcomb;
    }
    maior=0;
    tcomb=0;
  }
  if(intei<=0){//se o inteiro é maior ou igual a zero sai da funcao
    return;
  }
  prev=-1;
  //for para percorrer todos os candidatos do conjunto
  for(i=ind;i<M;i++){
    if(conjunto[i]==prev){//se o valor do candidato é igual ao valor do posterior, pula essa iteracao para nao duplicar
      //nunca sera verdadeiro para o primeiro candidato
      continue;
    }
    if(conjunto[i]>maior){
      maior = conjunto[i];
    }
    //armazena candidato no vetor combinacao
    comb[p]=conjunto[i];
    p++;
    decompor(conjunto, M, intei-conjunto[i], i+1, comb, tcomb+1, maior);//chama a funcao recursivamente
    //retira candidato do vetor combinacao
    p--;
    comb[p]=0;
    
    prev=conjunto[i];//valor do prev passa a ser o candidato para comparar com o proximo
  }
}
