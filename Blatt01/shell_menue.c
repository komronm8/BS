#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){

    while(1){
        int wahl;
        printf("Bitte wählen Sie ein Programm aus:\n 1. ls -a\n 2. cat fish.txt\n 3. exit\n");
        
        if(scanf("%d", &wahl) < 1){
            printf("Fehler bei scanf!\n");
            return 1;
        }
        if(wahl < 1 || wahl > 3 ){
            printf("Bitte wählen Sie nur 1, 2 oder 3.\n");
            return 1;
        }

        printf("Sie haben Option %d ausgewählt.\n", wahl);

        if(wahl == 3){
            return 0;
        }

        pid_t pid = fork();
        int status;

        switch(pid){
            case -1: 
                perror("Fork"); 
                exit(EXIT_FAILURE);
            case 0: 
                if(wahl == 1){
                    execlp("ls", "ls", "-a", NULL);
                }
                else{
                    execlp("cat", "cat", "fish.txt", NULL);
                }
            default:
                if(waitpid(pid, &status, 0) == -1){
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }
                printf("\nDer Kindprozess hat mit dem PID %d terminiert.\n", pid);
                printf("Der Kindprozess hat mit dem Status %d terminiert.\n", WEXITSTATUS(status));
                if(WEXITSTATUS(status)){
                    printf("Kindprozess hat terminiert mit error.\n");
                }
        }   
    }
}   