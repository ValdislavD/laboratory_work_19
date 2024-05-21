#include <stdio.h>
#include <stdlib.h>
#include "file_.h"

int** readMatrix(FILE *file, int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        matrix[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; ++j) {
            fscanf(file, "%d", &(matrix[i][j]));
        }
    }
    return matrix;
}

void writeMatrix(FILE *file, int **matrix, int n) {
    fprintf(file, "%d\n", n);
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            fprintf(file, "%d", matrix[i][j]);
            if (i < n - 1) {
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }
}

void freeMatrix(int **matrix, int n) {
    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void convertFixedToFloating(const char *inputFilePath, const char *outputFilePath) {
    FILE *inputFile = fopen(inputFilePath, "r");
    FILE *outputFile = fopen(outputFilePath, "w");

    if (inputFile == NULL || outputFile == NULL) {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }

    double number;
    while (fscanf(inputFile, "%lf", &number) == 1) {
        fprintf(outputFile, "%.2lf\n", number);
    }

    fclose(inputFile);
    fclose(outputFile);
}
