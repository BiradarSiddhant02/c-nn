#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "fileHelper.h"
#include "ann.h"
#include "dataFrame.h"

WeightField create_field(Layer layer, int layer_num)
{
    WeightField field;

    if (layer.input_dim <= 0 || layer.output_dim <= 0) 
    {
        fprintf(stderr, "Error: Invalid dimensions in layer for creating field\n");
        exit(EXIT_FAILURE);
    }

    field.layer_num = layer_num;
    field.rows = layer.input_dim;
    field.columns = layer.output_dim;

    field.weights = (double**)malloc(field.rows * sizeof(double*));
    if (field.weights == NULL) 
    {
        fprintf(stderr, "Error: Memory allocation failed for weights in create_field\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < field.rows; i++) 
    {
        field.weights[i] = (double*)malloc(field.columns * sizeof(double));
        if (field.weights[i] == NULL) 
        {
            for (int j = 0; j < i; j++) 
                free(field.weights[j]);
        
            free(field.weights);
            fprintf(stderr, "Error: Memory allocation failed for weights[%d] in create_field\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Copy weights from the layer
    for(int i = 0; i < field.rows; i++)
        memcpy(field.weights[i], layer.weights[i], field.columns * sizeof(double));

    // Allocate memory for biases
    field.biases = (double*)malloc(field.rows * sizeof(double));
    if (field.biases == NULL) 
    {
        // Clean up previously allocated memory
        for (int i = 0; i < field.rows; i++)
            free(field.weights[i]);
        free(field.weights);
        fprintf(stderr, "Error: Memory allocation failed for biases in create_field\n");
        exit(EXIT_FAILURE);
    }

    // Set biases
    for(int i = 0; i < field.rows; i++)
        field.biases[i] = layer.bias;

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

    // Open the file for writing
    FILE *fp = fopen(file.file_path, "w");
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
                fprintf(fp, "%.2f ", field.weights[j][k]);
            }
            fprintf(fp, "\n");
        }

        fprintf(fp, "Biases:\n");
        for (int j = 0; j < field.columns; j++) 
        {
            fprintf(fp, "%.2f ", field.biases[j]);
        }
        fprintf(fp, "\n\n");
    }

    // Close the file
    fclose(fp);
}

double** read_csv(char* file_name, int dims[])
{
    FILE* csv_file = fopen(file_name, "r");
    
    if(csv_file == NULL) 
    {
        printf("file not found\n");
        return NULL;
    }

    else
    {
        char buffer[1024];

        int rows = 0;
        int cols = 0;

        while(fgets(buffer, 1024, csv_file))
        {
            rows++;

            if(rows == 1) {continue;}

            char* value = strtok(buffer, ", ");
            while(value)
            { 
                value = strtok(NULL, ",");
                cols++;
            }
        }
        
        rows -= 1; cols /= rows;
        
        dims[0] = rows;
        dims[1] = cols;

        double** data = malloc(rows * sizeof(double*));
        for(int i = 0; i < rows; i++)
            data[i] = malloc(cols * sizeof(double));

        fseek(csv_file, 0, SEEK_SET);
        rows = 0; 
        cols = 0;
        
        while (fgets(buffer, 1024, csv_file)) 
        {
            ++rows;

            if (rows == 1) { continue; }

            char* value = strtok(buffer, ", ");
            cols = 0; // Reset cols for each row
            while (value) 
            {
                data[rows - 2][cols++] = atof(value); // Adjusted indexing
                value = strtok(NULL, ",");
            }
        }
        
        fclose(csv_file);
        return data;
    }
}