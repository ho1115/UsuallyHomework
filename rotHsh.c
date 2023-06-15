#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Stringgs strs;

struct Stringgs {
  char* cont;
  int val;
  strs* prev;
  strs* next;
};


int orgHash(char* str, int len, int P) {
  int hash = 0;
  for (int i = 0; i < len; i++) {hash = ((hash*27) % P + str[i] - 96) % P;}
  return hash;     
}

int sameCheck(char* str1, char* str2, int len, int shift) {
  for (int i = 0; i < len; i++) {if (str1[(i+shift)%len] != str2[i]) {return 0;}}
  return 1;     
}

int main () {
  int N, Q, ope, len, hash, shift, P = 1000000181;
  long long pairs = 0;
  char* tmp = (char*) malloc(sizeof(char) * 1000001); 
  scanf("%d%d", &N, &Q);
  strs* set = (strs*) malloc(sizeof(strs) * (N+Q));
  strs* head = set;
  strs* ptr = NULL;
  strs* last = set[N-1];
  char* strpool = (char*) malloc(sizeof(char) * (N+Q) * (len+1));
  scanf("%s", tmp);
  len = strlen(tmp);
  char* str = (char*) malloc(sizeof(char) * (len+1));
  strcpy(str, tmp);
  free(tmp);
  int h = (int) ceil(pow(27, len-1)) % P;
  set[0].prev = NULL;
  set[0].next = NULL;
  for (int i = 0; i < N; i++) {
    if (i != 0) {
      scanf("%s", str);
      set[i].prev = &set[i-1];
      set[i].next = NULL;
    }
    set[i].cont = strpool + i*(len+1);
    strcpy(strpool + i*(len+1), str);
    hash = orgHash(str, len, P);
    if (hash < 0) {hash += P;}
    set[i].val = hash;
    for (int j = 0; j < len; j++) {
      shift = j;
      ptr = head;
      if (j != 0) {
        hash = (27*((hash-(set[i].cont[j-1] - 96)*h) % P) + set[i].cont[j-1] - 96) % P;
        if (hash < 0) {hash += P;}
      }
      while (ptr && ptr != set[i]) {
        if (ptr->val == hash && sameCheck(set[i].cont, ptr->cont, len, shift) == 1) {pairs++;}
        ptr = ptr->next;
      }
    }
  }
  for (int i = 0; i < Q; i++) {    
    scanf("%d", &ope);
    scanf("%s", str);
    if (ope == 1) {      
      set[i+N].prev = last;
      set[i+N].next = NULL;
      set[i+N].cont = strpool + (i+N)*(len+1);
      last = set[i+N];
      strcpy(strpool + (i+N)*(len+1), str);
      hash = orgHash(str, len, P);
      if (hash < 0) {hash += P;}
      set[i+N].val = hash;
      for (int j = 0; j < len; j++) {
        shift = j;
        ptr = head;
        if (j != 0) {
          hash = (27*((hash-(set[i+N].cont[j-1] - 96)*h) % P) + set[i+N].cont[j-1] - 96) % P;
          if (hash < 0) {hash += P;}
        }
        while (ptr && ptr != set[i+N]) {
          if (ptr->val == hash && sameCheck(set[i+N].cont, ptr->cont, len, shift) == 1) {pairs++;}
          ptr = ptr->next;
        }
      }
    } else {
      ptr = head; 
      while () { 

      }
    }
  }
  return 0;
}
