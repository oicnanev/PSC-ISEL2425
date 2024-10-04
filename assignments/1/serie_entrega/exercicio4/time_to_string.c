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

    // Calculate the required buffer size
    size_t required_size = 0;
    required_size += strlen(week_day[tm->tm_wday]) + 2; // Day of the week + comma + space
    required_size += 2 + 1; // Day of the month (2 digits) + dash
    required_size += 2 + 1; // Month (2 digits) + dash
    required_size += 4 + 2; // Year (4 digits) + comma and space
    required_size += 2 + 1; // Hour (2 digits) + colon
    required_size += 2 + 1; // Minute (2 digits) + colon
    required_size += 2 + 1; // Second (2 digits) + null terminator

    size_t index = 0;

    // Check if the buffer is sufficient
    if (buffer_size < required_size) {
        return index;
    }

    // Write the day of the week
    const char *day = week_day[tm->tm_wday];
    while (*day && index < buffer_size - 1) {
        buffer[index++] = *day++;
    }

    // Write the comma and space
    if (index < buffer_size - 1) buffer[index++] = ',';
    if (index < buffer_size - 1) buffer[index++] = ' ';

    // Write the day of the month
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_mday / 10) + '0';
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_mday % 10) + '0';

    // Write the dash
    if (index < buffer_size - 1) buffer[index++] = '-';

    // Write the month
    if (index < buffer_size - 1) buffer[index++] = ((tm->tm_mon + 1) / 10) + '0';
    if (index < buffer_size - 1) buffer[index++] = ((tm->tm_mon + 1) % 10) + '0';

    // Write the dash
    if (index < buffer_size - 1) buffer[index++] = '-';

    // Write the year
    int year = tm->tm_year + 1900;
    if (index < buffer_size - 1) buffer[index++] = (year / 1000) + '0';
    if (index < buffer_size - 1) buffer[index++] = ((year / 100) % 10) + '0';
    if (index < buffer_size - 1) buffer[index++] = ((year / 10) % 10) + '0';
    if (index < buffer_size - 1) buffer[index++] = (year % 10) + '0';

    // Write the comma and space
    if (index < buffer_size - 1) buffer[index++] = ',';
    if (index < buffer_size - 1) buffer[index++] = ' ';

    // Write the hour
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_hour / 10) + '0';
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_hour % 10) + '0';

    // Write the colon
    if (index < buffer_size - 1) buffer[index++] = ':';

    // Write the minute
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_min / 10) + '0';
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_min % 10) + '0';

    // Write the colon
    if (index < buffer_size - 1) buffer[index++] = ':';

    // Write the second
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_sec / 10) + '0';
    if (index < buffer_size - 1) buffer[index++] = (tm->tm_sec % 10) + '0';

    // Null-terminate the buffer
    if (index < buffer_size) buffer[index] = '\0';

    return index;
}