// Larissa de Brito Santos - 202210349

#include <stdio.h>
#include <stdlib.h>

const char* ehBinario(const char* str) { 
    const char* retorno = NULL;
    for (int c = 0; str[c] != '\0'; c++) {
        if (str[c] != '0' && str[c] != '1') {
            retorno = "rejeitada";
        }
    }
    if (!retorno) 
        retorno = "reconhecida";

    return retorno;
}

int main() {
    FILE *arquivo;
    arquivo = fopen("in_binario.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char palavra[100];
    while (fscanf(arquivo, "%s", palavra) != EOF) {
        printf("%s -> %s\n", palavra, ehBinario(palavra));
    }

    fclose(arquivo);
    return 0;
}