#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

void print_usage() {
  printf("Usage: ./csv_show [-o outputfile] [-a alignment] filename\n");
}

void print_csv(FILE *input, FILE *output, char alignment) {
  char line[MAX_LINE_LENGTH];
  char *fields[MAX_FIELD_LENGTH];
  int num_fields = 0;

  // Read the first line to determine the number of fields
  if (fgets(line, sizeof(line), input)) {
    char *token = strtok(line, ",");
    while (token) {
      fields[num_fields++] = token;
      token = strtok(NULL, ",");
    }
  }

  // Print the top border
  for (int i = 0; i < num_fields; i++) {
    fprintf(output, "+----------------");
  }
  fprintf(output, "+\n");

  // Print the CSV content
  rewind(input);
  while (fgets(line, sizeof(line), input)) {
    char *token = strtok(line, ",");
    int field_index = 0;
    while (token) {
      if (alignment == 'r') {
        fprintf(output, "| %14s ", token);
      } else {
        fprintf(output, "| %-14s ", token);
      }
      token = strtok(NULL, ",");
      field_index++;
    }
    fprintf(output, "|\n");

    // Print the border between rows
    for (int i = 0; i < num_fields; i++) {
      fprintf(output, "+----------------");
    }
    fprintf(output, "+\n");
  }
}

int main(int argc, char *argv[]) {
  int opt;
  char *output_filename = NULL;
  char alignment = 'l';
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

  print_csv(input, output, alignment);

  fclose(input);
  if (output != stdout) {
    fclose(output);
  }

  return 0;
}
