//tempo de ordenacao do quicksort
#include <stdio.h>
#include <stdlib.h>
#include <time.h>//para usar o clock
#define N 200000
//tamanho do vetor

typedef struct biggo {
  int high;
  int low;
} BigInt;

void quicksort(BigInt *vet, int lo, int hi);

int main(void) {
  clock_t begin;//para a contagem;
  double tempo;
  FILE *b = fopen("bigint.dat", "r");
  FILE *q = fopen("quick.dat", "w");
  BigInt vet[N];
  int i = 0;

  
  fscanf(b, "%d %d", &vet[i].high, &vet[i].low);//pega a primeira linha de dados
  while (!feof(b)) {//enquanto o arquivo nao chega ao fim
    i++;
    fscanf(b, "%d %d", &vet[i].high, &vet[i].low);
  }

  begin = clock();//comeca a contar o tempo

  quicksort(vet, 0, N-1);

  begin = clock() - begin;//tempo final menor o inicial
  tempo = ((double)begin)/CLOCKS_PER_SEC;//convertendo em segundos;
  
  //printf("%lf", tempo);
  
  for(i=0;i<N;i++){//armazena os dados no arquivo quick
    fprintf(q,"%d %d\n", vet[i].high, vet[i].low);
  }
  return 0;
}

void quicksort(BigInt *vet, int lo, int hi) {
  int i, pivo, bigger;
  BigInt aux;
  if (lo < hi) {
    pivo = hi;//pivo na ultima posicao
    bigger = lo;//bigger na primeira posicao
    for (i = bigger; i < hi; i++) {//loop para percorrer a parte direita do bigger
      if (vet[i].high < vet[hi].high || vet[i].high == vet[hi].high && (vet[i].high>=0 && vet[i].low < vet[hi].low || vet[i].high<0 && vet[i].low>vet[hi].low)) {//caso o high seja menor ou caso seja igual e positivo e o low seja menor ou caso seja igual e negativo e o low sejs maior
        aux = vet[i];
        vet[i] = vet[bigger];
        vet[bigger] = aux;//realiza a troca com o bigger
        bigger++;//bigger vai uma posicao para frente
      }
    }
    aux = vet[hi];
    vet[hi] = vet[bigger];
    vet[bigger] = aux;//troca o bigger e o pivo para os elementos a esquerda do pivo sejam menores que ele e a direita maiores
    quicksort(vet,lo,bigger-1);//recursao para o vetor a esquerda do pivo
    quicksort(vet,bigger+1,hi);//recursao para o vetor a direita do pivo
  }
}
