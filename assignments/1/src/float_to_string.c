#include <stdio.h>

#define BUFFER_SIZE 14
#define SINGLE_PRECISION_VALUE 127

size_t float_to_string( float value, char buffer[], size_t buffer_size ){

    // criação de uma união constituida por uma extrutura de 'bit fields' e um float
    typedef union {
    	struct {
    		unsigned int mantissa: 23;
    		unsigned int exponent: 8;
    		unsigned int signal: 1;
    	};
    	float _float;
    } Float_Bit_Fields;

    Float_Bit_Fields float_bit_fields;
    float_bit_fields._float = value;  // passar o float recebido

    int signal = float_bit_fields.signal;
    int exponent = float_bit_fields.exponent - SINGLE_PRECISION_VALUE;
    int normalized_value = (1 << 23) | float_bit_fields.mantissa;  // adicionar o '1,' que falta 

    // DEBUG lines -----------------------------------------------------------------------------
    printf("Signal: %d\n", signal);
    printf("Exponent: %d\n", exponent);
    printf("Normalized Value: %d\n", normalized_value);
    // ------------------------------------------------------------------------------------------

    // parte inteira
    int deslocament = 23 - exponent;
    int integer_part = normalized_value >> deslocament;

    printf("Integer part: %d\n", integer_part);

    // TODO: parte fracionária - NAO ESTA CORRETO #################################################
    float fractional_value = value - (float)integer_part;
    unsigned int fractional_part = (unsigned int) (fractional_value * 1000000);
    printf("Fraction part: %u\n", fractional_part); 

    // escrever sinal no buffer e noramalizar parte inteira se for negativo
    size_t index = 0;
    if (signal) {
    	buffer[index++] = '-';
    	integer_part *= -1;
    } else {
    	buffer[index++] = '+';
    }

    // Escrever parte inteira no buffer
    index += snprintf(buffer + index, buffer_size - index, "%d", integer_part);

    // Escrever ponto decimal e parte fracionária no buffer
    index += snprintf(buffer + index, buffer_size - index, ".%06u", fractional_part);

    // Garantir que o buffer seja nulo-terminado
    buffer[index] = '\0';

    return index;
}

int main(){
	float num = -123.123459;
	char buffer[BUFFER_SIZE];
	printf("The number %f is stored in %ld characters\n\n", num, float_to_string(num, buffer, sizeof(buffer)));

	num = 0.0;
	printf("The number %f is stored in %ld characters\n\n", num, float_to_string(num, buffer, sizeof(buffer)));

	num = 1.1;
	printf("The number %f is stored in %ld characters\n\n", num, float_to_string(num, buffer, sizeof(buffer)));

	num = 123.123456789;
	printf("The number %f is stored in %ld characters\n\n", num, float_to_string(num, buffer, sizeof(buffer)));
	return 0;
}