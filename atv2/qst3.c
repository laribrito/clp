#include <stdio.h>

#define levmax 3
#define amax 2047
#define stacksize 500
#define numShowStack 7

// instruções
typedef enum {
    lit, opr, lod, sto, cal, intt, jmp, jpc
} fct;

// uma instrução
typedef struct {
    fct f;
    int l;
    int a;
} instruction;

// código atual
instruction code[] = {
    {intt, 0, 3},  // 1.  separa 3 espaços na memoria para as variáveis obrigatórias
    {lit, 0, 0},   // 2.  coloca 0 em 'somador'
    {intt, 0, 1},  // 3.  separa espaço para 'quadrado'
    {lit, 0, 101}, // 4.  coloca max+1 em 'x'
    {lit, 0, 1},   // 5.  coloca 1 em 'passo'
    {opr, 0, 3},   // 6.  subtração de 'x' por 'passo'
    {sto, 0, 5},   // 7.  copiar o conteúdo de 'x' para 'quadrado'
    {intt, 0, 1},  // 8.  aponta t para 'x'
    {opr, 0, 4},   // 9.  faz a multiplicação
    {intt, 0, 1},  // 10.  aponta t para 'x', de novo
    {opr, 0, 4},   // 11.  faz a multiplicação, de novo
    {opr, 0, 2},   // 12.  adiciona ao 'somador'
    {intt, 0, 2},  // 13.  retorna para 'x'
    {jpc, 0, 16},  // 14.  quando der falso, o programa é enviado ao fim
    {intt, 0, 2},  // 15.  retorna para 'passo'
    {jmp, 0, 5},   // 16. loop para linha 6
    {opr, 0, 0},   // 17. FIM
};

void inicializaPilha(int pilha[]){
    for (int i = 1; i <= numShowStack; i++){
        pilha[i]=0;
    }
}

void exibePilha(int pilha[]){
    for(int x=1; x<=numShowStack; x++){
        printf("%4d   ", pilha[x]);
    }
    printf("\n");
}

void salvaPilha(FILE *arq, int pilha[]){
    for(int x=1; x<=numShowStack; x++){
        fprintf(arq, "%d ", pilha[x]);
    }
    fprintf(arq, "\n");
}

void interpret() {
    int stack[stacksize]; 
    int p = 0, b = 0, t = 0; // linha do programa, base, topo da pilha
    instruction inst;

    // Inicialização da pilha
    inicializaPilha(stack);

    printf("valores iniciais              p      b      t      stack\n");
    printf("                           %4d   %4d   %4d   ", p, b, t);
    exibePilha(stack);
    printf("\n");

    printf("codigo                        p      b      t      stack\n");
    FILE *arq = fopen("dadosQst1.csv","w");
    fprintf(arq, "codigo, p, b, t, stack\n");
    do {
        // próxima instrução
        inst = code[p++];


        switch (inst.f) {
            case lit:
                // Empilha um valor no topo da pilha
                printf(" lit  ");
                fprintf(arq, "lit");
                t++;
                stack[t] = inst.a;
                break;
            case opr:
                printf(" opr  ");
                fprintf(arq, "opr");
                // Operações aritméticas e lógicas
                switch (inst.a) {
                    case 0:
                        // return
                        t = b;
                        p = stack[t + 3];
                        b = stack[t + 2];
                        break;
                    case 1:
                        // negativo 
                        stack[t] = -stack[t];
                        break;
                    case 2:
                        // printf("soma");
                        t--;
                        stack[t] += stack[t + 1];
                        break;
                    case 3:
                        // printf("subtração");
                        t--;
                        stack[t] -= stack[t + 1];
                        break;
                    case 4:
                        // printf("multiplicação");
                        t--;
                        stack[t] *= stack[t + 1];
                        break;
                    case 5:
                        // printf("divisão");
                        t--;
                        stack[t] /= stack[t + 1];
                        break;
                    case 6:
                        // printf("paridade");
                        stack[t] = stack[t] % 2;
                        break;
                    case 8:
                        // printf("igualdade");
                        t--;
                        stack[t] = (stack[t] == stack[t + 1]);
                        break;
                    case 9:
                        // printf("desigualdade");
                        t--;
                        stack[t] = (stack[t] != stack[t + 1]);
                        break;
                    case 10:
                        // printf("menor que");
                        t--;
                        stack[t] = (stack[t] < stack[t + 1]);
                        break;
                    case 11:
                        // printf("maior ou igual");
                        t--;
                        stack[t] = (stack[t] >= stack[t + 1]);
                        break;
                    case 12:
                        // printf("maior que");
                        t--;
                        stack[t] = (stack[t] > stack[t + 1]);
                        break;
                    case 13:
                        // printf("menor ou igual a");
                        t--;
                        stack[t] = (stack[t] <= stack[t + 1]);
                        break;
                }
                break;
            case lod:
                printf(" lod  ");
                fprintf(arq, "lod");
                // valor da memória para a pilha
                t++;
                stack[t] = stack[b + inst.a];
                break;
            case sto:
                printf(" sto  ");
                fprintf(arq, "sto");
                // valor da pilha na memória
                stack[b + inst.a] = stack[t];
                t--;
                break;
            case cal:
                printf(" cal  ");
                fprintf(arq, "cal");
                // chama uma função
                stack[t + 1] = b;
                stack[t + 2] = p;
                stack[t + 3] = b;
                b = t + 1;
                p = inst.a;
                break;
            case intt:
                printf("intt  ");
                fprintf(arq, "intt");
                // Incrementa o topo da pilha por um valor
                t += inst.a;
                break;
            case jmp:
                printf(" jmp  ");
                fprintf(arq, "jmp");
                // Salto incondicional para uma posição na memória
                p = inst.a;
                break;
            case jpc:
                printf(" jpc  ");
                fprintf(arq, "jpc");
                // Salto condicional se o topo da pilha for zero
                if (stack[t] == 0) {
                    p = inst.a;
                }
                t--;
                break;
        }

        printf("%2d %2d", inst.l, inst.a);
        printf("                ");
        printf("%4d   %4d   %4d   ", p, b, t);
        exibePilha(stack);

        fprintf(arq, " %d %d, %d, %d, %d, ", inst.l, inst.a, p, b, t);
        salvaPilha(arq, stack);
        
    } while (p != 0);

    printf("end pl/0\n");
    fclose(arq);
}

int main() {
    printf("start pl/0\n");
    interpret();
    return 0;
}
