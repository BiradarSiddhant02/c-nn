#include "networkMath.h"
#include "dataframe.h"
#include "ann.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

double relu(double x) { return (x > 0) ? x : 0; }
double sigmoid(double x) { return 1 / (1 + exp(-x)); }
double relu_derivative(double x) { return (x > 0) ? 1 : 0; }
double sigmoid_derivative(double x) { return sigmoid(x) * (1 - sigmoid(x)); }


double** run_epoch(Net net, Data data)
{
    // shuffle data

        shuffle(data);
        // printf("%d %d\n", data.rows, data.columns);

    // split data into train and validation

        Data* train_val_set = split(data, .7);

    // seperate features and labels

        Sample* train_samples = samples(train_val_set[0]);
        Sample* validation_samples = samples(train_val_set[1]);

        head(train_val_set[0], 3);
        head(train_val_set[1], 3);

    // forward pass all training data

        // forwardpass()

    // calculate loss
    // backpropagate loss

        // backprop()

    // track loss and performance
    // validate

        // validate()

        return NULL;
}

void shuffle(Data data)
{

    srand(time(NULL));
    for (int i = data.rows - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        if (i != j) {
            double *temp = data.raw_data[i];
            data.raw_data[i] = data.raw_data[j];
            data.raw_data[j] = temp;
        }
    }
}

Data* split(Data data, double trainsize)
{
    if(trainsize > 1. - (1 / data.rows) | trainsize < (1 / data.rows))
    {
        fprintf(stderr, "Error: invalid split size\n");
        exit(EXIT_FAILURE);
    }

    int size = round(trainsize * data.rows);
    Data* train_val_set = malloc(2 * sizeof(Data));
    // printf("%d\n", size);

    train_val_set[0].raw_data = malloc(size * sizeof(double*));
    for(int i = 0; i < size; i++)
    {
        train_val_set[0].raw_data[i] = malloc(data.columns * sizeof(double));
        memcpy(train_val_set[0].raw_data[i], data.raw_data[i], data.columns * sizeof(double));
    }

    train_val_set[0].rows = size;
    train_val_set[0].columns = data.columns;

    train_val_set[1].raw_data = malloc((data.rows - size) * sizeof(double*));
    for(int i = 0; i < data.rows - size; i++)
    {
        train_val_set[1].raw_data[i] = malloc(data.columns * sizeof(double));
        memcpy(train_val_set[1].raw_data[i], data.raw_data[i + size], data.columns * sizeof(double));
    }

    train_val_set[1].rows = data.rows - size;
    train_val_set[1].columns = data.columns;

    return train_val_set;
}

Sample* samples(Data data)
{
    Sample* sample = malloc(data.rows * sizeof(Sample));
    
    // printf("%d\n", data.rows);
    for(int i = 0; i < data.rows; i++)
    {
        // printf("i=%d\n", i);
        sample[i] = get_sample(data.raw_data[i], data.columns);
    }

    return sample;
}