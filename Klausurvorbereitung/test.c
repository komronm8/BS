#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int x = 1; 
void next() {
    printf("%d, ", x++);
}

void* five() { 
    x += 5;
    printf("%d, ", x++);
    return 0; 
}

int main() { 
    next(); 
    fflush(stdout);

    pid_t pid = fork();
    if (pid > 0) {
        waitpid(pid, NULL, 0); 
        next();
        int x = 0; 
        next();
    } 
    else if (pid == 0) { 
        pthread_t t;
        if(pthread_create(&t, NULL, &five, NULL)) {
            printf("Schade\n");
        } 
        else{
            pthread_join(t, NULL);
        }
        next();
        printf("Hello ");
    } 
    else { 
        next();
        printf("Ohje\n"); 
        return 0;
    }
    return 0;
}
