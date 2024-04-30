#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "filehelper.h"
#include "ann.h"

WeightField create_field(Layer layer, int layer_num)
{
    WeightField field;
    field.layer_num = layer_num;
    field.rows = layer.input_dim;
    field.columns = layer.output_dim;

    field.weights = (double**)malloc(field.rows * sizeof(double*));
    for(int i = 0; i < field.rows; i++)
        field.weights[i] = (double*)malloc(field.columns * sizeof(double));

    for(int i = 0; i < field.rows; i++) {
        for(int j = 0; j < field.columns; j++) {
            //copy layer weights and biases
            field.weights[i][j] = layer.weights[j][i]; // Note the change in indices
        }
    }

    // printf("layer num: %d\n", layer_num);
    // printf("columns: %d\n", field.columns);
    // printf("output_dim: %d\n", layer.output_dim);
    // printf("rows: %d\n", field.rows);
    // printf("input_dim: %d\n\n", layer.input_dim);

    return field;
}

TXTFile create_file(Net net, char* file_name) {
    TXTFile file;

    // Assign file name
    file.file_name = file_name;
    file.num_fields = net.num_layers;

    // Allocate memory for file path
    char cwd[2048];
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        file.file_path = malloc(strlen(cwd) + strlen(file_name) + 2); // +2 for the separator and null terminator
        if (file.file_path != NULL) 
        {
            strcpy(file.file_path, cwd);
            strcat(file.file_path, "/");
            strcat(file.file_path, file_name);
        } 
        else 
        {
            perror("Memory allocation failed for file path");
            exit(EXIT_FAILURE);
        }
    } 
    else 
    {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }

    file.fields = (WeightField*)malloc(net.num_layers * sizeof(WeightField));

    for(int i = 0; i < net.num_layers; i++)
    {
        file.fields[i] = create_field(net.layers[i], i);
    }

    return file;
}

void dump_to_file(Net net, char* file_name) 
{

    TXTFile file = create_file(net, file_name);
    // printf("fields created\n");

    // Open the file for writing
    FILE *fp = fopen(file.file_path, "w");
    // printf("file path : %s\n", file.file_path);
    if (fp == NULL) 
    {
        perror("Error opening file");
        return;
    }

    // Write data to the file
    fprintf(fp, "File Name: %s\n", file.file_name);
    fprintf(fp, "File Path: %s\n", file.file_path);
    
    for (int i = 0; i < file.num_fields; i++) 
    {
        WeightField field = file.fields[i];
        fprintf(fp, "Layer Number: %d\n", field.layer_num);
        fprintf(fp, "Rows: %d\n", field.rows);
        fprintf(fp, "Columns: %d\n", field.columns);
        
        for (int j = 0; j < field.rows; j++) 
        {
            for (int k = 0; k < field.columns; k++) 
            {
                fprintf(fp, "%.2f,", field.weights[j][k]);
            }
            fprintf(fp, "\n");
        }

        fprintf(fp, "Biases:\n");
        for (int j = 0; j < field.columns; j++) 
        {
            fprintf(fp, "%.2f,", field.biases[j]);
        }
        fprintf(fp, "\n\n");
    }

    // Close the file
    fclose(fp);
}