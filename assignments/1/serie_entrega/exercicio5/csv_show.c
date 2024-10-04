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

    // Read the first line to determine the number of fields
    if (fgets(line, sizeof(line), input)) {
        char *token = strtok(line, ",");
        while (token) {
            num_fields++;
            token = strtok(NULL, ",");
        }
    }

    // Calculate the maximum width for each column
    int max_widths[num_fields];
    memset(max_widths, 0, sizeof(max_widths));
    calculate_max_widths(input, max_widths, num_fields);

    // Print the top border
    print_border(output, max_widths, num_fields);

    // Print the CSV content
    rewind(input);
    while (fgets(line, sizeof(line), input)) {
        // Remove the newline character from the line
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

        // Print the border between rows
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

    // Print the initial information
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
