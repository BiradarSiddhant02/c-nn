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

Data X(Data data);
Data y(Data data);
Data* X_y(Data data);

void head(Data data, int num);
void printHorizontalLine(int width);