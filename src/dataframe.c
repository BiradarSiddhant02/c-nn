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

double** X(Data df)
{
    double** features = (double**)malloc(df.rows * sizeof(double*));
    printf("1\n");
    for(int i = 0; i < df.columns - 1; i++)
        features[i] = (double*)malloc((df.columns - 1) * sizeof(double));
    printf("1\n");
    for(int i = 0; i < df.rows; i++)
    {
        for(int j = 0; j < df.columns - 1; j++)
            features[i][j] = df.raw_data[i][j];
    }
    printf("1\n");
    
    return features;
}

double* y(Data df)
{
    
    double* labels = (double*)malloc(df.rows * sizeof(double));
    printf("1\n");
    for(int i = 0; i < df.rows; i++)
        labels[i] = df.raw_data[i][df.columns - 1];
    printf("1\n");
    return labels;
}

Samples X_y(Data df)
{
    Samples dataframe;
    printf("1\n");
    dataframe.num_samples = df.rows;
    dataframe.num_features = df.columns - 1;

    printf("1\n");
    dataframe.features = X(df);
    printf("1\n");
    dataframe.labels = y(df);
    
    printf("1\n");
    return dataframe;
}
