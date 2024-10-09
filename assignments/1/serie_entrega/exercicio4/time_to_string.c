/*
 * Função: time_to_string
 * ----------------------
 * Converte uma estrutura de tempo (struct tm) para uma string formatada e 
 * armazena o resultado no buffer fornecido.
 *
 * Parâmetros:
 *  - struct tm *tm: ponteiro para a estrutura de tempo a ser convertida.
 *  - char *buffer: o array de caracteres onde a string resultante será armazenada.
 *  - size_t buffer_size: o tamanho do array buffer.
 *
 * Retorna:
 *  - size_t: o comprimento da string produzida. Retorna 0 se o buffer for insuficiente.
 *
 * Método:
 * 1. Calcula o tamanho necessário do buffer para armazenar a string formatada.
 * 2. Verifica se o buffer fornecido é suficiente para armazenar a string resultante.
 * 3. Escreve o dia da semana no buffer.
 * 4. Adiciona a vírgula e o espaço.
 * 5. Escreve o dia do mês no buffer.
 * 6. Adiciona o hífen.
 * 7. Escreve o mês no buffer.
 * 8. Adiciona o hífen.
 * 9. Escreve o ano no buffer.
 * 10. Adiciona a vírgula e o espaço.
 * 11. Escreve a hora no buffer.
 * 12. Adiciona os dois pontos.
 * 13. Escreve os minutos no buffer.
 * 14. Adiciona os dois pontos.
 * 15. Escreve os segundos no buffer.
 * 16. Adiciona o caractere nulo ('\0') ao final da string no buffer.
 *
 * Autor:
 * 45824 Nuno Venâncio
 */


#include <stdio.h>
#include <string.h>

struct tm {
    int tm_sec;   // seconds after the minute - [0, 60] including leap second
    int tm_min;   // minutes after the hour - [0, 59]
    int tm_hour;  // hours since midnight - [0, 23]
    int tm_mday;  // day of the month - [1, 31]
    int tm_mon;   // months since January - [0, 11]
    int tm_year;  // years since 1900
    int tm_wday;  // days since Sunday - [0, 6]
    int tm_yday;  // days since January 1 - [0, 365]
    int tm_isdst; // daylight saving time flag
};

size_t time_to_string(struct tm *tm, char *buffer, size_t buffer_size) {
    const char *week_day[] = {"domingo", "segunda-feira", "terça-feira", "quarta-feira",
                              "quinta-feira", "sexta-feira", "sábado"};

    // Calcular o buffer size necessario
    size_t required_size = 0;
    required_size += strlen(week_day[tm->tm_wday]) + 2; // dia da semana + virgula + espaço
    required_size += 2 + 1; // Dia do mês (2 digitos) + traço
    required_size += 2 + 1; // Mês (2 digitos) + traço
    required_size += 4 + 2; // Ano (4 digitos) + virgula + espaço
    required_size += 2 + 1; // Hora (2 digitos) + dois pontos
    required_size += 2 + 1; // Minutos (2 digitos) + dois pontos
    required_size += 2 + 1; // Segundos (2 digitos) + null terminator

    size_t index = 0;

    // Ver se o buffer é sufficiente
    if (buffer_size < required_size) {
        return index;
    }

    // Escrever dia da semana
    const char *day = week_day[tm->tm_wday];
    while (*day && index < buffer_size - 1) {
        buffer[index++] = *day++;
    }

    // Escrever virgula e espaço
    if (index < buffer_size - 1) buffer[index++] = ',';
    if (index < buffer_size - 1) buffer[index++] = ' ';

    // Escrever dia do mês
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_mday / 10) + '0';
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_mday % 10) + '0';

    // Escrever o '-'
    if (index < buffer_size - 1) buffer[index++] = '-';

    // Escrever o mês
    if (index < buffer_size - 1) buffer[index++] = ((tm->tm_mon + 1) / 10) + '0';
    if (index < buffer_size - 1) buffer[index++] = ((tm->tm_mon + 1) % 10) + '0';

    // Escrever '-'
    if (index < buffer_size - 1) buffer[index++] = '-';

    // Escrever o ano
    int year = tm->tm_year + 1900;
    if (index < buffer_size - 1) buffer[index++] = (year / 1000) + '0';
    if (index < buffer_size - 1) buffer[index++] = ((year / 100) % 10) + '0';
    if (index < buffer_size - 1) buffer[index++] = ((year / 10) % 10) + '0';
    if (index < buffer_size - 1) buffer[index++] = (year % 10) + '0';

    // Escrever virgula e espaço
    if (index < buffer_size - 1) buffer[index++] = ',';
    if (index < buffer_size - 1) buffer[index++] = ' ';

    // Escrever hora
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_hour / 10) + '0';
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_hour % 10) + '0';

    // Escrever dois pontos
    if (index < buffer_size - 1) buffer[index++] = ':';

    // Escrever o minuto
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_min / 10) + '0';
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_min % 10) + '0';

    // Escrever os dois pontos
    if (index < buffer_size - 1) buffer[index++] = ':';

    // Escrever os segundos
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_sec / 10) + '0';
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_sec % 10) + '0';

    // Terminar com o caracter terminador '\0'
    if (index < buffer_size) buffer[index] = '\0';

    return index;
}
