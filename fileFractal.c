#include <stdio.h>
#include <stdlib.h>

// gcc -o filefractal fileFractal.c -lm

// ainda esta dando erro para iteration = 0,
// A forma recursiva escrevendo e lendo arquivos
// é bem mais leve do que armazenar uma string de 200000 caracteres em uma variavel.
// portanto precisa ajustar o codigo para ela.
// falta fazer para o fractal 2 e o 3, e ajustar o 1.



// Constantes para o axioma e regras
#define AXIOMA 'F'
#define REGRAS "F-F+F+FF-F-F+F"
#define ARQUIVO_FINAL "i.txt"

// Função para gerar o fractal
void firstFractal(int iterations) {
    // Caso especial para 0 iterações
    if (iterations == 0) {
        // Abre o arquivo final no modo "w" para sobrescrever qualquer conteúdo existente
        FILE* file = fopen(ARQUIVO_FINAL, "w");
        if (!file) {
            fprintf(stderr, "Erro: Não foi possível criar o arquivo '%s'.\n", ARQUIVO_FINAL);
            exit(EXIT_FAILURE);
        }
        fprintf(file, "%c", AXIOMA);
        fclose(file);
        printf("Fractal gerado com 0 iterações salvo em '%s'.\n", ARQUIVO_FINAL);
        return;
    }

    // Nomes dos arquivos temporários
    const char* arquivo_atual = "temp1.txt";
    const char* arquivo_proximo = "temp2.txt";

    // Grava o axioma inicial no arquivo inicial
    FILE* file = fopen(arquivo_atual, "w");
    if (!file) {
        fprintf(stderr, "Erro: Não foi possível criar o arquivo '%s'.\n", arquivo_atual);
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%c", AXIOMA);
    fclose(file);

    // Loop para as iterações
    for (int i = 0; i < iterations; i++) {
        // Abre os arquivos
        FILE* input_file = fopen(arquivo_atual, "r");
        if (!input_file) {
            fprintf(stderr, "Erro: Não foi possível abrir o arquivo '%s' para leitura.\n", arquivo_atual);
            exit(EXIT_FAILURE);
        }

        FILE* output_file = fopen(arquivo_proximo, "w");
        if (!output_file) {
            fprintf(stderr, "Erro: Não foi possível criar o arquivo '%s' para escrita.\n", arquivo_proximo);
            fclose(input_file);
            exit(EXIT_FAILURE);
        }

        // Substitui os caracteres conforme as regras
        char c;
        while ((c = fgetc(input_file)) != EOF) {
            if (c == AXIOMA) {
                fprintf(output_file, "%s", REGRAS);
            } else {
                fputc(c, output_file);
            }
        }

        fclose(input_file);
        fclose(output_file);

        // Troca os arquivos
        const char* temp = arquivo_atual;
        arquivo_atual = arquivo_proximo;
        arquivo_proximo = temp;
    }

    // Garante que o arquivo final seja sobrescrito
    FILE* final_file = fopen(ARQUIVO_FINAL, "w");
    if (!final_file) {
        fprintf(stderr, "Erro: Não foi possível criar o arquivo final '%s'.\n", ARQUIVO_FINAL);
        exit(EXIT_FAILURE);
    }

    FILE* result_file = fopen(arquivo_atual, "r");
    if (!result_file) {
        fprintf(stderr, "Erro: Não foi possível abrir o arquivo '%s' para leitura do resultado final.\n", arquivo_atual);
        fclose(final_file);
        exit(EXIT_FAILURE);
    }

    // Transfere o conteúdo do arquivo de resultado para o arquivo final
    char c;
    while ((c = fgetc(result_file)) != EOF) {
        fputc(c, final_file);
    }

    fclose(result_file);
    fclose(final_file);

    // Remove os arquivos temporários
    remove(arquivo_atual);
    remove(arquivo_proximo);

    printf("Fractal gerado com %d iterações salvo em '%s'.\n", iterations, ARQUIVO_FINAL);
}

int main() {
    int iterations;
    printf("Digite o número de iterações: ");
    if (scanf("%d", &iterations) != 1 || iterations < 0) {
        fprintf(stderr, "Erro: Entrada inválida. Por favor, insira um número inteiro não negativo.\n");
        return EXIT_FAILURE;
    }

    firstFractal(iterations);

    return EXIT_SUCCESS;
}
