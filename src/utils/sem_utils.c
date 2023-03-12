//
// Created by Ophélien DUPARC on 09/03/2023.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "sem_utils.h"
#include "cmesseger_common.h"

char *get_sem_server() {
    char buffer[CMESSENGER_MAX_LENGHT];
    char *result = malloc(strlen(buffer) + 1);
    sprintf(buffer, "/sem_server_%d", getppid());

    strcpy(result, buffer);
    return result;
}

char *get_sem_server_start() {
    char buffer[CMESSENGER_MAX_LENGHT];
    char *result = malloc(strlen(buffer) + 1);
    sprintf(buffer, "/sem_server_start_%d", getppid());

    strcpy(result, buffer);
    return result;
}

char *get_sem_client() {
    char buffer[CMESSENGER_MAX_LENGHT];
    char *result = malloc(strlen(buffer) + 1);
    sprintf(buffer, "/sem_client_%d", getppid());

    strcpy(result, buffer);
    return result;
}