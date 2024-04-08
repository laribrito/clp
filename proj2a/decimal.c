// Larissa de Brito Santos - 202210349

#include <stdio.h>
#include <stdlib.h>

const char* ehDecimal(const char* str) { 
    const char* retorno = NULL;
    
    for (int c = 0; str[c] != '\0'; c++) {
        if (str[c] != '0' 
         && str[c] != '1'
         && str[c] != '2'
         && str[c] != '3'
         && str[c] != '4'
         && str[c] != '5'
         && str[c] != '6'
         && str[c] != '7'
         && str[c] != '8'
         && str[c] != '9') {
            retorno = "rejeitada";
        }
    }
    if (!retorno) 
        retorno = "reconhecida";

    return retorno;
}

int main() {
    FILE *arquivo;
    arquivo = fopen("in_decimal.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char palavra[100];
    while (fscanf(arquivo, "%s", palavra) != EOF) {
        printf("%s -> %s\n", palavra, ehDecimal(palavra));
    }

    fclose(arquivo);
    return 0;
}