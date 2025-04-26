// بسم الله الرحمن الرحيم
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lockA, lockB;

void* thread1(void* arg) {
    printf("thread 1 trying to acquire lock A ..\n");
    pthread_mutex_lock(&lockA);
    printf("thread 1 acquired lock A \n");

    sleep(3);

    printf("thread 1 trying to acquire lock B ..\n");
    pthread_mutex_lock(&lockB);
    printf("thread 1 acquired lock B \n");

    printf("thread 1 in critical section\n");

    pthread_mutex_unlock(&lockB);
    pthread_mutex_unlock(&lockA);
}

void* thread2(void* arg) {
    printf("thread 2 trying to acquire lock B ..\n");
    pthread_mutex_lock(&lockB);
    printf("thread 2 acquired lock B \n");

    sleep(3);

    printf("thread 2 trying to acquire lock A ..\n");
    pthread_mutex_lock(&lockA);
    printf("thread 2 acquired lock A \n");

    printf("thread 2: In critical section\n");

    pthread_mutex_unlock(&lockA);
    pthread_mutex_unlock(&lockB);
}

int main() {
    pthread_t tid1, tid2;
    pthread_mutex_init(&lockA, NULL);
    pthread_mutex_init(&lockB, NULL);

    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}
