#ifndef NETWORKMATH_H
#define NETWORKMATH_H

#include "dataframe.h"
#include "ann.h"

double relu(double x);
double sigmoid(double x);
double relu_derivative(double x);
double sigmoid_derivative(double x);

double** run_epoch(Net net, Data data);

void shuffle(Data data);
Data* split(Data data, double trainsize);
Sample* samples(Data data);

#endif