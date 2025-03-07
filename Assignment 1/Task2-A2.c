//Raed Alsheikh Amin 2528271
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 5

int array[N];

void *child_thread(void *arg) {
    printf("Updating the values of the array elements:\n");
    for (int i = 0; i < N; i++)
        array[i] = 462;

    pthread_exit(NULL);
}

int main() {
    pthread_t tid;

    // initialize array
    for (int i = 0; i < N; i++)
        array[i] = 334;

    printf("The values of the array elements:\n");
    for (int i = 0; i < N; i++)
        printf("%d\n", array[i]);

    // create child thread
    if (pthread_create(&tid, NULL, child_thread, NULL) != 0) {
        fprintf(stderr, "error while  creating thread\n");
        return 1;
    }

    // wait for child thread to finish
    if (pthread_join(tid, NULL) != 0) {
        fprintf(stderr, "error while joining thread\n");
        return 1;
    }

    printf("The values of the array elements again:\n");
    for (int i = 0; i < N; i++)
        printf("%d\n", array[i]);

    return 0;
}
