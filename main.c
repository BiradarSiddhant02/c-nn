#include "ann.h"
#include "networkMath.h"
#include "filehelper.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() 
{
    int input_dim = 2;
    int hidden_dim[] = {2, 2};
    int classes = 2;

    int num_layers = sizeof(hidden_dim) / sizeof(hidden_dim[0]) + 1;

    Net ann = network_builder(num_layers, input_dim, hidden_dim, classes);

    double input_vector[2] = {5, -1};

    printf("\ninputs\n");
    for(int i = 0; i < input_dim; i++)
        printf("%.2f ", input_vector[i]);
    printf("\n");   

    print_weights(ann);

    double* output_vector = forward_pass(ann, input_vector);

    for(int i = 0; i < classes; i++)
        printf("%.2f ", output_vector[i]);
    printf("\n");


    return 0;
}
