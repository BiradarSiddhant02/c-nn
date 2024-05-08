#include <stdio.h>
#include <stdlib.h>
#include "ann.h"

typedef struct data
{
    double** raw_data; 
    int rows;
    int columns;
} Data;

typedef struct samples
{
    double** features;
    double* labels;

    int num_features;
    int num_samples;
} Samples;

Data get_data(char* file_name);

double** X(Data df);
double* y(Data df);

Samples X_y(Data df);

void head(Data data, int num);
void printHorizontalLine(int width);