#include "ann.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

Layer layer_builder(int input_dim, int output_dim, unsigned input_layer)
{
    Layer layer;
    layer.input_dim = input_dim;
    layer.output_dim = output_dim;
    layer.bias = 0.0; // Default bias value

    // Allocate memory for weights
    layer.weights = (double**)malloc(layer.output_dim * sizeof(double*));
    if (layer.weights == NULL) 
    {
        fprintf(stderr, "Memory allocation failed for weights in layer_builder\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for each weight array
    for (int i = 0; i < layer.output_dim; i++) 
    {
        layer.weights[i] = (double*)malloc(layer.input_dim * sizeof(double));
        if (layer.weights[i] == NULL) {

            for (int j = 0; j < i; j++)
                free(layer.weights[j]);

            free(layer.weights);
            fprintf(stderr, "Memory allocation failed for weights[%d] in layer_builder\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // If it's an input layer, set random bias
    if (input_layer)
        layer.bias = ((double)rand() / RAND_MAX); // Random bias between 0 and 1

    // Initialize weights with random values
    for (int i = 0; i < layer.output_dim; i++) 
    {
        for (int j = 0; j < layer.input_dim; j++) 
            layer.weights[i][j] = ((double)rand() / RAND_MAX); // Random weight between -1 and 1
    }

    return layer;
}


Net network_builder(int num_layers, int input_dim, int* hidden_dims, int classes)
{
    srand(time(NULL));

    Net net;
    net.num_layers = num_layers;
    net.layers = (Layer*)malloc(num_layers * sizeof(Layer));
    if (net.layers == NULL)
    {
        // Error handling
        fprintf(stderr, "Memory allocation failed for net.layers in network_builder\n");
        exit(EXIT_FAILURE);
    }

    for(int layer = 0; layer < num_layers; layer++)
    {
        if(layer == 0)
            net.layers[layer] = layer_builder(input_dim, hidden_dims[layer], YES);
        
        else if(layer == num_layers - 1)
            net.layers[layer] = layer_builder(net.layers[layer - 1].output_dim, classes, YES);
        
        else
            net.layers[layer] = layer_builder(net.layers[layer - 1].output_dim, hidden_dims[layer], YES);
        
        if (net.layers[layer].weights == NULL) 
        {

            for (int i = 0; i < layer; i++) 
                free(net.layers[i].weights);
            
            free(net.layers);
            fprintf(stderr, "Error: layer_builder failed in network_builder for layer %d\n", layer);
            exit(EXIT_FAILURE);
        }
    }

    return net;
}


void print_model_summary(Net net)
{
    printf("Model Summary:\n");

    // Iterate through each layer
    for (int i = 0; i < net.num_layers; i++) 
    {

        if(i == net.num_layers - 1)
        {
        Layer layer = net.layers[i];
        printf("Output Layer:\n");
        printf("  Input Dimension: %d\n", layer.input_dim);
        printf("  Output Dimension (classes): %d\n", layer.output_dim);

        // Calculate total number of parameters
        int num_parameters = (layer.input_dim + 1) * layer.output_dim;
        printf("  Total Parameters: %d\n", num_parameters);            
        }

        else
        {
        Layer layer = net.layers[i];
        printf("Hidden Layer %d:\n", i + 1);
        printf("  Input Dimension: %d\n", layer.input_dim);
        printf("  Output Dimension: %d\n", layer.output_dim);

        // Calculate total number of parameters
        int num_parameters = (layer.input_dim + 1) * layer.output_dim;
        printf("  Total Parameters: %d\n", num_parameters);           
        }
    }
}

void print_weights(Net net)
{
    printf("\nFinal column of all matrices are the biases\n");
    for (int i = 0; i < net.num_layers; i++)
    {
        Layer layer = net.layers[i];
        printf("Layer no: %d\n", i+1);
        for(int j = 0; j < layer.output_dim; j++)
        {
            for(int k = 0; k < layer.input_dim; k++)
            {
                printf("%.2f ", layer.weights[j][k]);
            }
            printf("%.2f", layer.bias); // Print bias once per layer
            printf("\n");
        }
        printf("\n");
    }
}

