#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define NUM_VECTORS 1024
#define REPET 1024

void insertSort(int vector[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = vector[i];
        int j = i - 1;

        while (j >= 0 && vector[j] > chave) {
            vector[j + 1] = vector[j--];
        }
        vector[j + 1] = chave;
    }
}

void randomVectorInt(int vector[], int n) {
    for (int i = 0; i < n; i++) {
        vector[i] = rand() % 1000;  // Números aleatórios entre 0 e 999
    }
}

int main() {
    int qtd = REPET;
    clock_t start, end;
    double cpu_time_used;

    FILE *arquivo = fopen("temposEmC.txt", "w");

    while(qtd--){
        int numVectors = NUM_VECTORS;
        start = clock();
        while(numVectors--){
            int vector[SIZE];
            randomVectorInt(vector, SIZE);
            insertSort(vector, SIZE);
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        fprintf(arquivo, "%f\n", cpu_time_used);
    }
    fclose(arquivo);

    return 0;
}
