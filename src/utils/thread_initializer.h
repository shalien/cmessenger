//
// Created by Ophélien DUPARC on 12/03/2023.
//

#ifndef CMESSENGER_THREAD_INITIALIZER_H
#define CMESSENGER_THREAD_INITIALIZER_H

#include <sys/semaphore.h>

struct thread_initialize_st {
    sem_t *thread_semaphore;
    char *shared_memory_pointer;
    sem_t *thread_start_semaphore;
};

#endif //CMESSENGER_THREAD_INITIALIZER_H
