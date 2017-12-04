//NOME: LUCAS EDUARDO SILVEIRA COSTA Nº:2017023692


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DELIMITER "!? .,-\n"
#define MAX_N_W 5000
#define MAX_L_W 46 //Comprimento da maior palavra em PT segundo o Google: "pneumoultramicroscopicossilicovulcanoconiótico"
#define OPTION_DEFAULT '0'


//STRUCK PARA GERAÇÃO DA HASH TABLE
typedef struct hTable{
  int key;
  char word[MAX_L_W]; //Para caber até a maior palavra da língua portuguesa: 
  int reps;
}hashTable;


//void  SelectionSort2(hashTable *wordptr[], int n);

void SeqSearch (char unsort_vec[MAX_N_W][MAX_L_W], int n);
void SelectionSort (char *wordptr[], int n);
void MergeSort (char* arr[],int low,int high); //Main MergeSort function
void Merge (char* arr[],int low,int mid,int high); //Merging the Array Function
void genHashTable (char unsort_vec[MAX_N_W][MAX_L_W], int n);
unsigned int hashFunction(const char* str, unsigned int len);
void OpenTxt (char IN, char *unsort_vec[MAX_N_W][MAX_L_W]);


int main(int argc, char **argv){
  //DECLARAÇÃO DAS VARIAVEIS A SEREM USADAS
  char *word; //CORRIGIR ESSA PORRA
  int 
      i = 0, flag,max,hash = 0, aux = 0, j = 0,h=0, cont_abs=0, reps[MAX_N_W];
  
  word = malloc(MAX_L_W*sizeof(char));

  //sort using ptr
  char unsort_vec[MAX_N_W][MAX_L_W]; 
  char *vecptr[MAX_N_W];

  //ABERTURA DO ARQUIVO TXT
  FILE *IN;
  IN = fopen (argv[1],"r");
  //CASO O ARQUIVO NÃO SEJA ABERTO RETORNA O ERRO
  if(IN == NULL){
    printf("Arquivo não foi aberto!\n");
    exit (1);
  }
//POR CUIDADOS VAMOS ZERAR O BUFFER TAMBEM
  fflush(stdout);

  while ((fscanf (IN, "%m[^"DELIMITER"]%*["DELIMITER"]", &word)) != EOF){
      for(i = 0; word[i]; i++) 
          word[i] = tolower(word[i]);
      //VETOR ---UNSORTED---
      strcpy(unsort_vec[cont_abs], word);
      cont_abs++;
  }

  //genHashTable (unsort_vec, cont_abs);
  SeqSearch (unsort_vec, cont_abs);
  
  //LIMPA A VARIAVEL WORD
  free(word);
  //FECHA O ARQUIVO
  fclose (IN);
  return EXIT_SUCCESS;
}

//Merge sort function for MergeSort
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
        L[i]=arr[low+i];
    }
    for(i=0;i<nR;i++)
    {
        R[i] = malloc(sizeof(arr[mid+i+1]));
        R[i] = arr[mid+i+1];
    }
    int j=0,k;
    i=0;
    k=low;
    while(i<nL&&j<nR)
    {
        if(strcmp(L[i],R[j])<0) arr[k++]=L[i++];
        else arr[k++] = R[j++];
    }
    while(i<nL) arr[k++] = L[i++];
    while(j<nR) arr[k++] = R[j++];

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

void SelectionSort(char* wordptr[], int n){
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

void SeqSearch (char unsort_vec[MAX_N_W][MAX_L_W], int n){
 
  char 
      *word, *vecptr[MAX_N_W]; //RETIRAR ESSA PORRA

  word = malloc(MAX_L_W*sizeof(char));
 
  
  char wordlist[MAX_N_W][MAX_L_W];

  int
      i, j, cont_abs, reps[MAX_N_W], key[MAX_N_W]; 

  for (i = 0; i < n; i++){
    reps[i] = 0;
  }


  for (i = 0, cont_abs = 0, j = 0; i < n; i++){
      if(i > 0){
        for (j = 0; j < cont_abs && j >= 0; j++){
            if(strcmp(unsort_vec[i], wordlist[j]) == 0){
                    reps[j]++;
                    j=-2;
            }
        }
      }
      if (j >= 0){
          strcpy(wordlist[cont_abs], unsort_vec[i]);
          reps[cont_abs]++;
          cont_abs++;
      }
     
  }
 
 for (i = 0; i < cont_abs; i++)
    vecptr[i] = wordlist[i];

 printf("\nCont = %d\nPre sort", cont_abs);
   for (i = 0; i < cont_abs; i++){
       printf("\n%s = %d", wordlist[i], reps[i]);
 }
// SelectionSort(vecptr, cont_abs);
 MergeSort(vecptr, 0, cont_abs-1); //Main MergeSort function
 
 printf("\n\nCont = %d\nPos sort", cont_abs);
   for (i = 0; i < cont_abs; i++){
       j=((vecptr[i]-wordlist[0])/sizeof(wordlist[0]));
       printf("\n%s = %d  --- i = %d", vecptr[i], reps[j], i);
   }
  
}

void genHashTable (char unsort_vec[MAX_N_W][MAX_L_W], int n){

  char 
      *word, *vecptr[MAX_N_W]; //RETIRAR ESSA PORRA

  word = malloc(MAX_L_W*sizeof(char));
 
  
  char words[MAX_N_W][MAX_L_W];

  int
      i, hash = 0, aux = 0, j = 0, cont_abs, reps[MAX_N_W], key[MAX_N_W]; 

  for (i = 0; i < MAX_N_W; i++){
    reps[i] = 0;
    key[i] = 0;
  }

  cont_abs = n;

  for (i = 0; i < n; i++){
      strcpy(word, unsort_vec[i]);
      
      hash = hashFunction(word, strlen(word));
      aux = hash;
      if (reps[hash] == 0){
        strcpy(words[hash], word);
        reps[hash]++;
      }else if(strcmp(words[hash], word) == 0){
        reps[hash]++;
        cont_abs--;
      }else if (key[hash] == 0){
        while (reps[hash] != 0){
          hash++;
        }
        strcpy(words[hash], word);
        reps[hash] ++;
        key[hash]++;
      }else if(key[hash] != 0){
        for (i = 0;i < MAX_N_W; i++){
          if (strcmp(words[i], word) == 0){
            reps[i]++;
            cont_abs--;
            break;
          }
        }
      }else{
        while (key[hash] != 0){
          hash++;
        }
        strcpy(words[hash], word);
        key[hash]++;
      }
    }
  
  printf ("contabs = %d \n", cont_abs);
  
  for (i = 0; i < MAX_N_W; i++){
  			if (reps[i] > 0)
                vecptr[j++] = words[i]; 
  }

 SelectionSort(vecptr, cont_abs);
 //MergeSort(vecptr, 0, cont_abs-1); //Main MergeSort function

  for (i = 0; i < cont_abs; i++){
            printf(" %s\n", vecptr[i]); 
  }
  free(word);
}

unsigned int hashFunction(const char* str, unsigned int len){
  const unsigned int resp = 2;
  unsigned int hash = 0;
  unsigned int i = 0;
  for (i = 0; i < len; i++){
    hash *= resp;
    hash ^= (*str);
  }
  return hash%MAX_N_W;
}
