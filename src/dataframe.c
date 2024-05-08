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

// function to seperate features and labels
Data* X_y(Data data)
{
    // printf("data created\n");
    Data* result = (Data*)malloc(2 * sizeof(Data)); // Allocate memory for features and labels

    // Extract features
    // printf("extracting x\n");
    result[0] = X(data);
    // printf("extracted x\n");

    // Extract labels
    // printf("extracting y\n");
    result[1] = y(data);
    // printf("extracted y\n");

    return result;
}

Data X(Data data)
{
    Data features;
    // printf("%d %d\n", data.rows, data.columns);
    features.rows = data.rows;
    // printf("%d\n", features.rows);
    features.columns = data.columns - 1; // Exclude the last column for labels
    // printf("%d\n", features.columns);
    // printf("%d %d, %d %d\n", data.rows, data.columns, features.rows, features.columns);

    // Allocate memory for features
    features.raw_data = (double**)malloc(data.rows * sizeof(double*));
    for (int i = 0; i < features.rows; i++) {
        features.raw_data[i] = (double*)malloc((data.columns - 1) * sizeof(double));
        for (int j = 0; j < features.columns; j++) {
            features.raw_data[i][j] = data.raw_data[i][j];
        }
    }

    return features;
}

Data y(Data data)
{
    Data labels;
    labels.rows = data.rows;
    labels.columns = 1; // Only one column for labels

    // Allocate memory for labels
    labels.raw_data = (double**)malloc(labels.rows * sizeof(double*));
    for (int i = 0; i < labels.rows; i++) 
    {
        labels.raw_data[i] = (double*)malloc(labels.columns * sizeof(double));
        // Copy the last column from raw_data to labels
        labels.raw_data[i][0] = data.raw_data[i][data.columns - 1];
    }

    return labels;
}