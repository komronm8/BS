#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUF_SIZE 20

sem_t mutex;
sem_t cnt_used;
sem_t cnt_empty;

struct buffer{
    int data[BUF_SIZE];
    int read;
    int write;
};

struct buffer char_buf;

void put_buffer(int value){
    char_buf.data[char_buf.write] = value; 
    char_buf.write = (char_buf.write + 1) % BUF_SIZE;
}

int get_buffer(void) {
    int value;
    value = char_buf.data[char_buf.read]; 
    char_buf.read = (char_buf.read + 1) % BUF_SIZE; 
    return value;
}

void* reader_thread(void* arg){
    
    while(1){

        sem_wait(&cnt_used);
        sem_wait(&mutex);
        int num = get_buffer();
        sem_post(&mutex);
        printf("reader: Read value '%d' from the buffer\n", num);
        if(num < 0){
            printf("reader: Negative value. Terminating\n");
            break;
        }

    }
    return 0;
}

int main(int argc, const char *argv[]){
    pthread_t thread;
    char_buf.read = 0;
    char_buf.write = 0;

    sem_init(&mutex, 0, 1);
    sem_init(&cnt_used, 0, 0);
    sem_init(&cnt_empty, 0, 20);   

    int status;
    status = pthread_create(&thread, NULL, reader_thread, NULL);
    if(status){
        printf("Fehler ist aufgetretten\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        int num;
        printf("writer: Please enter a number: ");
        scanf("%d", &num);

        sem_wait(&cnt_empty);
        sem_wait(&mutex);
        put_buffer(num);
        sem_post(&mutex);
        sem_post(&cnt_used);

        if(num < 0){
            printf("writer: Negative value. Terminating\n");
            break;
        }
    }

    status = pthread_join(thread, NULL);
    if(status){
        printf("Fehler ist aufgetreten\n");
        exit(EXIT_FAILURE);
    }

    sem_destroy(&mutex);
    sem_destroy(&cnt_empty);
    sem_destroy(&cnt_used);

    return EXIT_SUCCESS;

}