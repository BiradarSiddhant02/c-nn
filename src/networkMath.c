#include "networkMath.h"
#include "ann.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double relu(double x) { return (x > 0) ? x : 0; }

double*** get_all_weights(Net net)
{
    double*** all_weights = (double***)malloc(net.num_layers * sizeof(double**));
    
    for (int i = 0; i < net.num_layers; i++) 
    {
        const Layer layer = net.layers[i];
        all_weights[i] = layer.weights;
    }

    return all_weights;
}

double* forward_pass(Net net, double* input_vec) 
{
    double* current_out = input_vec;

    // loop running through all the layers
    for(int i = 0; i < net.num_layers; i++)
    {
        // pass the current output vector and the current weight matrix to the dot() function
        int dimA = net.layers[i].input_dim;
        int dimB[2] = {net.layers[i].output_dim, net.layers[i].input_dim}; // Corrected dimB

        current_out = dot(current_out, net.layers[i].weights, dimA, dimB);

        for (int j = 0; j < dimB[0]; j++) 
        {
            current_out[j] += net.layers[i].bias; // Add bias
            current_out[j] = relu(current_out[j]); // Apply ReLU activation
        }
    }

    return current_out;
}


double* dot(double* A, double** B, int dimA, int* dimB)
{
    double sum;

    double* out_vec = (double*)malloc(dimB[0] * sizeof(double));
    
    for (int i = 0; i < dimB[0]; i++) {
        sum = 0.0;
        for (int j = 0; j < dimA; j++) {
            sum += B[i][j] * A[j];
        }
        out_vec[i] = sum;
    }

    return out_vec;
}