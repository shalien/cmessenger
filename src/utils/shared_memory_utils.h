//
// Created by Ophélien DUPARC on 12/03/2023.
//

#ifndef CMESSENGER_SHARED_MEMORY_UTILS_H
#define CMESSENGER_SHARED_MEMORY_UTILS_H

void write_shared_memory(void *data, size_t size, char *shared_memory);

void read_shared_memory(void *data, size_t size, char *shared_memory);

#endif //CMESSENGER_SHARED_MEMORY_UTILS_H
