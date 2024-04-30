#ifndef ANN_H
#define ANN_H

#define YES 1
#define NO 0

typedef struct layer
{
    int input_dim;
    int output_dim;
    double** weights;
    double bias;
} Layer;

typedef struct network
{
    int num_layers;
    Layer* layers;
} Net;

Layer layer_builder(int input_dim, int output_dim, unsigned input_layer);
Net network_builder(int num_layers, int input_dim, int* hidden_dims, int classes);
void print_model_summary(Net net);

void print_weights(Net net);


#endif /* ANN_H */
