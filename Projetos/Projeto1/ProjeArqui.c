#include <stdio.h>
#include <math.h>
#include <string.h>

int main(void) {
  FILE *cd, *pl, *ln;
  int n, i, j=0, k=0;
  char palavra[20];

  //fopen abre o arquivo
  cd=fopen("codigos.dat", "r");
  //fopen abre o arquvio
  pl=fopen("palavras.dat", "r");

  //le o conteudo do arquivo até o final
  while(!feof(pl)){
    fscanf(pl, "%s", palavra);
    k++;//contador para a quantidade de palavras
  }//fim do while
  char pal[k][20];
  //posiciona o ponteiro para o inicio do arquivo
  fseek(pl, 0, SEEK_SET);
  //armazena cada palavra em um vetor
  for(i=0;i<k;i++){
    fscanf(pl, "%s", palavra);
    strcpy(pal[i], palavra);
  }//fim do for
  //posiciona o ponteiro para o inicio do arquivo
  fseek(pl, 0, SEEK_SET);
  //fopen abre o arquivo
  ln=fopen("linhas.dat", "w");
  k=0;
  //le o conteudo de ambos os arquivos ate o final
  while(!feof(pl) && !feof(cd)){
    fscanf(cd,"%d", &n);//le um codigo do arquivo
      if(n>0){
        //caso o codigo for maior que zero; le uma certa quantidade de palavra e a imprime no arquivo linhas.dat
        for(i=0;i<n;i++){
          fscanf(pl,"%s", palavra);
          fprintf(ln,"%s ", palavra);
          k++;
        }//fim do for
      }
    //se o codigo for igual a zero; imprime zero no arquivo
      if(n==0){
        fprintf(ln,"%d", n);
      }
    //caso o codigo for menor que zero; retorna uma quantidade de palavras
      if(n<0){
        for(i=1;i<=abs(n);i++){
          //posiciona o ponteiro para o inicio de cada palavra
          fseek(pl, -1*strlen(pal[k-i])-1, SEEK_CUR);
        }
        for(i=0;i<abs(n);i++){
          fscanf(pl,"%s", palavra);
          fprintf(ln,"%s ", palavra);
        }
      }
      fprintf(ln,"\n");
  }
  //caso o arquivo codigos.dat não tenha chegado ao fim
  if(!feof(cd)){
    while(!feof(cd)){
      //imprime os codigos restante
      fscanf(cd,"%d", &n);
      fprintf(ln,"%d ", n);
    }
  }//fim do if
  //caso o arquivo palavras.dat não tenha chegado ao fim
  if(!feof(pl)){
    while(!feof(pl)){
      //escreve 5 palavras em cada linha
      if(j==5){
      fprintf(ln,"\n");  
      }
      fscanf(pl,"%s", palavra);
      fprintf(ln,"%s ", palavra);
      j++;
    }
  }
  fclose(cd);
  fclose(pl);
  fclose(ln);
  //fclose fecha o arquivo
  
}
