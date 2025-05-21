#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers

enum { THINKING, HUNGRY, EATING } state[N];

sem_t mutex;           // Global mutex for synchronization
sem_t S[N];            // One semaphore per philosopher

void test(int i) {
    if (state[i] == HUNGRY &&
        state[(i + 4) % N] != EATING &&
        state[(i + 1) % N] != EATING) {
        
        state[i] = EATING;
        sleep(1);
        printf("Philosopher %d takes forks %d and %d\n", i + 1, (i + 4) % N + 1, (i + 1) % N + 1);
        printf("Philosopher %d is Eating\n", i + 1);
        sem_post(&S[i]);
    }
}

void take_forks(int i) {
    sem_wait(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is Hungry\n", i + 1);
    test(i);
    sem_post(&mutex);
    sem_wait(&S[i]);
}

void put_forks(int i) {
    sem_wait(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d puts down forks %d and %d\n", i + 1, (i + 4) % N + 1, (i + 1) % N + 1);
    printf("Philosopher %d is Thinking\n", i + 1);
    test((i + 4) % N); // Test left neighbor
    test((i + 1) % N); // Test right neighbor
    sem_post(&mutex);
}

void* philosopher(void* num) {
    int i = *(int*)num;

    while (1) {
        sleep(1);
        take_forks(i);
        sleep(2); // Eating time
        put_forks(i);
    }
}

int main() {
    int i;
    pthread_t thread_id[N];
    int phil[N];

    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++) {
        sem_init(&S[i], 0, 0);
        phil[i] = i;
    }

    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is Thinking\n", i + 1);
    }

    for (i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}
