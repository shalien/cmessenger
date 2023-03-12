//
// Created by Ophélien DUPARC on 11/02/2023.
//

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>

#ifndef BATTLESHIP_SIREN_H
#define BATTLESHIP_SIREN_H

#define L(format, ...) log_message(__FILE_NAME__, __LINE__, getpid(), format, ##__VA_ARGS__)

#define E(format, ...) log_error(__FILE_NAME__, __LINE__, getpid(), format, ##__VA_ARGS__)

#define EE(format, ...) log_error_errno(__FILE_NAME__, __LINE__, getpid(), format, ##__VA_ARGS__)

/**
 * Logging function
 *
 * @param content the text content to print
 * @param ... the formatted data
 */
extern void log_message(const char *file, int line, pid_t pid, const char *format, ...);

extern void log_error(const char *file, int line, pid_t pid, const char *format, ...);

extern void log_error_errno(const char *file, int line, pid_t pid, const char *format, ...);

#endif //BATTLESHIP_SIREN_H
