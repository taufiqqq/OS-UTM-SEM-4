#include <stdio.h>
#include <pthread.h>

typedef struct {
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t condition;
} semaphore;

void init_semaphore(semaphore* sem, int initial_value) {
    sem->value = initial_value;
    pthread_mutex_init(&sem->mutex, NULL);
    pthread_cond_init(&sem->condition, NULL);
}

void wait(semaphore* sem) {
    pthread_mutex_lock(&sem->mutex);
    while (sem->value <= 0) {
        printf("Waiting for previous process to end\n");
        pthread_cond_wait(&sem->condition, &sem->mutex);
    }
    sem->value--;
    pthread_mutex_unlock(&sem->mutex);
}

void signal(semaphore* sem) {
    pthread_mutex_lock(&sem->mutex);
    sem->value++;
    pthread_cond_signal(&sem->condition);
    pthread_mutex_unlock(&sem->mutex);
}

// Example usage

semaphore mutex;

void* thread_function(void* arg) {
    int id = *(int*)arg;
    
    wait(&mutex);
    printf("\nThread %d is entering the critical section.\n", id);
    // Critical section
    printf("Thread %d is leaving the critical section.\n", id);
    signal(&mutex);
    
    return NULL;
}

int main() {
    printf("Semaphore presentation OS-6\n");
    pthread_t threads[5];
    int thread_ids[5] = {1, 2, 3, 4, 5};

    init_semaphore(&mutex, 1);

    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

system("PAUSE");
    return 0;
}
