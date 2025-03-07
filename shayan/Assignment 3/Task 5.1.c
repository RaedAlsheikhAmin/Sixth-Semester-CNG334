//Name: Shayan Nadeem Bhutta
//ID: 2542413

#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 5 
#define MAX_ITEMS 5 //Declared Max Items to be produced (and consumed) as 5 to not make the program loop infinitely.

//Follows the provided Skeleton from the book.

typedef int buffer_item;

buffer_item buffer[BUFFER_SIZE];
int count = 0; //To keep track of numbers of items currently present in the buffer.
int in = 0;  //To keep track of location of next item to be inserted (produced)
int out = 0; //To keep track of location of next item to be removed (consumed_

pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;

int insert_item(buffer_item item) {
    pthread_mutex_lock(&mutex);
    
    // Wait if buffer is full
    while (count == BUFFER_SIZE) {
        pthread_cond_wait(&empty, &mutex);
    }
    
    // Insert item into buffer
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    count++;
    
    printf("Producer produced item %d\n", item);
    
    // Signal that buffer is no longer empty
    pthread_cond_signal(&full);
    
    pthread_mutex_unlock(&mutex);
    
    return 0;
}

int remove_item(buffer_item *item) {
    pthread_mutex_lock(&mutex);
    
    // Wait if buffer is empty
    while (count == 0) {
        pthread_cond_wait(&full, &mutex);
    }
    
    // Remove item from buffer
    *item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    count--;
    
    printf("Consumer consumed item %d\n", *item);
    
    // Signal that buffer is no longer full
    pthread_cond_signal(&empty);

    pthread_mutex_unlock(&mutex);
    
    return 0;
}

void *producer_work() {
    buffer_item produced_item = 0;
    
    while (produced_item < MAX_ITEMS) {
        produced_item++;
        insert_item(produced_item);
    }
    
    pthread_exit(NULL);
}

void *consumer_work() {
    buffer_item consumed_item;
    
    while (1) {
        remove_item(&consumed_item);
    }
    
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t producer, consumer;
    
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
    
    pthread_create(&producer, NULL, producer_work, NULL);
    pthread_create(&consumer, NULL, consumer_work, NULL);
    
    sleep(2);  // Sleep for 2 seconds before termination of the program.
    
    return 0;
}
