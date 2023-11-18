#include <stdio.h>
#include <iostream>

void fillArray(int* size, double** array, char* fname) {
    FILE* file;

    if ((file = fopen(fname, "r")) == NULL) {
        printf("Невозможно открыть файл '%s' для чтения\n", fname);
        return;
    }
    if (fscanf(file, "%i", size) != 1) {
        printf("Ошибка чтения из файла '%s'\n", fname);
        fclose(file);
        return;
    }

    *array = new double[*size]; // выделяем память динамически

    for (int i = 0; i < *size; i++) {
        if (fscanf(file, "%lf", &(*array)[i]) != 1) {
            printf("Ошибка чтения из файла '%s'\n", fname);
            fclose(file);
            delete[] *array; // освобождаем память в случае ошибки
            return;
        }
    }
    fclose(file);
}

double F1(double x) {
    return x * x;
}

double F2(double x) {
    return x;
}

double sumInRange(double (*func)(double), double array[], int n, double minRange, double maxRange) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        double value = func(array[i]);
        if (value >= minRange && value <= maxRange) {
            sum += func(array[i]);
        }
    }
    return sum;
}

void printArr(double (*func)(double), double array[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << func(array[i]) << " ";
    }
    std::cout << "\n";
}

int main(int argc, char* argv[]) {
    FILE* output = fopen(argv[4], "w");
    if (output == nullptr) {
        printf("Невозможно открыть файл '%s' для записи\n", argv[5]);
        return 1;
    }
    double* a = nullptr; // инициализируем указатели как nullptr
    double* b = nullptr;
    double* c = nullptr;
    int na = 0, nb = 0, nc = 0;
    double minRange = 0, maxRange = 0;

    if (argc < 5) {
        printf("Недостаточно параметров\n");
        fclose(output);
        return 1;
    }
    else {
        fillArray(&na, &a, argv[1]); // передаем адрес указателя
        fillArray(&nb, &b, argv[2]);
        fillArray(&nc, &c, argv[3]);

        // задайте значения диапазон
        printf("Введите минимальное значение диапазона: ");
        scanf("%lf", &minRange);
        printf("Введите максимальное значение диапазона: ");
        scanf("%lf", &maxRange);

        if (a == nullptr || b == nullptr || c == nullptr) { // проверка на успешное выделение памяти
            printf("Ошибка выделения памяти\n");
            fclose(output);
            delete[] a; // освобождаем память в случае ошибки
            delete[] b;
            delete[] c;
            return 1;
        }
        double sumA = sumInRange(F2, a, na, minRange, maxRange);
        double sumB = sumInRange(F2, b, nb, minRange, maxRange);
        double sumC = sumInRange(F2, c, nc, minRange, maxRange);

        printArr(F2, a, na);
        printArr(F2, b, nb);
        printArr(F2, c, nc);

        fprintf(output, "Сумма элементов в заданном диапазоне в массиве A: %.2lf\n", sumA);
        fprintf(output, "Сумма элементов в заданном диапазоне в массиве B: %.2lf\n", sumB);
        fprintf(output, "Сумма элементов в заданном диапазоне в массиве C: %.2lf\n", sumC);

        if (sumA > sumB && sumA > sumC) {
            fprintf(output, "Сумма больше в массиве A.\n");
        }
        else if (sumB > sumA && sumB > sumC) {
            fprintf(output, "Сумма больше в массиве B.\n");
        }
        else if (sumC > sumA && sumC > sumB) {
            fprintf(output, "Сумма больше в массиве C.\n");
        }
        else if (sumC == sumA && sumC == sumB) {
            fprintf(output, "Суммы совпадают в трех массивах.\n");
        } else {
            fprintf(output, "Суммы совпадают в двух массивах.\n");
        }

        // Освобождаем память
        delete[] a;
        delete[] b;
        delete[] c;
    }

    fclose(output);

    return 0;
}
