//NOME: LUCAS EDUARDO SILVEIRA COSTA Nº:2017023692


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DELIMITER "!? .,-\n"
#define MAX_N_W 20000
#define MAX_L_W 46 //Comprimento da maior palavra em PT segundo o Google: "pneumoultramicroscopicossilicovulcanoconiótico"
#define SELECTION_SORT 0
#define MERGE_SORT 1


//Variaveis globais para os nomes dos arquivos de entrada e saída
char
  namein[MAX_L_W], nameout[MAX_L_W];


//void  SelectionSort2(hashTable *wordptr[], int n);

void SeqSearch (char unsort_vec[MAX_N_W][MAX_L_W], int n, int sort_method);
void SelectionSort (char *wordptr[], int n);
void MergeSort (char* arr[],int low,int high); //Main MergeSort function
void Merge (char* arr[],int low,int mid,int high); //Merging the Array Function
void genHashTable (char unsort_vec[MAX_N_W][MAX_L_W], int n, int sort_method);
unsigned int hashFunction(const char* str, unsigned int len);
int OpenTxt (char *unsort_vec[], int cont_abs);


//------------------ MAIN FUNCTION ----------------//

int main(int argc, char **argv){
  
  int 
      i, cont_abs = 0;
  
  char unsort_vec[MAX_N_W][MAX_L_W]; 
  char *vecptr[MAX_N_W];

  for (i = 0; i < MAX_N_W; i++)
    vecptr[i] = unsort_vec[i];

  strcpy(namein, argv[1]);
  strcpy(nameout, argv[4]);

  cont_abs = OpenTxt (vecptr, 0);

  if (strcmp(argv[2], "0") == 0){
      if (strcmp(argv[3], "0") == 0) 
         SeqSearch (unsort_vec, cont_abs, SELECTION_SORT);
      else
         SeqSearch (unsort_vec, cont_abs, MERGE_SORT);
  }
  else{
      if (strcmp(argv[3], "0") == 0) 
         genHashTable (unsort_vec, cont_abs, SELECTION_SORT);
      else
         genHashTable (unsort_vec, cont_abs, MERGE_SORT);
  }
   
  return EXIT_SUCCESS;
}
//------------------END OF MAIN FUNCTION ----------------//




//--------------------OPEN TXT FUNCTION ----------------//

int OpenTxt (char *unsort_vec[], int cont_abs){

  unsort_vec = malloc((cont_abs)*sizeof(char *));

  char 
      *word; 
  word = malloc(MAX_L_W*sizeof(char));
  
  int 
      i;
  
  FILE
      *IN;
  IN = fopen (namein,"r");
  if(IN == NULL){
    printf("Error opening the file! Terminating... \n");
    exit (1);
  }

  //Zerando buffer
  fflush(stdout);

  while ((fscanf (IN, "%m[^"DELIMITER"]%*["DELIMITER"]", &word)) != EOF){
//  while ((fscanf (IN, "%s", &word)) != EOF){
        for(i = 0; word[i]; i++) 
            word[i] = tolower(word[i]);
        //VETOR ---UNSORTED---
        strcpy(unsort_vec[cont_abs], word);
        (cont_abs)++;
  }
  free(word);
  free(unsort_vec);
  fclose (IN);
  return cont_abs;
}

//------------------END OF OPEN TXT FUNCTION ----------------//




//--------------------SEQ  SEARCH  FUNCTION ----------------//

void SeqSearch (char unsort_vec[MAX_N_W][MAX_L_W], int n, int sort_method){
 
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
  
  //SORT METHOD
  if (sort_method == 0)
     SelectionSort(vecptr, cont_abs);
  if (sort_method != 0)
     MergeSort(vecptr, 0, cont_abs-1);

  //Print file
  FILE 
      *OUT;
  OUT = fopen(nameout, "w");
  
  for (i = 0; i < cont_abs; i++){
      j=((vecptr[i]-wordlist[0])/sizeof(wordlist[0]));
      fprintf (OUT, "%s %d\n", vecptr[i], reps[j]);
  }
  fclose(OUT);
  free(word);
}

//------------------END OF SEQ SEARCH FUNCTION ----------------//




//-------------------- HASH SEARCH FUNCTION ----------------//

void genHashTable (char unsort_vec[MAX_N_W][MAX_L_W], int n, int sort_method){

  char 
      *word, *vecptr[MAX_N_W]; //RETIRAR ESSA PORRA

  word = malloc(MAX_L_W*sizeof(char));
 
  
  char wordlist[MAX_N_W][MAX_L_W];

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
        strcpy(wordlist[hash], word);
        reps[hash]++;
      }else if(strcmp(wordlist[hash], word) == 0){
        reps[hash]++;
        cont_abs--;
      }else if (key[hash] == 0){
        while (reps[hash] != 0){
          hash++;
        }
        strcpy(wordlist[hash], word);
        reps[hash] ++;
        key[hash]++;
      }else if(key[hash] != 0){
        for (i = 0;i < MAX_N_W; i++){
          if (strcmp(wordlist[i], word) == 0){
            reps[i]++;
            cont_abs--;
            break;
          }
        }
      }else{
        while (key[hash] != 0){
          hash++;
        }
        strcpy(wordlist[hash], word);
        key[hash]++;
      }
    }
  
  for (i = 0; i < MAX_N_W; i++){
  			if (reps[i] > 0)
                vecptr[j++] = wordlist[i]; 
  }
  
  //SORT METHOD
  if (sort_method == 0)
     SelectionSort(vecptr, cont_abs);
  if (sort_method != 0)
     MergeSort(vecptr, 0, cont_abs-1);

  //Print file
  FILE 
      *OUT;
  OUT = fopen(nameout, "w");
  
  for (i = 0; i < cont_abs; i++){
      j=((vecptr[i]-wordlist[0])/sizeof(wordlist[0]));
      fprintf (OUT, "%s %d\n", vecptr[i], reps[j]);
  }
  fclose(OUT);
  free(word);
}

//------------------END OF HASH SEARCH FUNCTION ----------------//




//-------------------- HASH GEN FUNCTION ----------------//

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
//-------------------- END OF HASH GEN FUNCTION ----------------//





//--------------------MERGE  FUNCTION ----------------//

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
    free(L);
    free(R);
}
//------------------END OF MERGE FUNCTION ----------------//




//--------------------MERGE SORT  FUNCTION ----------------//

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

//------------------END OF MERGE SORT FUNCTION ----------------//




//--------------------SELECT  SORT  FUNCTION ----------------//

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

//------------------END OF SELECT SORT FUNCTION ----------------//
