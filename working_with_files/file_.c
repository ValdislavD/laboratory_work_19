#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
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

int evaluateExpression(const char *expression, int *result) {
    int operand1 = 0, operand2 = 0;
    char operator = 0;
    int numOperands = 0;

    while (*expression) {
        if (isdigit(*expression)) {
            if (numOperands == 0) {
                operand1 = *expression - '0';
                numOperands++;
            } else if (numOperands == 1) {
                operand2 = *expression - '0';
                numOperands++;
            } else {
                return -1; // Ошибка: слишком много операндов
            }
        } else if (*expression == '+' || *expression == '-' || *expression == '*' || *expression == '/') {
            if (operator == 0) {
                operator = *expression;
            } else {
                return -1; // Ошибка: слишком много операторов
            }
        }
        expression++;
    }

    if (numOperands < 2) {
        return -1; // Ошибка: недостаточно операндов
    }

    switch (operator) {
        case '+': *result = operand1 + operand2; break;
        case '-': *result = operand1 - operand2; break;
        case '*': *result = operand1 * operand2; break;
        case '/': *result = operand1 / operand2; break;
        default: return -1; // Ошибка: неизвестный оператор
    }

    return 0; // Успешно
}

void calculateExpressionAndAppendResult(const char *filePath) {
    FILE *file = fopen(filePath, "r+");
    if (file == NULL) {
        SetConsoleOutputCP(CP_UTF8);
        fprintf(stderr, "Ошибка открытия файла.\n");
        exit(1);
    }

    char expression[100];
    char buffer[10000] = {0};  // buffer to store the entire content of the file
    char *buf_ptr = buffer;
    long offset = 0;

    while (fgets(expression, sizeof(expression), file) != NULL) {
        // Remove the newline character at the end of the expression
        size_t len = strlen(expression);
        if (len > 0 && expression[len - 1] == '\n') {
            expression[len - 1] = '\0';
        }

        int result;
        if (evaluateExpression(expression, &result) == 0) {
            buf_ptr += sprintf(buf_ptr, "%s\n%d\n", expression, result);
        } else {
            buf_ptr += sprintf(buf_ptr, "%s\n", expression);
            SetConsoleOutputCP(CP_UTF8);
            fprintf(stderr, "Ошибка вычисления выражения: %s\n", expression);
        }
    }

    freopen(filePath, "w", file);
    fputs(buffer, file);

    fclose(file);
}

int containsPattern(const char *word, const char *pattern) {
    return strstr(word, pattern) != NULL;
}

void filterWordsContainingPattern(const char *inputFilePath, const char *outputFilePath, const char *pattern) {
    FILE *inputFile = fopen(inputFilePath, "r");
    if (inputFile == NULL) {
        SetConsoleOutputCP(CP_UTF8);
        fprintf(stderr, "Ошибка при открытии входного файла.\n");
        exit(1);
    }

    FILE *outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL) {
        SetConsoleOutputCP(CP_UTF8);
        fprintf(stderr, "Ошибка при открытии выходного файла.\n");
        fclose(inputFile);
        exit(1);
    }

    char word[256];
    while (fscanf(inputFile, "%255s", word) == 1) {
        if (containsPattern(word, pattern)) {
            fprintf(outputFile, "%s\n", word);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}
