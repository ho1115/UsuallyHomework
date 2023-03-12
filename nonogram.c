#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool rowValid (int** graph, int** r, int rowsToCheck) {
    for (int i = 0; i < rowsToCheck; i++) {
        for (int j = 1; j <= r[i][0]; j++) {
            if (r[i][j]) {return false;}
        }
    }
    return true;
}
bool colValid (int** graph, int** c, int colsToCheck) {
    for (int i = 0; i <= colsToCheck; i++) {
        for (int j = 1; j <= c[i][0]; j++) {
            if (c[i][j]) {return false;}
        }
    }
    return true;
}

bool paint (int** graph, int** r, int** c, int rlen, int clen, int idx) {
    if (idx%clen == 0 && !rowValid(graph, r, idx/clen)) {return false;}
    if (idx == rlen*clen) {
        if (!colValid(graph, c, clen-1)){return false;} 
        for (int i = 0; i < rlen; i++) {
            for (int j = 0; j < clen; j++) {
                if (graph[i][j] < 0) {printf("_");}
                else {printf("o");}
            }printf("\n");        
        }
        return true;
    }    
    else {
        int canWhite = graph[idx/clen][idx%clen] == 2 ? 0 : 1;
        if (graph[idx/clen][idx%clen] >= 0) {
            int rowCursor = 1, colCursor = 1, skip = 0, rightTag = 0;
            if (idx%clen + 1 < clen) {rightTag = graph[idx/clen][idx%clen + 1];}
            while (r[idx/clen][rowCursor] == 0) {rowCursor++;}
            while (c[idx%clen][colCursor] == 0) {colCursor++;}
            if (rowCursor <= r[idx/clen][0] && colCursor <= c[idx%clen][0]) {
                if ((idx%clen + r[idx/clen][rowCursor] <= clen) && (idx/clen + c[idx%clen][colCursor] <= rlen)) {           
                    if (r[idx/clen][rowCursor] == 1 && idx%clen < clen-1) {
                        if (graph[idx/clen][idx%clen + 1] == 2) { 
                            if (idx%clen && graph[idx/clen][idx%clen - 1] == 1) {return false;}
                            else {skip = 1;} 
                        }
                        else {graph[idx/clen][idx%clen + 1] = -2;}
                    } else if (r[idx/clen][rowCursor] > 1) {
                        if (graph[idx/clen][idx%clen + 1] == -2) {
                            if (idx%clen && graph[idx/clen][idx%clen - 1] == 1) {return false;}
                            else {skip = 1;} 
                        }
                        else {graph[idx/clen][idx%clen + 1] = 2;}
                    } 
                    if (!skip) {                  
                        if (c[idx%clen][colCursor] == 1 && idx/clen < rlen-1) {
                            graph[idx/clen + 1][idx%clen] = -2;
                        } else if (c[idx%clen][colCursor] > 1) {
                            graph[idx/clen + 1][idx%clen] = 2;
                        }
                        graph[idx/clen][idx%clen] = 1; 
                        r[idx/clen][rowCursor]--;
                        c[idx%clen][colCursor]--;  
                        if (paint(graph, r, c, rlen, clen, idx+1)) {return true;} 
                        r[idx/clen][rowCursor]++;
                        c[idx%clen][colCursor]++;
                        graph[idx/clen][idx%clen] = 0;
                        if (idx%clen + 1 < clen) {graph[idx/clen][idx%clen + 1] = rightTag;} 
                        if (idx/clen + 1 < rlen) {graph[idx/clen + 1][idx%clen] = 0;}
                        if (idx%clen - 1 >= 0 && graph[idx/clen][idx%clen - 1] == 1) {return false;}
                        if (idx/clen - 1 >= 0 && graph[idx/clen - 1][idx%clen] == 1) {return false;}      
                    }    
                } else {return false;}
            }  
        } 
        if (graph[idx/clen][idx%clen] <= 0 && canWhite) {        
            graph[idx/clen][idx%clen] = -1;
            if (paint(graph, r, c, rlen, clen, idx+1)) {return true;}
        }
        graph[idx/clen][idx%clen] = 0;
        return false;
    }
}

int main() {
    int totalRows, totalCols, temp;
    scanf("%d%d", &totalRows, &totalCols);
    char* buffer = (char*) malloc(26);
    int** rows = (int**) malloc(sizeof(int*) * totalRows);
    int** cols = (int**) malloc(sizeof(int*) * totalCols);
    int** graph = (int**) malloc(sizeof(int*) * totalRows);
    for (int i = 0; i < totalRows; i++) {
        graph[i] = (int*) malloc(sizeof(int) * totalCols);
        for (int j = 0; j < totalCols; j++) {graph[i][j] = 0;}
    }
    for (int i = 0; i < totalRows; i++) {
        scanf("%d", &temp);        
        if (temp) {
            rows[i] = (int*) malloc(sizeof(int) * 25);
            rows[i][0] = temp;
            for (int j = 1; j <= temp; j++) {scanf("%d", &rows[i][j]);}
        }
        else {
            rows[i] = (int*) malloc(sizeof(int));
            rows[i][0] = 0;
        }
    }
    for (int i = 0; i < totalCols; i++) {
        scanf("%d", &temp);        
        if (temp) {
            cols[i] = (int*) malloc(sizeof(int) * 25);
            cols[i][0] = temp;
            for (int j = 1; j <= temp; j++) {scanf("%d", &cols[i][j]);}
        }
        else {
            cols[i] = (int*) malloc(sizeof(int));
            cols[i][0] = 0;
        }
    }
    paint(graph, rows, cols, totalRows, totalCols, 0);
    return 0;
}
