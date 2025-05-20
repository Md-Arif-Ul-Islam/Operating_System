#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;
int readcount = 0;
pthread_mutex_t mutex;

void *writer(void *arg) {
    sem_wait(&wrt);
    printf("Writer is writing...\n");
    sleep(1);
    printf("Writer finished writing.\n");
    sem_post(&wrt);
    return NULL;
}
void *reader(void *arg) {
    pthread_mutex_lock(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);
    pthread_mutex_unlock(&mutex);
    printf("Reader is reading...\n");
    sleep(1);
    printf("Reader finished reading.\n");

    pthread_mutex_lock(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
int main() {
    pthread_t r1, r2, w1;
    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&r1, NULL, reader, NULL);
    pthread_create(&w1, NULL, writer, NULL);
    pthread_create(&r2, NULL, reader, NULL);

    pthread_join(r1, NULL);
    pthread_join(w1, NULL);
    pthread_join(r2, NULL);

    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);
    return 0;
}
