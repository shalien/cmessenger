//
// Created by Ophélien DUPARC on 11/02/2023.
//

#include <string.h>
#include <time.h>
#include <errno.h>

#include "siren.h"


extern void log_message(const char *file, int line, pid_t pid, const char *format, ...) {
    va_list args;
    va_start(args, format);

    char date_time_str[100];
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    strftime(date_time_str, 100, "%Y-%m-%d %H:%M:%S", timeinfo);

    fprintf(stdout, "[%s][%s:%d][%d] ", date_time_str, file, line, pid);
    vfprintf(stdout, format, args);
    fprintf(stdout, "\n");

    va_end(args);
}

extern void log_error(const char *file, int line, pid_t pid, const char *format, ...) {
    va_list args;
    va_start(args, format);

    char date_time_str[100];
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    strftime(date_time_str, 100, "%Y-%m-%d %H:%M:%S", timeinfo);

    fprintf(stderr, "[%s][%s:%d][%d] ", date_time_str, file, line, pid);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");

    va_end(args);
}

extern void log_error_errno(const char *file, int line, pid_t pid, const char *format, ...) {
    va_list args;
    va_start(args, format);

    char date_time_str[100];
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    strftime(date_time_str, 100, "%Y-%m-%d %H:%M:%S", timeinfo);

    fprintf(stderr, "[%s][%s:%d][%d][%d] %s ", date_time_str, file, line, pid, errno, strerror(errno));
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");

    va_end(args);

}