#include "networkMath.h"
#include "dataFrame.h"
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
    // Check if data is not empty and has at least two rows
    if (data.raw_data == NULL || data.rows < 2) {
        fprintf(stderr, "Error: Cannot shuffle empty or insufficient data\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (int i = data.rows - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        if (i != j) {
            // Swap rows
            double *temp = data.raw_data[i];
            data.raw_data[i] = data.raw_data[j];
            data.raw_data[j] = temp;
        }
    }
}

Data* split(Data data, double trainsize)
{
    if (trainsize <= 0 || trainsize >= 1 || trainsize > (1.0 - (1.0 / data.rows)) || trainsize < (1.0 / data.rows))
    {
        fprintf(stderr, "Error: invalid split size\n");
        exit(EXIT_FAILURE);
    }

    // Check if data is not empty
    if (data.raw_data == NULL || data.rows == 0 || data.columns == 0) 
    {
        fprintf(stderr, "Error: Cannot split empty data\n");
        exit(EXIT_FAILURE);
    }

    int size = round(trainsize * data.rows);

    // Allocate memory for train_val_set
    Data* train_val_set = malloc(2 * sizeof(Data));
    if (train_val_set == NULL) 
    {
        fprintf(stderr, "Error: Memory allocation failed for train_val_set in split\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for training set
    train_val_set[0].raw_data = malloc(size * sizeof(double*));
    if (train_val_set[0].raw_data == NULL) 
    {
        free(train_val_set); // Clean up memory
        fprintf(stderr, "Error: Memory allocation failed for training set in split\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < size; i++)
    {
        train_val_set[0].raw_data[i] = malloc(data.columns * sizeof(double));
        if (train_val_set[0].raw_data[i] == NULL) 
        {
            // Clean up previously allocated memory
            for (int j = 0; j < i; j++) 
                free(train_val_set[0].raw_data[j]);
            
            free(train_val_set[0].raw_data);
            free(train_val_set);
            fprintf(stderr, "Error: Memory allocation failed for training set row %d in split\n", i);
            exit(EXIT_FAILURE);
        }
        memcpy(train_val_set[0].raw_data[i], data.raw_data[i], data.columns * sizeof(double));
    }

    train_val_set[0].rows = size;
    train_val_set[0].columns = data.columns;

    // Allocate memory for validation set
    train_val_set[1].raw_data = malloc((data.rows - size) * sizeof(double*));
    if (train_val_set[1].raw_data == NULL) 
    {
        // Clean up memory
        for (int i = 0; i < size; i++) 
            free(train_val_set[0].raw_data[i]);
        
        free(train_val_set[0].raw_data);
        free(train_val_set);
        fprintf(stderr, "Error: Memory allocation failed for validation set in split\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < data.rows - size; i++)
    {
        train_val_set[1].raw_data[i] = malloc(data.columns * sizeof(double));
        if (train_val_set[1].raw_data[i] == NULL) 
        {
            for (int j = 0; j < i; j++) 
                free(train_val_set[1].raw_data[j]);
            
            free(train_val_set[1].raw_data);
            for (int j = 0; j < size; j++) 
                free(train_val_set[0].raw_data[j]);
            
            free(train_val_set[0].raw_data);
            free(train_val_set);
            fprintf(stderr, "Error: Memory allocation failed for validation set row %d in split\n", i);
            exit(EXIT_FAILURE);
        }
        memcpy(train_val_set[1].raw_data[i], data.raw_data[i + size], data.columns * sizeof(double));
    }

    train_val_set[1].rows = data.rows - size;
    train_val_set[1].columns = data.columns;

    return train_val_set;
}

Sample* samples(Data data)
{
    // Check if data is not empty
    if (data.raw_data == NULL || data.rows == 0 || data.columns == 0) {
        fprintf(stderr, "Error: Cannot create samples from empty data\n");
        exit(EXIT_FAILURE);
    }

    Sample* sample = malloc(data.rows * sizeof(Sample));
    if (sample == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for samples in samples\n");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < data.rows; i++)
        sample[i] = get_sample(data.raw_data[i], data.columns);

    return sample;
}

double** forward_pass(Net net, Sample* samples, int num_samples)
{
    double** outputs = (double**)malloc(num_samples * sizeof(double*));

    for(int sample = 0; sample < num_samples; sample++)
    {
        double* X = samples[sample].features;
        double* input = X;
        
        for(int layer = 0; layer < net.num_layers; layer++)
        {
            Layer current_layer = net.layers[layer];
            int dimY = current_layer.output_dim;

            // Allocate memory for output of this layer
            double* Y = (double*)malloc(dimY * sizeof(double));

            // Calculate output of this layer (assuming dot() is a function for matrix multiplication)
            Y = dot(input, current_layer.weights, current_layer.input_dim, dimY);
            
            for (int i = 0; i < dimY; i++)
                Y[i] += current_layer.bias;

            // Apply activation function
            for (int i = 0; i < dimY; i++) {
                Y[i] = relu(Y[i]); // Apply ReLU activation
                // Y[i] = sigmoid(Y[i]); // Alternatively, apply sigmoid activation
            }

            // Free memory of input for next layer
            free(input);

            // Update input for next layer
            input = Y;
        }

        // Store output of the last layer
        outputs[sample] = input;
    }

    return outputs;
}


double* dot(double* A, double** B, int dim_in, int dim_out)
{
    double* result = (double*)malloc(sizeof(double) * dim_out);
    for (int i = 0; i < dim_out; i++) 
    {
        result[i] = 0.0;
        for (int j = 0; j < dim_in; j++) 
            result[i] += A[j] * B[j][i];
    }
    return result;
}