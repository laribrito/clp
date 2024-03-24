// p-code.cpp :  cpp.sh
//
// C conventions
// 0 == FALSE
//
#include <stdio.h>

#define levmax 3
#define amax 2047

enum fct {LIT, OPR, LOD, STO, CAL, INT, JMP, JPC};

typedef struct tinstruction {
     fct    f;
     int    l; // l: 0..levmax; // Level buffer
     int    a; // a: 0..amax;   // Address buffer
}instruction;

instruction code[2048];

//procedure interpret;
// const stacksize = 500;

#define stacksize 5012

 // p, b, t: integer; {program-, base-, topstack-registers}
 int p, // program-register
     b, // base-register
     t; // topstack-register
 
instruction i;            //: instruction; {instruction register}
int         s[stacksize]; //: array [1..stacksize] of integer; {datastore}

int base(int l){ //l: integer)
 int b1; //

 b1 = b; // {find base l levels down}
 while (l > 0) {
    b1 = s[b1];
    l  = l - 1;
 }
 return b1;
}//end-int-base

// Determina se seu argumento é impar
int odd(int x){ return (  ((x%2)==1) ); }

void pcodevhw(){ // begin 
 printf("\n start pl/0");
 printf("\n p   b   t     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14");
 printf("\n === === ===   === === ===             === === === === === === === === === === === === === === ===");
 t = -1; // topstack-register
 b = 0;  // base-register
 p = 0;  // program-register
 
 // OBS: s[0] must not be used
 s[1] = 0; 
 s[2] = 0; 
 s[3] = 0;

 
 do {
  i = code[p]; 
  //printf("\n %3d %3d %3d - %3d %3d %3d", p, b, t, i.f, i.l, i.a);
  printf("\n %3d %3d %3d   ", p, b, t);
  p = p + 1;
 // switch case i.f-BEGIN
  switch  (i.f) { // with i do case f of
    case LIT : { t = t + 1; s[t] = i.a; printf("LIT %3d %3d", i.l, i.a); } break;
    case OPR :
               printf("OPR %3d %3d", i.l, i.a);
//             switch case i.a-BEGIN
               switch (i.a) { // case a of {operator}
                 case  0: { // return
                            t = b - 1; 
                            p = s[t + 3]; 
                            b = s[t + 2];
                          }
                          break;
         
                 case  1: { //
                            s[t] = -s[t];
                          }
                          break;
         
                 case  2: { //  ADD     : PUSH( POP()+POP() )
                            t    = t - 1; 
                            s[t] = s[t] + s[t + 1];
                          }
                          break;
         
                 case  3: { // SUBSTRACT: PUSH( POP()-POP() )
                            t    = t - 1; 
                            s[t] = s[t] - s[t + 1];
                          }
                          break;
         
                 case  4: { // MULTIPLY: PUSH( POP()*POP() )
                            t    = t - 1; 
                            s[t] = s[t] * s[t + 1];
                          }
                          break;
         
                 case  5: { // DIVIDE  : PUSH( POP()/POP() )
                            t    = t - 1; 
                            s[t] = s[t] / s[t + 1];
                          }
                          break;
         
                 case  6: { // 
                            s[t] = odd(s[t]); //s[t] = ord(odd(s[t]));
                          }
                          break;
         
                 case  8: { // EQUAL
                            t    = t - 1; 
                            s[t] = (s[t] == s[t + 1]);
                          }
                          break;
         
                 case  9: { // NOT.EQUAL
                            t    = t - 1; 
                            s[t] = (s[t] != s[t + 1]);
                          }
                          break;
         
                 case 10: { // LESS THAN
                            t    = t - 1; 
                            s[t] = (s[t] < s[t + 1]);
                          }
                          break;
         
                 case 11: { // GREATER EQUAL THAN
                            t    = t - 1; 
                            s[t] = (s[t] >= s[t + 1]);
                          }
                          break;
         
                 case 12: { // GREATER THAN
                            t = t - 1; 
                            s[t] = (s[t] > s[t + 1]);
                          }
                          break;
         
                 case 13: { // LESS EQUAL THAN
                            t    = t - 1; 
                            s[t] = (s[t] <= s[t + 1]);
                          }
                          break;
               } // end;
//         switch case i.a-END
           break;

   case LOD : { // LOAD
                printf("LOD %3d %3d", i.l, i.a);
                t    = t + 1; 
                s[t] = s[base(i.l) + i.a];
              }
              break;

   case STO : { // STORE
                printf("STO %3d %3d", i.l, i.a);
                s[base(i.l)+i.a] = s[t]; 
                t            = t - 1;
              }
              break;

   case CAL :
              { // {generate new block mark}
                printf("CAL %3d %3d", i.l, i.a);
                s[t + 1] = base(i.l); 
                s[t + 2] = b; 
                s[t + 3] = p;
                b        = t + 1; 
                p        = i.a;
              }
              break;

   case INT : t = t + i.a;printf("INT %3d %3d", i.l, i.a); break;
   case JMP : p = i.a;    printf("JMP %3d %3d", i.l, i.a); break;
   case JPC : if (s[t] != 0) { p = i.a; }  t = t - 1; printf("JPC %3d %3d", i.l, i.a); break;
  } // end {with, case}
  // switch case i.f-END
  
  // print stack
  printf("      s[] : ");
  for (int h=0; h<=t; h++) { printf(" %3d", s[h]); }

  scanf("%*c");
 } while ( p != 0 );

 printf("\n === === ===   === === ===             === === === === === === === === === === === === === === ==="); 
 printf("\n p   b   t     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14");
 printf("\n end pl/0");
}//end-void-pcmachine() {interpret};

int main(){
    int pCode = 0;

    code[pCode].f = JMP; code[pCode].l = 0; code[pCode].a = 17; pCode++;     // 00. aponta para o main
    code[pCode].f = JMP; code[pCode].l = 0; code[pCode].a = 3; pCode++;      // 01. aponta para a função de soma
    code[pCode].f = JMP; code[pCode].l = 0; code[pCode].a = 10; pCode++;      // 02. aponta para a função de multiplicação

    code[pCode].f = INT; code[pCode].l = 0; code[pCode].a = 6; pCode++;      // 03. [função soma] reserva o espaço das tres variáveis obrigatórias, dois parametros, e o retorno
    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 3; pCode++;     // 04. empilha o primeiro parametro
    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 4; pCode++;     // 05. empilha o segundo parametro
    code[pCode].f = OPR; code[pCode].l = 0; code[pCode].a = 2; pCode++;      // 06. operação de soma
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 5; pCode++;      // 07. coloca o resultado no local de valor de retorno
    code[pCode].f = STO; code[pCode].l = 1; code[pCode].a = 7; pCode++;      // 08. retorna o resultado para o AR anterior
    code[pCode].f = OPR; code[pCode].l = 0; code[pCode].a = 0; pCode++;      // 09. [return soma]

    code[pCode].f = INT; code[pCode].l = 0; code[pCode].a = 6; pCode++;      // 10. [função multiplicação] reserva o espaço das tres variáveis obrigatórias, dois parametros, e o retorno
    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 3; pCode++;     // 11. empilha o primeiro parametro
    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 4; pCode++;     // 12. empilha o segundo parametro
    code[pCode].f = OPR; code[pCode].l = 0; code[pCode].a = 4; pCode++;      // 13. operação de multiplicação
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 5; pCode++;      // 14. coloca o resultado no local de valor de retorno
    code[pCode].f = STO; code[pCode].l = 1; code[pCode].a = 7; pCode++;      // 15. retorna o resultado para o AR anterior
    code[pCode].f = OPR; code[pCode].l = 0; code[pCode].a = 0; pCode++;      // 16. [return multiplicação]

    code[pCode].f = INT; code[pCode].l = 0; code[pCode].a = 10; pCode++;     // 17. [função main]
    code[pCode].f = LIT; code[pCode].l = 0; code[pCode].a = 1; pCode++;      // 20. valor da variável 'a'
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 3; pCode++;      // 21. posição da variável 'a'

    code[pCode].f = LIT; code[pCode].l = 0; code[pCode].a = 2; pCode++;      // 22. valor da variável 'b'
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 4; pCode++;      // 23. posição da variável 'b'

    code[pCode].f = LIT; code[pCode].l = 0; code[pCode].a = 3; pCode++;      // 24. valor da variável 'c'
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 5; pCode++;      // 25. posição da variável 'c'

    code[pCode].f = LIT; code[pCode].l = 0; code[pCode].a = 4; pCode++;      // 26. valor da variável 'x'
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 6; pCode++;      // 27. posição da variável 'x'

    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 6; pCode++;      // 28. traz o primeiro parâmetro
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 13; pCode++;     // 29. carrega o primeiro parâmetro
    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 6; pCode++;      // 28. traz o segundo parâmetro
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 14; pCode++;     // 29. carrega o segundo parâmetro
    code[pCode].f = CAL; code[pCode].l = 0; code[pCode].a = 2; pCode++;      // 30. chama função [multiplicação] (x*x)
    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 7; pCode++;      // 31. empilha o resultado
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 8; pCode++;      // 32. guarda na posição devida

    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 8; pCode++;      // 33. traz o primeiro parâmetro
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 13; pCode++;     // 34. carrega o primeiro parâmetro
    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 3; pCode++;      // 35. traz o segundo parâmetro
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 14; pCode++;     // 36. carrega o segundo parâmetro
    code[pCode].f = CAL; code[pCode].l = 0; code[pCode].a = 2; pCode++;      // 37. chama função [multiplicação] (x²*a)
    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 7; pCode++;      // 38. empilha o resultado
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 8; pCode++;      // 39. guarda na posição devida

    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 4; pCode++;      // 40. traz o primeiro parâmetro
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 13; pCode++;     // 41. carrega o primeiro parâmetro
    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 6; pCode++;      // 42. traz o segundo parâmetro
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 14; pCode++;     // 43. carrega o segundo parâmetro
    code[pCode].f = CAL; code[pCode].l = 0; code[pCode].a = 2; pCode++;      // 44. chama função [multiplicação] (b*x)
    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 7; pCode++;      // 45. empilha o resultado
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 9; pCode++;      // 46. guarda na posição devida

    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 5; pCode++;      // 47. traz o primeiro parâmetro
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 13; pCode++;     // 48. carrega o primeiro parâmetro
    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 9; pCode++;      // 49. traz o segundo parâmetro
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 14; pCode++;     // 50. carrega o segundo parâmetro
    code[pCode].f = CAL; code[pCode].l = 0; code[pCode].a = 1; pCode++;      // 51. chama função [soma] (c + bx)
    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 7; pCode++;      // 52. empilha o resultado
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 9; pCode++;      // 53. guarda na posição devida

    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 8; pCode++;      // 54. traz o primeiro parâmetro
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 13; pCode++;     // 55. carrega o primeiro parâmetro
    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 9; pCode++;      // 56. traz o segundo parâmetro
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 14; pCode++;     // 57. carrega o segundo parâmetro
    code[pCode].f = CAL; code[pCode].l = 0; code[pCode].a = 1; pCode++;      // 58. chama função [soma]
    code[pCode].f = LOD; code[pCode].l = 0; code[pCode].a = 7; pCode++;      // 59. empilha o resultado
    code[pCode].f = STO; code[pCode].l = 0; code[pCode].a = 9; pCode++;      // 60. guarda na posição devida

    code[pCode].f = OPR; code[pCode].l = 0; code[pCode].a = 0; pCode++;      // [FIM]






	// Aqui vc chama a P-code machine para interpretar essas instrucoes
	pcodevhw();
	return 0;
}