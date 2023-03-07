#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    int totalRows, totalCols;
    scanf("%d%d", &totalRows, &totalCols);
    char* buffer = (char*) malloc(26);
    int** rows = (int**) malloc(sizeof(int*) * totalRows);
    int** cols = (int**) malloc(sizeof(int*) * totalCols);
    int** graph = (int**) malloc(sizeof(int*) * totalRows);
    for (int i = 0; i < totalRows; i++) {
        graph[i] = (int*) malloc(sizeof(int) * totalCols);
        for (int j = 0; j < totalCols; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < totalRows; i++) {
        fgets(buffer, 26, stdin);
        if (buffer[0] == 48) {
            rows[0] = (int*) malloc(sizeof(int));
            rows[0][0] = 0;
        }
        else {
            rows[0] = (int*) malloc(sizeof(int) * 25);
            for (int j = 0; j < strlen(buffer); j++) {

            }
        }
    }
    
    return 0;

}
