#include "sum.h"
#include <stdio.h>

int main(int argc, char* argv[]) {

    if(argc != 3){
        printf("Not enough arguments are given\n");
    }
    else{
        sum_of_pairs_to_file(argv[1], argv[2]);
    }

    return 0;
}