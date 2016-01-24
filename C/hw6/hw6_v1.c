#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void rnd_array(int *[], int, int);
void prt_array(int *[], int, int);

int main(int argc, char *argv[]){
    
    //TEST
    argv[1] = "c";
    argv[2] = "50";
    argv[3] = "4";
    
    int m = atoi(argv[2]), n = atoi(argv[3]);    
    int *a[m], *b[n], *c[m];
    int i, j, k;

    srand(time(NULL));
    rnd_array(a, m, n);
    rnd_array(b, n, m);
    
    printf("A:\n");
    prt_array(a, m, n);
    printf("B:\n");
    prt_array(b, n, m);
    
    for(i = 0; i < m; i++){
        
        c[i] = calloc(m, sizeof(int));
        assert(c[i] != NULL);
    
        for(j = 0; j < m; j++){
            c[i][j] = 0;
            for(k = 0; k < n; k++)
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
        }
    }
        
    printf("C:\n");
    prt_array(c, m, m);

    system("pause");
    return 0;
}

void rnd_array(int *array[], int m, int n){
     
    int i, j;
       
    for(i = 0; i < m; i++){
        
        array[i] = calloc(n, sizeof(int));
        assert(array[i] != NULL);
        
        for(j = 0; j < n; j++){
            array[i][j] = rand() % 19 - 9;
        }
    }

    return;
}

void prt_array(int *array[], int m, int n){
     
    int i, j;

    //printf("¢z");
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            printf("%5d", array[i][j]);
        }
        putchar('\n');
        //printf("%s", (i == 0 ? "¢{\n¢x" : (i == m - 2 ? "¢x\n¢|" : (i == m - 1 ? "¢}\n" : "¢x\n¢x"))));
    }
    putchar('\n');

    return;
}
