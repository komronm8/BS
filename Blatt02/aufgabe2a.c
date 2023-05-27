#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int tueten = 40;

void *verteilen(void* arg){
    while(tueten > 0){
        printf("Es sind noch %d Tüten übrig.\n", tueten);
        sleep(1);
        tueten--;
    }

    pthread_exit(NULL);

}

int main(void){

    int status;
    pthread_t thread[5];

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

    return 0;

}