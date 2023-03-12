//
// Created by Ophélien DUPARC on 12/03/2023.
//

#include <memory.h>
#include "shared_memory_utils.h"


void write_shared_memory(void *data, size_t size, char *shared_memory) {
    memcpy(shared_memory, data, size);
}

void read_shared_memory(void *data, size_t size, char *shared_memory) {
    memcpy(data, shared_memory, size);
}