#include <stdio.h>

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
  size_t index = 0;

  const char *week_day[] = {"Domingo", "Segunda", "Terça", "Quarta",
                            "Quinta",  "Sexta",   "Sábado"};

  index += snprintf(buffer + index, buffer_size - index,
                    "%s, %02d-%02d-%d %02d:%02d:%02d", week_day[tm->tm_wday],
                    tm->tm_mday, tm->tm_mon, tm->tm_year + 1900, tm->tm_hour,
                    tm->tm_min, tm->tm_sec);
  return index;
}
