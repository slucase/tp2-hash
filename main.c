//NOME: LUCAS EDUARDO SILVEIRA COSTA Nº:2017023692


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DELIMITER "!? .,-\n"
#define TAM 256

//STRUCK PARA GERAÇÃO DA HASH TABLE
typedef struct{
  int key;
  char word [46]; //Para caber até a maior palavra da língua portuguesa: "pneumoultramicroscopicossilicovulcanoconiótico"
  int repeticao;
}hashTable;

//merge sort by ptrs
void Merge(char* arr[],int low,int mid,int high) //Merging the Array Function
{
    int nL= mid-low+1;
    int nR= high-mid;

    char** L=malloc(sizeof(char *)*nL);
    char** R=malloc(sizeof(char *)*nR);
    int i;
    for(i=0;i<nL;i++)
    {
        L[i]=malloc(sizeof(arr[low+i]));
        strcpy(L[i],arr[low+i]);
    }
    for(i=0;i<nR;i++)
    {
        R[i]=malloc(sizeof(arr[mid+i+1]));
        strcpy(R[i],arr[mid+i+1]);
    }
    int j=0,k;
    i=0;
    k=low;
    while(i<nL&&j<nR)
    {
        if(strcmp(L[i],R[j])<0)strcpy(arr[k++],L[i++]);
        else strcpy(arr[k++],R[j++]);
    }
    while(i<nL)strcpy(arr[k++],L[i++]);
    while(j<nR)strcpy(arr[k++],R[j++]);

}


void MergeSort(char* arr[],int low,int high) //Main MergeSort function
{
    if(low<high)
    {
        int mid=(low+high)/2;
        MergeSort(arr,low,mid);
        MergeSort(arr,mid+1,high);
        Merge(arr,low,mid,high);
    }
}


//selection sort by ptrs
void SelectionSort(char *wordptr[], int n){
    int i, eff_size, maxpos = 0;
    char *auxptr;

    for (eff_size = n; eff_size > 1; eff_size--){
        for (i = 0; i < eff_size; i++){

            if (strcmp(wordptr[i], wordptr[maxpos]) > 0)
                maxpos = i;

        }
        auxptr = wordptr[maxpos];
        wordptr[maxpos] = wordptr[eff_size-1];
        wordptr[eff_size-1] = auxptr;
    }
}


int main(int argc, char **argv){
  //DECLARAÇÃO DAS VARIAVEIS A SEREM USADAS
  char *word; //CORRIGIR ESSA PORRA
  int 
      i = 0, flag,max,hash = 0, aux = 0, j = 0,h=0, cont_abs=0, reps[5000];
  hashTable ht[TAM], htaux[TAM] /*  unsort_vec[5000], a_aux[1] */;

  word = malloc(46*sizeof(char));

  //sort using ptr
  char unsort_vec[5000][46]; 
  char *vecptr[5000];

  //ABERTURA DO ARQUIVO TXT
  FILE *IN;
  IN = fopen (argv[1],"r");
  //CASO O ARQUIVO NÃO SEJA ABERTO RETORNA O ERRO
  if(IN == NULL){
    printf("Arquivo não foi aberto!\n");
    exit (1);
  }

  //VAMOS ZERAR ESSAS VARIAVEIS DA STRUCT PARA ASSIM TERMOS CERTEZA DE QUE NÃO HAVERA
  //NADA NELAS
  for (i = 0; i < TAM; i++){
    ht[i].repeticao = 0;
    ht[i].key = 0;
  }
  for (i = 0; i < 5001; i++){
    reps[i] = 0;
  }
/*  for (i = 0; i < 5000; i++){
      unsort_vec[i].key = 0;
      unsort_vec[i].repeticao = 0;
  }
*/
  //POR CUIDADOS VAMOS ZERAR O BUFFER TAMBEM
  fflush(stdout);
  
  while ((fscanf (IN, "%m[^"DELIMITER"]%*["DELIMITER"]", &word)) != EOF){
    //VAMOS IGNORAR PALAVRAS COM SOMENTE UMA LETRA
    if(strlen(word) > 1){
      //PASSANDO TUDO PARA LOWER CASE
      for(i = 0; word[i]; i++) word[i] = tolower(word[i]);
      
      //VETOR ---UNSORTED---
      for (i = 1; i <= cont_abs && i > 0; i++){ 
        if(strcmp(unsort_vec[i], word) == 0){
          reps[i]++;
          i=-1;
        }
      }
      if(i > 0){
        strcpy(unsort_vec[cont_abs], word);
        reps[cont_abs]++;
        cont_abs++;
      } 
    }
  }

//assgin pointers
  for (i = 0; i < cont_abs; i++)
      vecptr[i] = unsort_vec[i];

  
  //Sort functions
  //SelectionSort(vecptr, cont_abs);
  MergeSort(vecptr, 0, cont_abs-1); //Main MergeSort function


//printa
  printf("\nCont abs = %d\n",cont_abs);
  	for (i = 0; i < cont_abs; i++){
        j=((vecptr[i]-unsort_vec[0])/sizeof(unsort_vec[0]));
        printf ("%s %d\n",vecptr[i], reps[j]);
	}
    
  //LIMPA A VARIAVEL WORD
  free(word);
  //FECHA O ARQUIVO
  fclose (IN);
  return EXIT_SUCCESS;
}
