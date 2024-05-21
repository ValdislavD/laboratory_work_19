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

void calculateExpressionAndAppendResult(const char *filePath);

//Функция для проверки того, содержит ли слово шаблон
int containsPattern(const char *word, const char *pattern);

// Функция для фильтрации слов, содержащих определенный шаблон, из входного файла в выходной
void filterWordsContainingPattern(const char *inputFilePath, const char *outputFilePath, const char *pattern);

#endif //UNTITLED26_FILE__H
