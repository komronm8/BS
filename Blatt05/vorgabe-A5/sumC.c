#include "sum.h"
#include <stdio.h>
#include <string.h>

void sum_of_pairs_to_file(const char* input_file_path, const char* output_file_path) {
    // HIER CODE EINFÜGEN

    int max = sum_of_pairs(input_file_path);

    FILE *file_pointer;

    file_pointer = fopen(output_file_path, "r+");
    if(file_pointer == NULL){
        printf("Error occured while opening file\n");
        return;
    }

    fprintf(file_pointer, "Die größte Summe lautet %d.", max);
    printf("Die größte Summe lautet %d\n", max);
    fclose(file_pointer);
	
}