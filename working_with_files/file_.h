#ifndef UNTITLED26_FILE__H
#define UNTITLED26_FILE__H

#include <stdio.h>
#include <stdlib.h>

// Функция для чтения матрицы из файла
int** readMatrix(FILE *file, int n);

// Функция для записи матрицы в файл
void writeMatrix(FILE *file, int **matrix, int n);

// Функция для освобождения памяти, выделенной под матрицу
void freeMatrix(int **matrix, int n);

void convertFixedToFloating(const char *inputFilePath, const char *outputFilePath);

#endif //UNTITLED26_FILE__H
