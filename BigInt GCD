#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int divByTwo (int* big, int len) {
    big[0] = big[0] / 2;
    for (int i = 1; i <= len; i++) {
        if (big[i] % 2) {big[i-1] += 5;}
        big[i] = big[i] / 2;
    }
    if (len) {return big[len] == 0 ? len - 1 : len;}
    else {return 0;}
}

int sub (int* n, int* m, int lenn, int lenm) {    
    for (int i = 0; i <= lenn; i++) {
        m[i] -= n[i];
        if (m[i] < 0 && i+1 <= lenm) {
            m[i] += 10;                         
            int ptr = i+1;                   
            while(m[ptr] == 0) {             
                m[ptr] = 9;                                    
                ptr++;
            }
            m[ptr]--;
        }
    }
    while (m[lenm] == 0 && lenm) {lenm--;}
    return lenm;
}

int comp (int* a, int* b, int lena, int lenb) {
    if (lena > lenb) {return 0;}
    else if (lenb > lena) {return 1;}
    else {
        int idx = lena;
        while (idx != -1) {
            if (a[idx] == b[idx]) {idx--;}
            else {return a[idx] > b[idx] ? 0 : 1;}
        }
        return 2;
    }
    // 0 = a > b, 1 = b > a, 2 = a == b;
}

void sqr (int* n, int lenn, int times) {
    while (times) {
        int temp = 0;
        for (int i = 0; i <= lenn; i++) {
            n[i] *= 2;
            if (temp) {
                n[i] += temp;
                temp = 0;
            }
            if (n[i] > 9) {
                temp = n[i] / 10;
                n[i] %= 10;
            }
        }
        if (temp) {
            lenn++;
            n[lenn] = temp;
        }
        times--;
    } 
    for (int i = lenn; i >= 0; i--) {printf("%d", n[i]);}

}

void BinAlgo(int* n, int* m, int lenn, int lenm) {
    int ans = 0, loop = 0;
    while(n[lenn] != 0 && m[lenm] != 0) {        
        if (n[0] % 2 == 0 && m[0] % 2 == 0) {
            ans++; 
            lenn = divByTwo(n, lenn);
            lenm = divByTwo(m, lenm);          
        } else if (n[0] % 2 == 0) {lenn = divByTwo(n, lenn);}
        else if (m[0] % 2 == 0) {lenm =  divByTwo(m, lenm);}
        if (comp(n, m, lenn, lenm) == 0) {
            int temp = lenn;
            lenn = lenm;
            lenm = temp;
            int* ptr = n;
            n = m;
            m = ptr;
        }
        lenm = sub(n, m, lenn, lenm);
        loop++;
    }    
    sqr(n, lenn, ans);
}

void store (int* a, char* str, int len) {
    int idx = 0;
    while (str[idx] != 0) {        
        a[len - idx] = str[idx] - 48;
        idx++;
    }
}

int main () {
    int* a;
    int* b;
    char temp[1024];

    scanf("%s", temp);
    int lenOfA = strlen(temp) - 1;
    a = (int*) malloc((lenOfA + 1) * sizeof(int));
    store(a, temp, lenOfA);
    
    scanf("%s", temp);    
    int lenOfB = strlen(temp) - 1;
    b = (int*) malloc((lenOfB + 1) * sizeof(int));    
    store(b, temp, lenOfB);
    
    int max = comp(a, b, lenOfA, lenOfB);   
    if (max == 2) {for (int i = lenOfA; i >= 0; i--) {printf("%d", a[i]);}}
    else if (max == 1) {BinAlgo(a, b, lenOfA, lenOfB);}
    else {BinAlgo(b, a, lenOfB, lenOfA);}
    return 0;
}
