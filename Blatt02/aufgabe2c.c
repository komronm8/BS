#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int tueten = 40;
pthread_mutex_t mutex;

void *verteilen(void* arg){
    while(tueten > 0){
        pthread_mutex_lock(&mutex);
        if(tueten > 0){
            tueten--;
            printf("Es sind noch %d Tüten übrig.\n", tueten);
            sleep(1);
        }   
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);

}

int main(void){

    int status;
    pthread_t thread[5];
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < 5; i++){
        status = pthread_create(&thread[i], NULL, &verteilen, NULL);
        if(status){
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < 5; i++){
        status = pthread_join(thread[i], NULL);
        if(status){
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    printf("Programm ist geendet. Anzahl von tüten: %d\n", tueten);

    pthread_mutex_destroy(&mutex);

    return 0;

}