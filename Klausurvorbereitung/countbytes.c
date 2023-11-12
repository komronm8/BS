#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 100

static size_t count_bytes(const char *filename){

    FILE* file_pointer = fopen(filename, "r");
    
    if(file_pointer == NULL){
        printf("Error occured while opening file.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[BUF_SIZE];
    int size = 0;

    while(!feof(file_pointer) && !ferror(file_pointer)){
        fread(buffer, 1, 1, file_pointer);
        size++;
    }

    if(ferror(file_pointer)){
        printf("Error occured while reading file.\n");
        exit(EXIT_FAILURE);
    }

    return size-1;
}

int main(int argc, const char *argv[]){

    if(argc < 2){
        printf("Not enough arguments given.\n");
        return EXIT_FAILURE;
    }

    int size;

    for(int i = 1; i < argc; i++){
        size = count_bytes(argv[i]);
        printf("Die Datei %s enthält %d Bytes.\n", argv[i], size);
    }

    return EXIT_SUCCESS;
}