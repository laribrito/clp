// Larissa de Brito Santos - 202210349

#include <stdio.h>
#include <stdlib.h>

int top, xStr;

void push(char*pilha, const char str){
    top++;
    pilha[top] = str;
}

const char getToken(const char* str){
    return str[xStr++];
}

void pop(){
    top--;
}

const char* pertenceGramatica(const char* str) { 
    top = -1;
    xStr = 0;

    char pilha[10];
    char token;

    q0:
        push(pilha, 'S'); // top++; stack[top] = â€˜Sâ€™;
        token = getToken(str);
    goto q1;

    q1:
        if(token=='a' && pilha[top]=='S' ||
           token=='b' && pilha[top]=='S') { 
            pop(); 
            // "push(aSb)"; 
            push(pilha, 'b');
            push(pilha, 'S');
            push(pilha, 'a');
        } else if (token=='c' && pilha[top]=='S') { pop(); push(pilha, 'c'); }
        else if (token=='a' && pilha[top]=='a') { pop(); token = getToken(str);}
        else if (token=='b' && pilha[top]=='b') { pop(); token = getToken(str);}
        else if (token=='c' && pilha[top]=='c') { pop(); token = getToken(str);}
        else if (token=='\0') { 
            if (top)
                return "pertence";
            return "não pertence"; 
        } else {
            return "não pertence"; 
        }
    goto q1; 
}

int main() {
    FILE *arquivo;
    arquivo = fopen("words.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char palavra[100];
    while (fscanf(arquivo, "%s", palavra) != EOF) {
        printf("%s -> %s\n", palavra, pertenceGramatica(palavra));
    }

    fclose(arquivo);
    return 0;
}