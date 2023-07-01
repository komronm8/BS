#include "sum.h"
#include <stdio.h>

int read_sum(FILE* file) {
    // HIER CODE EINFÜGEN

    int nummer1, nummer2;
    long offset;

    if(fscanf(file, "%d", &nummer1) == -1){
        printf("Ende das Datei wurde erreicht.\n");
        return -1;
    }
    offset = ftell(file);
    if(fscanf(file, "%d", &nummer2) == -1){
        printf("Ende das Datei wurde erreicht.\n");
        return -1;
    }
    fseek(file, offset, SEEK_SET);

    return nummer1 + nummer2;
}

int sum_of_pairs(const char* file_path) {
    // HIER CODE EINFÜGEN

    int max = 0;
    FILE *fp = checked_open(file_path);

    while( 1 ){
        int sum = read_sum(fp);
        if(sum == -1){
            return max;
        }
        else{
            if(sum > max){
                max = sum;
            }
        }
    }

	return 0;
}
