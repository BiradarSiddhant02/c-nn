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
    int dims[2] = {0, 0};

    csv_data.raw_data = read_csv(file_name, dims);
    csv_data.rows = dims[0];
    csv_data.columns = dims[1];

    return csv_data;
}

void printHorizontalLine(int width) {
    for (int i = 0; i < width; i++) {
        printf("-");
    }
    printf("\n");
}

void head(Data data, int num) {
    // Print the header line
    printHorizontalLine(data.columns * 10 + 1);
    printf("|");
    for (int j = 0; j < data.columns - 1; j++) {
        printf("   X%d   |", j + 1);
    }
    printf("   y    |\n");
    printHorizontalLine(data.columns * 10 + 1);

    // Print data rows

    int min = 0;
    int max = data.rows;

    for (int i = 0; i < num; i++) {
        printf("|");
        for (int j = 0; j < data.columns; j++) {
            printf(" %.3f  |", data.raw_data[min + rand() / (RAND_MAX / (max - min + 1) + 1)][j]);
        }
        printf("\n");
        printHorizontalLine(data.columns * 10 + 1);
    }
}

Sample get_sample(double* row, int num)
{
    Sample sample;
    sample._class = row[num];
    sample.num_features = num - 1;

    return sample;
}
