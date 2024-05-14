#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <stdio.h>
#include <stdlib.h>
#include "ann.h"

typedef struct data
{
    double** raw_data; 
    int rows;
    int columns;
} Data;

typedef struct sample
{
    double* features;
    double _class;

    int num_features;
}Sample;

Data get_data(char* file_name);
Sample get_sample(double* row, int num);

void head(Data data, int num);
void printHorizontalLine(int width);

#endif