#include "ann.h"
#include "networkMath.h"
#include "filehelper.h"
#include "dataframe.h"

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

    int dims[2] = {0, 0};

    Data data = get_data("../data/data.csv");
    head(data, 3);

    Data* frame;
    frame = X_y(data);

    return 0;
}
