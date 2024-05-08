#include <stdio.h>
#include <stdlib.h>
#include "ann.h"

typedef struct data
{
    double** raw_data; 
    int rows;
    int columns;
} Data;

Data get_data(char* file_name);

void head(Data data, int num);
void printHorizontalLine(int width);