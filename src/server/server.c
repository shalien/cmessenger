//
// Created by Ophélien DUPARC on 09/03/2023.
//

#include <netinet/in.h>
#include "server.h"
#include "../utils/cmesseger_common.h"
#include "../log/siren.h"
#include "../utils/sem_utils.h"
#include "../utils/thread_initializer.h"
#include "../utils/shared_memory_utils.h"
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/semaphore.h>
#include <sys/fcntl.h>


const int server_ports_length = 3;
const int server_ports[] = {3553, 3556, 3559};

sem_t *sem_server, *sem_server_start;
char *shm_server_ptr;

void *init_server(void *arg) {
    //  L("Serveur lancé");

    struct thread_initialize_st *server_initializer = (struct thread_initialize_st *) arg;
    sem_server = server_initializer->thread_semaphore;
    sem_server_start = server_initializer->thread_start_semaphore;
    shm_server_ptr = server_initializer->shared_memory_pointer;

    struct sockaddr_in my_addr;
    struct sockaddr_in remote_address;

    char buffer[CMESSENGER_MAX_LENGHT];

    long size_buffer;

    socklen_t size_server_socket;

    int local_socket, remote_socket;

    local_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (local_socket == -1) {
        EE("Erreur lors de la création du socket");
    }

    int binding;
    int port_index = 0;

    do {

        my_addr.sin_family = AF_INET;
        my_addr.sin_port = htons(server_ports[port_index]);
        my_addr.sin_addr.s_addr = INADDR_ANY;

        binding = bind(local_socket, (const struct sockaddr *) &my_addr, sizeof(struct sockaddr_in));

        port_index++;
    } while (port_index > server_ports_length && binding == -1);

    int local_port = server_ports[port_index];

    write_shared_memory(&local_port, sizeof(local_port), shm_server_ptr);

    sem_post(sem_server_start);


    if (binding == -1) {
        EE("Erreur lors de la réservation du socket");
        exit(EXIT_FAILURE);
    }

    listen(local_socket, 1);

    do {

        remote_socket = accept(local_socket, (struct sockaddr *) &remote_address, &size_server_socket);

        /**
         * Get remote ip
         */
        struct sockaddr_in *remote_ip = (struct sockaddr_in *) &remote_address;
        struct in_addr ip_address = remote_ip->sin_addr;
        char remote_address_buffer[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &ip_address, remote_address_buffer, INET_ADDRSTRLEN);

        read(remote_socket, buffer, CMESSENGER_MAX_LENGHT);

        if (strcmp(buffer, "CMENHELLO") == 0) {
            write(remote_socket, "CMENCLIENT", sizeof("CMENCLIENT"));
        } else {
        }

    } while (strcmp(buffer, ":q") == 0);
}