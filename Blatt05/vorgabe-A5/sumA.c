#include "sum.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

FILE* checked_open(const char* input_file_path) {
    // HIER CODE EINFÜGEN

    struct stat finfo;
    FILE *file_pointer;

    if(stat(input_file_path, &finfo) == -1){
        printf("Das path für das Datei ist falsch.\n");
    }
    else{
        if(S_ISREG(finfo.st_mode)){
            if(finfo.st_size > 0){
                file_pointer = fopen(input_file_path, "r");
                if(file_pointer == NULL){
                    printf("Error occured while opening file\n");
                }
                else{
                    return file_pointer;
                }
            }
            else{
                printf("Das Datei ist nicht größer als 0 Bytes.\n");
            }
        }
        else{
            printf("Das Datei ist nicht regular.\n");
        }
    }

	return NULL;
}
