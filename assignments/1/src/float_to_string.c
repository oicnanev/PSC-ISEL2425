#include <stdio.h>

#define BUFFER_SIZE 14

size_t float_to_string( float value, char buffer[], size_t buffer_size ){
	//const char *digits = "0123456789";

	// Multiplica o 'value' por 1 000 000 para lidar com as 6 casas decimais necessárias.
	// Usa-se long long para garantir portabilidade entre tecnologias, long long será sempre 64 bits
	long long int_value = (long long)(value * 1000000);

	// se negativo, tornalo positivo
	int is_negative = int_value < 0;
	if (is_negative){
		int_value = -int_value;
	} 

	// separar a parte inteira e a parte fracionaria
	long long int_part = int_value / 1000000;
	long long frac_part = int_value % 1000000;


	// construção da string --------------------------------------------------
	int pos = 0;
	if (is_negative) {
		buffer[pos++] = '-';
	}

	// parte inteira
    char int_str[20];
    sprintf(int_str, "%lld", int_part);
    for (size_t i = 0; int_str[i] != '\0'; ++i) {
        if (pos < buffer_size - 1) {
            buffer[pos++] = int_str[i];
        }
    }

    // ponto (separador)
    buffer[pos++] = '.';

    // parte fracionária
    char frac_str[7];
    sprintf(frac_str, "%06lld", frac_part);
    for (size_t i = 0; frac_str[i] != '\0'; ++i) {
        if (pos < buffer_size - 1) {
            buffer[pos++] = frac_str[i];
        }
    }

    // Adiciona o caractere nulo final
    if (pos < buffer_size) {
        buffer[pos] = '\0';
    } else {
        buffer[buffer_size - 1] = '\0';
    }

    // Retorna o número de caracteres escritos
    return pos;	
}

int main(){
	float num = -123.123456;
	char buffer[BUFFER_SIZE];
	printf("The number %f is stored in %ld characters\n", num, float_to_string(num, buffer, sizeof(buffer)));
	return 0;
}
