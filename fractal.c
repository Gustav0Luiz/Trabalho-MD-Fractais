#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// funciona ate 4 iteraçoes, mas fica muito grande a string

// Função para redimensionar a memória dinamicamente
char* reallocMemory(char* array, size_t* current_size) {
    *current_size *= 2; // Dobra o tamanho atual
    char* new_array = (char*)realloc(array, *current_size);
    if (!new_array) {
        fprintf(stderr, "Erro ao redimensionar a memória.\n");
        free(array); // Libera memória anterior
        exit(EXIT_FAILURE);
    }
    return new_array;
}

// Floco de neve onda quadrada de von Koch
void firstFractal(int iterations) {
    // Variáveis
    char axioma = 'F';
    char regras[] = "F-F+F+FF-F-F+F";
    size_t tamanho_inicial = 10000; // Tamanho inicial da memória
    size_t tamanho_atual = tamanho_inicial;

    // Alocação dinâmica
    char* fractal_atual = (char*)malloc(tamanho_atual);
    char* proximo_fractal = (char*)malloc(tamanho_atual);
    if (!fractal_atual || !proximo_fractal) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }

    // Inicializações
    fractal_atual[0] = axioma;
    fractal_atual[1] = '\0';

    int tamanho_regras = strlen(regras);

    // Loop com todas as iterações
    for (int i = 0; i < iterations; i++) {
        int posicao = 0; // Índice para inserir no próximo fractal
        int tamanho_atual_string = strlen(fractal_atual);

        for (int k = 0; k < tamanho_atual_string; k++) {
            if (posicao + tamanho_regras >= tamanho_atual - 1) {
                // Redimensiona se necessário
                proximo_fractal = reallocMemory(proximo_fractal, &tamanho_atual);
            }

            if (fractal_atual[k] == axioma) {
                for (int l = 0; l < tamanho_regras; l++) {
                    proximo_fractal[posicao++] = regras[l];
                }
            } else {
                proximo_fractal[posicao++] = fractal_atual[k];
            }
        }

        proximo_fractal[posicao] = '\0'; // Finaliza a string

        // Redimensiona fractal_atual, se necessário
        if (posicao >= tamanho_atual - 1) {
            fractal_atual = reallocMemory(fractal_atual, &tamanho_atual);
        }
        strcpy(fractal_atual, proximo_fractal);
    }

    // Escreve o fractal no arquivo
    FILE* file = fopen("i.txt", "w");
    if (file) {
        fprintf(file, "%s", fractal_atual);
        fclose(file);
    } else {
        fprintf(stderr, "Erro ao abrir o arquivo 'i.txt'.\n");
    }

    // Libera memória alocada
    free(fractal_atual);
    free(proximo_fractal);
}

// Preenchimento de espaço de Hilbert
void secondFractal(int iterations) {
    // Variáveis
    char axioma = 'X';
    char regras_X[] = "-YF+XFX+FY-";
    char regras_Y[] = "+XF-YFY-FX+";
    size_t tamanho_inicial = 10000; // Tamanho inicial da memória
    size_t tamanho_atual = tamanho_inicial;

    // Alocação dinâmica
    char* fractal_atual = (char*)malloc(tamanho_atual);
    char* proximo_fractal = (char*)malloc(tamanho_atual);
    if (!fractal_atual || !proximo_fractal) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }

    // Inicializações
    fractal_atual[0] = axioma;
    fractal_atual[1] = '\0';

    // Loop com todas as iterações
    for (int i = 0; i < iterations; i++) {
        int posicao = 0;
        int tamanho_atual_string = strlen(fractal_atual);

        for (int k = 0; k < tamanho_atual_string; k++) {
            if (posicao + strlen(regras_X) >= tamanho_atual - 1 || posicao + strlen(regras_Y) >= tamanho_atual - 1) {
                proximo_fractal = reallocMemory(proximo_fractal, &tamanho_atual);
            }

            if (fractal_atual[k] == 'X') {
                for (int l = 0; l < strlen(regras_X); l++) {
                    proximo_fractal[posicao++] = regras_X[l];
                }
            } else if (fractal_atual[k] == 'Y') {
                for (int l = 0; l < strlen(regras_Y); l++) {
                    proximo_fractal[posicao++] = regras_Y[l];
                }
            } else {
                proximo_fractal[posicao++] = fractal_atual[k];
            }
        }

        proximo_fractal[posicao] = '\0'; // Finaliza a string

        // Redimensiona fractal_atual, se necessário
        if (posicao >= tamanho_atual - 1) {
            fractal_atual = reallocMemory(fractal_atual, &tamanho_atual);
        }
        strcpy(fractal_atual, proximo_fractal);
    }

    // Remove os símbolos X e Y
    int posicao_final = 0;
    for (int i = 0; i < strlen(proximo_fractal); i++) {
        if (proximo_fractal[i] != 'X' && proximo_fractal[i] != 'Y') {
            proximo_fractal[posicao_final++] = proximo_fractal[i];
        }
    }
    proximo_fractal[posicao_final] = '\0'; // Finaliza a string

    // Escreve o fractal no arquivo
    FILE* file = fopen("ii.txt", "w");
    if (file) {
        fprintf(file, "%s", proximo_fractal);
        fclose(file);
    } else {
        fprintf(stderr, "Erro ao abrir o arquivo 'ii.txt'.\n");
    }

    // Libera memória alocada
    free(fractal_atual);
    free(proximo_fractal);
}

// Função principal
int main() {
    int iterations;
    scanf("%d", &iterations);
    firstFractal(iterations);
    secondFractal(iterations);
    return 0;
}
