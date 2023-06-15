#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hashnode hNod;

struct Hashnode {
  int idx; int cnt; 
};


int orgHash(char* str, int len, int P) {
  int hash = 0;
  for (int i = 0; i < len; i++) {hash = ((hash*26) % P + str[i] - 97) % P;}
  return hash < 0 ? hash + P : hash;     
}

int shiftHash(char* str, int len, int P, int shift) {
  int hash = 0;
  for (int i = 0; i < len; i++) {hash = ((hash*26) % P + str[(i+shift)%len] - 97) % P;}
  return hash < 0 ? hash + P : hash;     
}

int sameCheck(char* str1, char* str2, int len, int shift, int cnt) {
  if (cnt == 0) {return 0;}
  for (int i = 0; i < len; i++) {if (str1[(i+shift)%len] != str2[i]) {return 0;}}
  return 1;     
}

int main () {
  int N, Q, ope, len, hash, tmphash, sechash, shift, cond = 0, P = 10000103, P2 = 10000453;
  long long pairs = 0;
  char* tmp = (char*) malloc(sizeof(char) * 1000001); 
  scanf("%d%d", &N, &Q);
  hNod* table = (hNod*) calloc(P, sizeof(hNod));
  scanf("%s", tmp);
  len = strlen(tmp); printf("len = %d\n", len);
  char* strpool = (char*) malloc(sizeof(char) * (N+Q) * (len+1));
  char* str = (char*) malloc(sizeof(char) * (len+1));
  strcpy(str, tmp);
  free(tmp);
  int h = 26;
  for (int i = 0; i < len-2; i++) {
    h = (h * 26) % P;
    if (h < 0) {h += P;}
  }
  printf("h = %d\n", h);  
  for (int i = 0; i < N; i++) {
    if (i != 0) {scanf("%s", str);}
    hash = orgHash(str, len, P); printf("orgHash = %d\n", hash);
    sechash = orgHash(str, len, P2);
    tmphash = hash;
    if (table[hash].cnt == 0) {
        table[hash].cnt++;
        table[hash].idx = i;
        strcpy(strpool + i*(len+1), str);
    } else {
        if (sameCheck(str, strpool + table[hash].idx*(len+1), len, 0,  table[hash].cnt) == 1) {
            pairs += table[hash].cnt;
            table[hash].cnt++;
        } else {
            tmphash = (tmphash + sechash) % P;
            if (tmphash < 0) {tmphash += P;} printf("colHash = %d\n", tmphash);
            while (table[tmphash].cnt > 0 && sameCheck(str, strpool + table[tmphash].idx*(len+1), len, 0, table[tmphash].cnt) == 0) {
                tmphash = (tmphash + sechash) % P;
                if (tmphash < 0) {tmphash += P;}
                printf("colHash = %d\n", tmphash);
            } printf("colHash = %d\n -------------------\n", tmphash);
            if (table[tmphash].cnt == 0) {
                table[tmphash].cnt++;
                table[tmphash].idx = i;
                strcpy(strpool + i*(len+1), str);
            } else {
                pairs += table[tmphash].cnt;
                table[tmphash].cnt++;
            }
        }
    }
    for (int j = 0; j < len; j++) {
        if (j == 0) {
            tmphash = hash;
            continue;
        }
        shift = j;        
        tmphash = (26*((tmphash-(str[j-1] - 97)*h) % P) + str[j-1] - 97) % P; 
        if (tmphash < 0) {tmphash += P;}printf("loop %d , rot hash = %d, org hash = %d\n", j, tmphash, hash);
        if (tmphash == hash) {break;}    
        if (table[tmphash].cnt == 0) {continue;} 
        else if (sameCheck(str, strpool + table[tmphash].idx*(len+1), len, shift,  table[tmphash].cnt) == 1) {pairs += table[tmphash].cnt;} 
        else {
            sechash = shiftHash(str, len, P2, shift);
            tmphash = (tmphash + sechash) % P;
            if (tmphash < 0) {tmphash += P;}
            while (table[tmphash].cnt > 0 && sameCheck(str, strpool + table[tmphash].idx*(len+1), len, 0, table[tmphash].cnt) == 0) {
                tmphash = (tmphash + sechash) % P;
                if (tmphash < 0) {tmphash += P;}
            } 
            if (table[tmphash].cnt > 0) {pairs += table[tmphash].cnt;}
        }
    }
  }
  printf("%lld\n", pairs);
  for (int i = 0; i < Q; i++) {    
    scanf("%d", &ope);
    scanf("%s", str);
    if (ope == 1) {      
      hash = orgHash(str, len, P);printf("orgHash = %d\n", hash);
      sechash = orgHash(str, len, P2);
      tmphash = hash;
      if (table[hash].cnt == 0) {
        table[hash].cnt++;
        table[hash].idx = i+N;
        strcpy(strpool + (i+N)*(len+1), str);
      } else {
          if (sameCheck(str, strpool + table[hash].idx*(len+1), len, 0,  table[hash].cnt) == 1) {
            pairs += table[hash].cnt;
            table[hash].cnt++;
          } else {
              tmphash = (tmphash + sechash) % P;
              if (tmphash < 0) {tmphash += P;}printf("colHash = %d\n", tmphash);
              while (table[tmphash].cnt > 0 && sameCheck(str, strpool + table[tmphash].idx*(len+1), len, 0, table[tmphash].cnt) == 0) {
                tmphash = (tmphash + sechash) % P;
                if (tmphash < 0) {tmphash += P;}printf("colHash = %d\n", tmphash);
              } printf("colHash = %d\n---------\n", tmphash);
              if (table[tmphash].cnt == 0) {
                table[tmphash].cnt++;
                table[tmphash].idx = i+N;
                strcpy(strpool + (i+N)*(len+1), str);
              } else {
                pairs += table[tmphash].cnt;
                table[tmphash].cnt++;
              }
            }
        }

      for (int j = 0; j < len; j++) {
        if (j == 0) {
            tmphash = hash;
            continue;
        }
        shift = j;        
        tmphash = (26*((tmphash-(str[j-1] - 97)*h) % P) + str[j-1] - 97) % P;
        if (tmphash < 0) {tmphash += P;}printf("loop %d , rot hash = %d, org hash = %d\n", j, tmphash, hash);
        if (tmphash == hash) {break;}    
        if (table[tmphash].cnt == 0) {continue;} 
        else if (sameCheck(str, strpool + table[tmphash].idx*(len+1), len, shift, table[tmphash].cnt) == 1) {pairs += table[tmphash].cnt;} 
        else {
            sechash = shiftHash(str, len, P2, shift);
            tmphash = (tmphash + sechash) % P;
            if (tmphash < 0) {tmphash += P;}
            while (table[tmphash].cnt > 0 && sameCheck(str, strpool + table[tmphash].idx*(len+1), len, 0, table[tmphash].cnt) == 0) {
                tmphash = (tmphash + sechash) % P;
                if (tmphash < 0) {tmphash += P;}
            } 
            if (table[tmphash].cnt > 0) {pairs += table[tmphash].cnt;}
        }
      }
    } else {
        hash = orgHash(str, len, P);printf("orgHash = %d\n", hash);
        sechash = orgHash(str, len, P2);
        tmphash = hash;
        if (table[hash].cnt == 0) {continue;} 
        else {
          if (sameCheck(str, strpool + table[hash].idx*(len+1), len, 0,  table[hash].cnt) == 1) {            
            table[hash].cnt--; printf("del hash cnt = %d, %d\n", hash, table[hash].cnt);
            pairs -= table[hash].cnt;
          } else {
              tmphash = (tmphash + sechash) % P;
              if (tmphash < 0) {tmphash += P;}
              while (table[tmphash].cnt > 0 && sameCheck(str, strpool + table[tmphash].idx*(len+1), len, 0, table[tmphash].cnt) == 0) {
                tmphash = (tmphash + sechash) % P;
                if (tmphash < 0) {tmphash += P;}
              } 
              if (table[tmphash].cnt == 0) {continue;}
              else {
                table[tmphash].cnt--;printf("del hash cnt = %d, %d\n", hash, table[hash].cnt);
                pairs -= table[tmphash].cnt;
              }
            }
        }

      for (int j = 0; j < len; j++) {
        if (j == 0) {
            tmphash = hash;
            continue;
        }
        shift = j;        
        tmphash = (26*((tmphash-(str[j-1] - 97)*h) % P) + str[j-1] - 97) % P;
        if (tmphash < 0) {tmphash += P;}
        if (tmphash == hash) {break;}    
        if (table[tmphash].cnt == 0) {continue;} 
        else if (sameCheck(str, strpool + table[tmphash].idx*(len+1), len, shift, table[tmphash].cnt) == 1) {pairs -= table[tmphash].cnt; printf("del hash cnt = %d, %d\n", tmphash, table[tmphash].cnt);} 
        else {
            sechash = shiftHash(str, len, P2, shift);
            tmphash = (tmphash + sechash) % P;
            if (tmphash < 0) {tmphash += P;}
            while (table[tmphash].cnt > 0 && sameCheck(str, strpool + table[tmphash].idx*(len+1), len, 0, table[tmphash].cnt) == 0) {
                tmphash = (tmphash + sechash) % P;
                if (tmphash < 0) {tmphash += P;}
            } 
            if (table[tmphash].cnt > 0) {pairs -= table[tmphash].cnt; printf("del hash cnt = %d, %d\n", tmphash, table[tmphash].cnt);}
        }
      }
    }
    printf("ans = %lld\n", pairs);
  }
  
  return 0;
}
