#include <stdio.h>
#include <stdlib.h>
#include "ann.h"

typedef struct weightField
{
    int layer_num;
    int rows;
    int columns;
    double** weights;
    double* biases;
} WeightField;

typedef struct csvfile
{
    char* file_name;
    char* file_path;
    int num_fields;
    WeightField* fields;
} TXTFile;

WeightField create_field(Layer layer, int layer_num);
TXTFile create_file(Net net, char* file_name);

void dump_to_file(Net net, char* file_name);