
#include <pthread.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <sys/semaphore.h>
#include <sys/fcntl.h>
#include "log/siren.h"
#include "utils/cmesseger_common.h"
#include "server/server.h"
#include "client/client.h"
#include "utils/sem_utils.h"
#include "utils/thread_initializer.h"
#include "utils/shared_memory_utils.h"

pthread_t server_thread, client_thread;
int shmid_server, shmid_client;
char *shm_server_ptr, *shm_client_ptr;
sem_t *sem_server, *sem_client, *sem_server_start;

int local_server_port;

int main(int argc, char *argv[]) {
    L("Démarrage de CMessenger %d", getppid());

    L("Démarrage du serveur");

    if ((sem_server = sem_open(get_sem_server(), O_CREAT, 0666, 1)) == SEM_FAILED) {
        EE("Impossible d'initialiser le semaphore server");
        exit(EXIT_FAILURE);
    }

    if ((sem_server_start = sem_open(get_sem_server_start(), O_CREAT, 0666, 0)) == SEM_FAILED) {
        EE("Impossible d'initialiser la synchro du serveur");
        exit(EXIT_FAILURE);
    }

    shmid_server = shmget(IPC_PRIVATE, CMESSENGER_MAX_LENGHT * 2, IPC_CREAT | 0666);
    if (shmid_server < 0) {
        EE("Impossible de créer la mémoire partagée pour le serveur !");
        exit(EXIT_FAILURE);
    }

    shm_server_ptr = shmat(shmid_server, NULL, 0);


    struct thread_initialize_st server_init = {
            sem_server,
            shm_server_ptr,
            sem_server_start
    };


    if (pthread_create(&server_thread, NULL, init_server, (void *) &server_init) > 0) {
        EE("Impossible de créer le thread serveur !");
    }

    L("Démarrage du client");

    shmid_client = shmget(IPC_PRIVATE, CMESSENGER_MAX_LENGHT * 2, IPC_CREAT | 0666);
    if (shmid_client < 0) {
        EE("Impossible de créer la mémoire partagée pour le serveur !");
        exit(EXIT_FAILURE);
    }

    shm_client_ptr = shmat(shmid_client, NULL, 0);

    L("Initialisation du sempahore pour le client");
    if ((sem_client = sem_open(get_sem_client(), O_CREAT, 0666, 1)) == SEM_FAILED) {
        EE("Impossible d'initialiser le semaphore client");
        exit(EXIT_FAILURE);
    }
    sem_wait(sem_client);

    struct thread_initialize_st client_init = {
            sem_client,
            shm_client_ptr
    };


    if (pthread_create(&client_thread, NULL, init_client, (void *) &client_init) > 0) {
        EE("Impossible de créer le thread client !");
        exit(EXIT_FAILURE);
    }

    char buffer[CMESSENGER_MAX_LENGHT];
    char name_buffer[CMESSENGER_MAX_LENGHT];
    char remote_address[CMESSENGER_MAX_LENGHT];
    int port = 0;

    do {

        sem_wait(sem_server_start);
        sem_wait(sem_server);

        read_shared_memory(&port, sizeof(port), shm_server_ptr);

        sem_post(sem_server);

    } while (port == 0);
    L("Server démarré sur le port %d", port);


    sem_close(sem_server_start);

    do {

        printf("\nBienvenu, entrer votre nom ? ");
        scanf("%s", name_buffer);

    } while (strlen(name_buffer) <= 0);

    do {
        do {

            printf("\nBonjour %s, pouvez vous me donner l'adresse de la personne que vous voulez joindre ? ",
                   name_buffer);
            scanf("%s", remote_address);
        } while (strlen(remote_address) <= 0);

        do {
            printf("\nBien et maintenant, j'ai besoin du port : ");
            scanf("%d", &port);
        } while (port <= 0);

        printf("\nMerci, tentative de connexion à %s:%d", remote_address, port);

        int length = snprintf(NULL, 0, "%s\n%d", remote_address, port);
        char *message = (char *) malloc(length + 1);

        snprintf(message, length + 1, "%s\n%d", remote_address, port);

        write_shared_memory(message, sizeof(message), shm_client_ptr);

        sem_post(sem_client);

    } while (1);

    do {

        printf("%s# : ", name_buffer);
        scanf("%s", buffer);
    } while (strcmp(buffer, ":q") == 0);

    shmdt(shm_client_ptr);
    shmdt(shm_server_ptr);

    shmctl(shmid_client, IPC_RMID, NULL);
    shmctl(shmid_server, IPC_RMID, NULL);

    pthread_join(server_thread, NULL);
    pthread_join(client_thread, NULL);

    exit(EXIT_SUCCESS);
}
