
#include <stdio.h>
#include <stdlib.h>

// Constantes para o axioma e regras
#define AXIOMA 'F'
#define REGRAS "F-F+F+FF-F-F+F"


// Floco de neve onda quadrada de von Koch

void firstFractal(int iterations){

    char* arquivo_atual = "i.txt";
    char* arquivo_temp = "ti.txt";

    // Grava o axioma inicial em arquivo_atual
    FILE* file = fopen(arquivo_atual, "w");
    if (!file) {
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%c", AXIOMA);
    fclose(file);

    // Loop para as iterações
    for (int i = 0; i < iterations; i++) {

        // Abre os arquivos - lê o atual e escreve no proximo

        FILE* arquivo_leitura = fopen(arquivo_atual, "r");
        if (!arquivo_leitura) {
            exit(EXIT_FAILURE);
        }
        FILE* arquivo_escrita = fopen(arquivo_temp, "w");
        if (!arquivo_escrita) {
            fclose(arquivo_leitura);
            exit(EXIT_FAILURE);
        }

        // Substitui os caracteres conforme as regras
        char c;
        while ((c = fgetc(arquivo_leitura)) != EOF) {
            if (c == AXIOMA) {
                fprintf(arquivo_escrita, "%s", REGRAS);
            } else {
                fputc(c, arquivo_escrita);
            }
        }

        fclose(arquivo_leitura);
        fclose(arquivo_escrita);

        remove(arquivo_atual);                   
        rename(arquivo_temp, arquivo_atual);

    }

}

// Preenchimento de espaço de Hilbert

#define AXIOMA2 'X'
#define REGRAS_X "-YF+XFX+FY-"
#define REGRAS_Y "+XF-YFY-FX+"

void secondFractal(int iterations) {

    char* arquivo_atual_2 = "ii.txt";
    char* arquivo_temp_2 = "tii.txt";

    // Grava o axioma inicial em arquivo_atual
    FILE* file = fopen(arquivo_atual_2, "w");
    if (!file) {
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%c", AXIOMA2);
    fclose(file);

    // Loop para as iterações
    for (int i = 0; i < iterations; i++) {

        // Abre os arquivos - lê o atual e escreve no proximo

        FILE* arquivo_leitura_2 = fopen(arquivo_atual_2, "r");
        if (!arquivo_leitura_2) {
            exit(EXIT_FAILURE);
        }
        FILE* arquivo_escrita_2 = fopen(arquivo_temp_2, "w");
        if (!arquivo_escrita_2) {
            fclose(arquivo_leitura_2);
            exit(EXIT_FAILURE);
        }

        // Substitui os caracteres conforme as regras
        char c;
        while ((c = fgetc(arquivo_leitura_2)) != EOF) {
            if (c == 'X') {
                fprintf(arquivo_escrita_2, "%s", REGRAS_X);
            }            
            else if (c == 'Y') {
                fprintf(arquivo_escrita_2, "%s", REGRAS_Y);
            }
             else {
                fputc(c, arquivo_escrita_2);
            }
        }
        
        fclose(arquivo_leitura_2);
        fclose(arquivo_escrita_2);
    
        remove(arquivo_atual_2);                   
        rename(arquivo_temp_2, arquivo_atual_2);

    }

    // Remoção de caracteres X e Y no arquivo final
    FILE* arquivo_leitura_final = fopen(arquivo_atual_2, "r");
    if (!arquivo_leitura_final) {
        exit(EXIT_FAILURE);
    }
    FILE* arquivo_escrita_final = fopen(arquivo_temp_2, "w");
    if (!arquivo_escrita_final) {
        fclose(arquivo_leitura_final);
        exit(EXIT_FAILURE);
    }

// Filtra os caracteres X e Y
    char c;
    while ((c = fgetc(arquivo_leitura_final)) != EOF) {
        if (c != 'X' && c != 'Y') {
            fputc(c, arquivo_escrita_final);
        }
    }

    fclose(arquivo_leitura_final);
    fclose(arquivo_escrita_final);

    // Substitui o arquivo original pelo filtrado
    remove(arquivo_atual_2);
    rename(arquivo_temp_2, arquivo_atual_2);
}

// Fractal de Sierpiński arrowhead curve L-system

#define AXIOMA3 'X'
#define REGRAS_X3 "Y-X-Y"
#define REGRAS_Y3 "X+Y+X"

void thirdFractal(int iterations) {

    char* arquivo_atual_3 = "iii.txt";
    char* arquivo_temp_3 = "tiii.txt";

    // Grava o axioma inicial em arquivo_atual
    FILE* file = fopen(arquivo_atual_3, "w");
    if (!file) {
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%c", AXIOMA3);
    fclose(file);

    // Loop para as iterações
    for (int i = 0; i < iterations; i++) {

        // Abre os arquivos - lê o atual e escreve no proximo

        FILE* arquivo_leitura_3 = fopen(arquivo_atual_3, "r");
        if (!arquivo_leitura_3) {
            exit(EXIT_FAILURE);
        }
        FILE* arquivo_escrita_3 = fopen(arquivo_temp_3, "w");
        if (!arquivo_escrita_3) {
            fclose(arquivo_leitura_3);
            exit(EXIT_FAILURE);
        }

        // Substitui os caracteres conforme as regras
        char c;
        while ((c = fgetc(arquivo_leitura_3)) != EOF) {
            if (c == 'X') {
                fprintf(arquivo_escrita_3, "%s", REGRAS_X3);
            }            
            else if (c == 'Y') {
                fprintf(arquivo_escrita_3, "%s", REGRAS_Y3);
            }
             else {
                fputc(c, arquivo_escrita_3);
            }
        }
        
        fclose(arquivo_leitura_3);
        fclose(arquivo_escrita_3);
    
        remove(arquivo_atual_3);                   
        rename(arquivo_temp_3, arquivo_atual_3);

    }

    // Remoção de caracteres X e Y no arquivo final
    FILE* arquivo_leitura_final = fopen(arquivo_atual_3, "r");
    if (!arquivo_leitura_final) {
        exit(EXIT_FAILURE);
    }
    FILE* arquivo_escrita_final = fopen(arquivo_temp_3, "w");
    if (!arquivo_escrita_final) {
        fclose(arquivo_leitura_final);
        exit(EXIT_FAILURE);
    }

// Transforma X e Y em F
    char c;
    while ((c = fgetc(arquivo_leitura_final)) != EOF) {
        if (c == 'X' || c == 'Y') {
            fputc('F', arquivo_escrita_final);
        }
        else {fputc(c, arquivo_escrita_final);}
    }

    fclose(arquivo_leitura_final);
    fclose(arquivo_escrita_final);

    // Substitui o arquivo original pelo filtrado
    remove(arquivo_atual_3);
    rename(arquivo_temp_3, arquivo_atual_3);
}

int main() {
    int iterations;
    scanf("%d", &iterations);
    firstFractal(iterations);
    secondFractal(iterations);
    thirdFractal(iterations);
    return 0;
}
