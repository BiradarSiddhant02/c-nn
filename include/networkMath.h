#ifndef NETWORKMATH_H
#define NETWORKMATH_H

#include "dataframe.h"
#include "ann.h"

double*** get_all_weights(Net net);

double* forward_pass(Net net, double* input_vec);

double relu(double x);
double* dot(double* A, double** B, int dimA, int* dimB);

double* run_epoch(Net net, Data data);

#endif