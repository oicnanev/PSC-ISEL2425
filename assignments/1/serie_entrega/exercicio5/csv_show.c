/*
 * Função: print_usage
 * -------------------
 * Exibe a mensagem de uso do programa, incluindo as opções disponíveis e os
 * parâmetros esperados.
 *
 * Parâmetros:
 *  - Nenhum.
 *
 * Retorna:
 *  - void: Esta função não retorna valores.
 *
 * Método:
 * 1. Usa a função printf para exibir a mensagem de uso com as opções e
 * parâmetros.
 *
 * ****************************************************************************
 * Função: calculate_max_widths
 * ----------------------------
 * Calcula a largura máxima de cada coluna em um arquivo CSV.
 *
 * Parâmetros:
 *  - FILE *input: o arquivo CSV de entrada.
 *  - int *max_widths: array onde as larguras máximas de cada coluna serão
 * armazenadas.
 *  - int num_fields: número de colunas no CSV.
 *
 * Retorna:
 *  - void: Esta função não retorna valores.
 *
 * Método:
 * 1. Lê cada linha do arquivo CSV.
 * 2. Divide a linha em campos usando strtok.
 * 3. Calcula o comprimento de cada campo e atualiza max_widths se o comprimento
 * for maior que o valor atual.
 * 4. Reposiciona o ponteiro do arquivo para o início.
 *
 * ****************************************************************************
 * Função: print_border
 * --------------------
 * Imprime uma borda para a tabela CSV com base nas larguras máximas das colunas.
 *
 * Parâmetros:
 *  - FILE *output: o arquivo de saída onde a borda será impressa.
 *  - int *max_widths: array com as larguras máximas de cada coluna.
 *  - int num_fields: número de colunas no CSV.
 *
 * Retorna:
 *  - void: Esta função não retorna valores.
 *
 * Método:
 * 1. Itera sobre cada coluna e imprime uma borda com base na largura máxima da
 * coluna.
 * 2. Adiciona um caractere '+' entre as colunas.
 *
 * ****************************************************************************
 * Função: print_csv
 * -----------------
 * Imprime o conteúdo de um arquivo CSV formatado com alinhamento especificado.
 *
 * Parâmetros:
 *  - FILE *input: o arquivo CSV de entrada.
 *  - FILE *output: o arquivo de saída onde o CSV formatado será impresso.
 *  - char alignment: o alinhamento dos campos ('l' para esquerda, 'r' para
 * direita).
 *
 * Retorna:
 *  - void: Esta função não retorna valores.
 *
 * Método:
 * 1. Lê a primeira linha do arquivo CSV para determinar o número de colunas.
 * 2. Calcula a largura máxima de cada coluna.
 * 3. Imprime a borda superior da tabela.
 * 4. Lê cada linha do arquivo CSV e imprime os campos formatados com o
 * alinhamento especificado.
 * 5. Imprime uma borda entre as linhas.
 *
 * ****************************************************************************
 * Função: main
 * ------------
 * Função principal que processa os argumentos da linha de comando e chama as
 * funções apropriadas para imprimir o CSV formatado.
 *
 * Parâmetros:
 *  - int argc: número de argumentos da linha de comando.
 *  - char *argv[]: array de strings contendo os argumentos da linha de comando.
 *
 * Retorna:
 *  - int: código de saída do programa (0 para sucesso, 1 para erro).
 *
 * Método:
 * 1. Processa os argumentos da linha de comando para obter o nome do arquivo de
 * entrada, o nome do arquivo de saída e o alinhamento.
 * 2. Abre o arquivo CSV de entrada.
 * 3. Abre o arquivo de saída, se especificado.
 * 4. Chama a função print_csv para imprimir o CSV formatado.
 * 5. Fecha os arquivos de entrada e saída.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

void print_usage() {
  printf("Usage: ./csv_show [options] <column> <pattern>\n");
  printf("-o <file>\tNome do ficheiros de saída\n");
  printf("-a <alignment>\tAlinhamento: -al : esquerda. -ar : direita\n");;
}


void calculate_max_widths(FILE *input, int *max_widths, int num_fields) {
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), input)) {
        char *token = strtok(line, ",");
        int field_index = 0;
        while (token && field_index < num_fields) {
            int len = strlen(token);
            if (len > max_widths[field_index]) {
                max_widths[field_index] = len;
            }
            token = strtok(NULL, ",");
            field_index++;
        }
    }
    rewind(input);
}

void print_border(FILE *output, int *max_widths, int num_fields) {
    for (int i = 0; i < num_fields; i++) {
        fprintf(output, "+%.*s", max_widths[i] + 2, "---------------------");
    }
    fputs("+\n", output);
}

void print_csv(FILE *input, FILE *output, char alignment) {
    char line[MAX_LINE_LENGTH];
    int num_fields = 0;

    // Ler a primeira linha para determinar o número de campos (células)
    if (fgets(line, sizeof(line), input)) {
        char *token = strtok(line, ",");
        while (token) {
            num_fields++;
            token = strtok(NULL, ",");
        }
    }

    // Calcular o  tamanho maximo para cada coluna
    int max_widths[num_fields];
    memset(max_widths, 0, sizeof(max_widths));
    calculate_max_widths(input, max_widths, num_fields);

    // Print the top border
    print_border(output, max_widths, num_fields);

    // Print the CSV content
    rewind(input);
    while (fgets(line, sizeof(line), input)) {
        // Remove o caractere newline da linha
        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, ",");
        int field_index = 0;
        while (token) {
            char formatted_field[MAX_FIELD_LENGTH];
            int len = strlen(token);
            if (alignment == 'r') {
                int padding = max_widths[field_index] - len;
                for (int i = 0; i < padding; i++) {
                    formatted_field[i] = ' ';
                }
                strcpy(formatted_field + padding, token);
            } else {
                strcpy(formatted_field, token);
                for (int i = len; i < max_widths[field_index]; i++) {
                    formatted_field[i] = ' ';
                }
                formatted_field[max_widths[field_index]] = '\0';
            }
            fprintf(output, "| %*s ", max_widths[field_index], formatted_field);
            token = strtok(NULL, ",");
            field_index++;
        }
        fputs("|\n", output);

        // Print o limite entre linhas
        print_border(output, max_widths, num_fields);
    }
}

int main(int argc, char *argv[]) {
    int opt;
    char *output_filename = NULL;
    char alignment = 'r';
    char *filename = NULL;

    while ((opt = getopt(argc, argv, "o:a:")) != -1) {
        switch (opt) {
        case 'o':
            output_filename = optarg;
            break;
        case 'a':
            alignment = optarg[0];
            break;
        default:
            print_usage();
            return 1;
        }
    }

    if (optind >= argc) {
        print_usage();
        return 1;
    }

    filename = argv[optind];

    char *csv_file_path = getenv("CSV_FILE_PATH");
    char filepath[MAX_LINE_LENGTH];
    if (csv_file_path) {
        snprintf(filepath, sizeof(filepath), "%s/%s", csv_file_path, filename);
    } else {
        snprintf(filepath, sizeof(filepath), "%s", filename);
    }

    FILE *input = fopen(filepath, "r");
    if (!input) {
        perror("Error opening input file");
        return 1;
    }

    FILE *output = stdout;
    if (output_filename) {
        output = fopen(output_filename, "w");
        if (!output) {
            perror("Error opening output file");
            fclose(input);
            return 1;
        }
    }

    // Informação inicial
    printf("Input filename = %s\n", filename);
    printf("Output filename = %s\n", output_filename ? output_filename : "(null)");
    printf("Alinhamento = %s\n\n", alignment == 'l' ? "esquerda" : "direita");


    print_csv(input, output, alignment);

    fclose(input);
    if (output != stdout) {
        fclose(output);
    }

    return 0;
}
