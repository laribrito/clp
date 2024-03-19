#include <stdio.h>

#define levmax 3
#define amax 2047
#define stacksize 500

// Enumeração para as funções de instrução
typedef enum {
    lit, opr, lod, sto, cal, intt, jmp, jpc
} fct;

// Estrutura para representar uma instrução
typedef struct {
    fct f;
    int l;
    int a;
} instruction;

// Array de instruções
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
    {opr, 0, 2},   // 10.  adiciona ao 'somador'
    {intt, 0, 2},  // 11.  retorna para 'x'
    {jpc, 0, 14},  // 12.  quando der falso, o programa é enviado ao fim
    {intt, 0, 2},  // 13.  retorna para 'passo'
    {jmp, 0, 5},   // 14. loop para linha 6
    {opr, 0, 0},   // 15. FIM
};

// Função para interpretar e executar as instruções
void interpret() {
    int stack[stacksize]; // Pilha de execução
    int p = 0, b = 0, t = 0; // Contador de programa, base, topo da pilha
    instruction inst; // Instrução atual

    // Inicialização da pilha
    stack[1] = stack[2] = stack[3] = 0;

    // Loop principal
    do {
        // Obtém a próxima instrução
        inst = code[p++];

        printf("------------------------Antes---------------------------\n");
        printf("p: %d\n", p);
        printf("b: %d\n", b);
        printf("t: %d\n", t);
        printf("stack: ");
        for (int x=1; x<=10; x++) printf("%d ", stack[x]);
        printf("\n========================================================\n");

        // Switch para lidar com diferentes funções de instrução
        switch (inst.f) {
            case lit:
                // Empilha um valor no topo da pilha
                t++;
                stack[t] = inst.a;
                break;
            case opr:
                // Operações aritméticas e lógicas
                switch (inst.a) {
                    case 0:
                        // Retorna de uma chamada de procedimento
                        t = b;
                        p = stack[t + 3];
                        b = stack[t + 2];
                        break;
                    case 1:
                        // Negativo
                        stack[t] = -stack[t];
                        break;
                    case 2:
                        // Adição
                        t--;
                        stack[t] += stack[t + 1];
                        break;
                    case 3:
                        // Subtração
                        t--;
                        stack[t] -= stack[t + 1];
                        break;
                    case 4:
                        // Multiplicação
                        t--;
                        stack[t] *= stack[t + 1];
                        break;
                    case 5:
                        // Divisão
                        t--;
                        stack[t] /= stack[t + 1];
                        break;
                    case 6:
                        // Módulo 2 (verifica se é ímpar)
                        stack[t] = stack[t] % 2;
                        break;
                    case 8:
                        // Igualdade
                        t--;
                        stack[t] = (stack[t] == stack[t + 1]);
                        break;
                    case 9:
                        // Desigualdade
                        t--;
                        stack[t] = (stack[t] != stack[t + 1]);
                        break;
                    case 10:
                        // Menor que
                        t--;
                        stack[t] = (stack[t] < stack[t + 1]);
                        break;
                    case 11:
                        // Maior ou igual a
                        t--;
                        stack[t] = (stack[t] >= stack[t + 1]);
                        break;
                    case 12:
                        // Maior que
                        t--;
                        stack[t] = (stack[t] > stack[t + 1]);
                        break;
                    case 13:
                        // Menor ou igual a
                        t--;
                        stack[t] = (stack[t] <= stack[t + 1]);
                        break;
                }
                break;
            case lod:
                // Carrega um valor da memória para a pilha
                t++;
                stack[t] = stack[b + inst.a];
                break;
            case sto:
                // Armazena um valor da pilha na memória
                stack[b + inst.a] = stack[t];
                t--;
                break;
            case cal:
                // Chama um procedimento, gerando um novo bloco de execução
                stack[t + 1] = b;
                stack[t + 2] = p;
                stack[t + 3] = b;
                b = t + 1;
                p = inst.a;
                break;
            case intt:
                // Incrementa o topo da pilha por um valor
                t += inst.a;
                break;
            case jmp:
                // Salto incondicional para uma posição na memória
                p = inst.a;
                break;
            case jpc:
                // Salto condicional se o topo da pilha for zero
                if (stack[t] == 0) {
                    p = inst.a;
                }
                t--;
                break;
        }

        printf("-----------------------Depois---------------------------\n");
        printf("p: %d\n", p);
        printf("b: %d\n", b);
        printf("t: %d\n", t);
        printf("stack: ");
        for (int x=1; x<=10; x++) printf("%d ", stack[x]);
        printf("\n--------------------------------------------------------\n");
        // scanf("%*c");
    } while (p != 0);

    printf("end pl/0\n");
}

// Função principal
int main() {
    printf("start pl/0\n");
    interpret();
    return 0;
}
