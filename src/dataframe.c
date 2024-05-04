#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "filehelper.h"
#include "ann.h"
#include "dataframe.h"

Data get_data(char* file_name)
{
    Data csv_data;
    int dims[2];
    
    csv_data.raw_data = read_csv(file_name, dims);
    csv_data.rows = dims[0] - 1;
    csv_data.columns = dims[1];

    return csv_data;
}