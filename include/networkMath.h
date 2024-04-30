#ifndef NETWORKMATH_H
#define NETWORKMATH_H

#include "ann.h"

double*** get_all_weights(Net net);

double* forward_pass(Net net, double* input_vec);

double relu(double x);
double* dot(double* A, double** B, int dimA, int* dimB);

#endif