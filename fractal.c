#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Floco de neve onda quadrada de von Koch
void firstFractal() {
    // Variáveis
    char axioma = 'F';
    char regras[] = "F-F+F+FF-F-F+F";
    int iterations;
    char fractal_atual[10000]; 
    char proximo_fractal[10000];

    // Entrada de dados
    printf("Digite o Numero de iteracoes: ");
    scanf("%d", &iterations);

    // Inicializações
    fractal_atual[0] = axioma; 
    fractal_atual[1] = '\0';  // Terminador de string
    proximo_fractal[0] = '\0';  // Terminador de string inicial

    int tamanho_regras = strlen(regras);

    // Loop com todas as iterações
    for (int i = 0; i < iterations; i++) {
        // Modifica o fractal atual
        int posicao = 0;  // Índice para inserir no proximo_fractal
        int tamanho_atual = strlen(fractal_atual);
        
        for (int k = 0; k < tamanho_atual; k++) {
            if (fractal_atual[k] == axioma) {
                // Substitui o axioma pelas regras
                for (int l = 0; l < tamanho_regras; l++) {
                    proximo_fractal[posicao++] = regras[l];
                }
            } else {
                // Copia o caractere atual
                proximo_fractal[posicao++] = fractal_atual[k];
            }
        }
        proximo_fractal[posicao] = '\0';  // Finaliza a string

        // Atualiza fractal_atual com o próximo fractal
        strcpy(fractal_atual, proximo_fractal);
        proximo_fractal[0] = '\0';  // Reseta o próximo fractal
    }

    // Abre o arquivo "i.txt" para escrita
    FILE *file = fopen("i.txt", "w");
    if (file == NULL) {
        //printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve o fractal gerado no arquivo
    fprintf(file, "%s", fractal_atual);

    // Fecha o arquivo
    fclose(file);

    //printf("Fractal gerado e salvo em 'i.txt'.\n");
}

//Preenchimento de espaço de Hilbert
void secondFractal(){
   
    // Variáveis
    char axioma = 'X'; 
    char regras_X[] = "-YF+XFX+FY-";  // Regra para X
    char regras_Y[] = "+XF-YFY-FX+";  // Regra para Y
    int iterations;
    char fractal_atual[10000];  // Fractal gerado
    char proximo_fractal[10000];  // Próxima geração do fractal

    // Entrada de dados
    printf("Digite o Numero de iteracoes: ");
    scanf("%d", &iterations);

    // Inicializações
    fractal_atual[0] = axioma; 
    fractal_atual[1] = '\0';  // Terminador de string
    proximo_fractal[0] = '\0';  // Terminador de string inicial

    // Loop com todas as iterações
    for (int i = 0; i < iterations; i++) {
        // Modifica o fractal atual
        int posicao = 0;  // Índice para inserir no proximo_fractal
        int tamanho_atual = strlen(fractal_atual);

        for (int k = 0; k < tamanho_atual; k++) {
            if (fractal_atual[k] == 'X') {
                // Substitui o X pela regra correspondente
                for (int l = 0; l < strlen(regras_X); l++) {
                    proximo_fractal[posicao++] = regras_X[l];
                }
            } else if (fractal_atual[k] == 'Y') {
                // Substitui o Y pela regra correspondente
                for (int l = 0; l < strlen(regras_Y); l++) {
                    proximo_fractal[posicao++] = regras_Y[l];
                }
            } else {
                // Copia o caractere atual
                proximo_fractal[posicao++] = fractal_atual[k];
            }
        }
        proximo_fractal[posicao] = '\0';  // Finaliza a string

        // Atualiza fractal_atual com o próximo fractal
        strcpy(fractal_atual, proximo_fractal);
        proximo_fractal[0] = '\0';  // Reseta o próximo fractal
    }

    // Remover os símbolos X e Y
    int posicao_final = 0;
    int tamanho_atual = strlen(fractal_atual);
    for (int i = 0; i < tamanho_atual; i++) {
        if (fractal_atual[i] != 'X' && fractal_atual[i] != 'Y') {
            // Copia apenas os caracteres F, + e -
            proximo_fractal[posicao_final++] = fractal_atual[i];
        }
    }
    proximo_fractal[posicao_final] = '\0';  // Finaliza a string

    // Abre o arquivo "i.txt" para escrita
    FILE *file = fopen("ii.txt", "w");
    if (file == NULL) {
        //printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve o fractal gerado no arquivo
    fprintf(file, "%s", proximo_fractal);

    // Fecha o arquivo
    fclose(file);

    //printf("Fractal gerado e salvo em 'ii.txt'.\n");
}

// Função principal
int main() {
    firstFractal();
    secondFractal();
    return 0;
}
