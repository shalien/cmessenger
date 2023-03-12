//
// Created by Ophélien DUPARC on 09/03/2023.
//
#include <netinet/in.h>
#include <printf.h>
#include <unistd.h>
#include <string.h>
#include <sys/semaphore.h>
#include "client.h"
#include "../log/siren.h"
#include "../utils/cmesseger_common.h"
#include "../utils/thread_initializer.h"
#include "../utils/shared_memory_utils.h"

char remote_address;
int remote_port;
char buffer[CMESSENGER_MAX_LENGHT];

sem_t *sem_client;
char *shm_client_ptr;

void *init_client(void *arg) {

    L("Client lancé !");

    struct thread_initialize_st *client_initializer = (struct thread_initialize_st *) arg;
    sem_client = client_initializer->thread_semaphore;
    shm_client_ptr = client_initializer->shared_memory_pointer;

    struct sockaddr_in remote_socket;
    int local_socket = socket(AF_INET, SOCK_STREAM, 0);

    int connected;

    do {

        sem_wait(sem_client);
        char *data[CMESSENGER_MAX_LENGHT * 2];

        read_shared_memory(&data, sizeof(data), shm_client_ptr);

        L(data);

    } while (strlen(&remote_address) <= 0 && remote_port <= 0);

    do {


        /*
        remote_socket.sin_family = AF_INET;
      //  remote_socket.sin_port = htons(CMESSENGER_SERVER_PORT);
        inet_aton(remote_host, &remote_socket.sin_addr);

        connected = connect(local_socket, (const struct sockaddr *) &remote_socket, sizeof(remote_socket));

        if(connected == 0) {
            write(local_socket, "CMENHELLO", sizeof("CMENHELLO"));

            read(local_socket, buffer, sizeof(buffer));

            if(strcmp(buffer, "CMENCLIENT")) {

            }

        } else {
            EE("Impossible de ce connecter");
        }
*/
    } while (connected == -1);
}