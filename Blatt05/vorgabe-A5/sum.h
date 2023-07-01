#ifndef _SUM_H_
#define _SUM_H_

#include <stdio.h>

FILE* checked_open(const char* input_file_path);
int  sum_of_pairs(const char* input_file_path);
void sum_of_pairs_to_file(const char* input_file_path, const char* output_file_path);

#endif