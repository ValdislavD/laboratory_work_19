#include <stdio.h>
#include <windows.h>
#include "working_with_files\file_.h"

int main() {
    const char *filePath = "expression.txt";

    calculateExpressionAndAppendResult(filePath);

    SetConsoleOutputCP(CP_UTF8);
    printf("Результат вычисления выражений дописан в конец файла.\n");

    return 0;
}