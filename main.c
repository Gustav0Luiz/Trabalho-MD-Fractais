#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char axioma;
    int angulo;
    char regras[100];
    int iterations;    
    char fractal_atual[10000]; 
    char proximo_fractal[10000];
   

    printf("Digite o AXIOMA: ");
    scanf(" %c ", &axioma);

    printf("Digite o ANGULO (graus): ");
    scanf("%d", &angulo);

    printf("Digite as Regras: %c->",axioma);
    scanf("%s", regras);

    printf("Digite o Numero de iteracoes: %d: ");
    scanf("%d", &iterations);

    fractal_atual[0] = axioma; 
    proximo_fractal[0] = "\0";


    int tamanho_regras = strlen(regras);
    int tamanho_atual  = strlen(fractal_atual);
    int tamanho_proximo = strlen(proximo_fractal);

    // loop com todas as iteracoes
    for(int i = 0; i<iterations; i++){
        printf("Estagio: %d \n", i+1);

        // printa o fractal
        for(int i = 0; i<tamanho_atual; i++){
            printf("Fractal: %c ", fractal_atual[i]);
        }

        // modifica o fractal atual

        for(int i = 0; i<tamanho_proximo; i++){
            if(fractal_atual[i]==axioma){
                for(int j = 0; j < tamanho_regras; j++){
                    proximo_fractal[j] = regras[j];
                }
            }
        }
    }

    return 0;
}