#include <cstdio>
#include <cstdlib>

//Даны две матрицы разного размера. Для той из матриц, в которой есть элементы,
// равные 0, проверить наличие отрицательных элементов в каждой строке.

bool array_input(const char* filename, int*** x, int* m, int* n);
bool HasZeros(int** x, int m, int n);
bool HasNegativesInRows(int* x, int n);

int main(int argc, char* argv[]) {
    int** a = nullptr;
    int** b = nullptr;
    int m1, n1, m2, n2;

    if (argc < 4) {
        printf("Недостаточно параметров!\n");
        return 1;
    }

    if (!array_input(argv[1], &a, &m1, &n1)) {
        return 1;
    }

    if (!array_input(argv[2], &b, &m2, &n2)) {
        free(a);
        return 1;
    }

    FILE* output_file = fopen(argv[3], "w");
    if (!output_file) {
        printf("Невозможно открыть файл для записи: %s\n", argv[3]);
        free(a);
        free(b);
        return 1;
    }

    if (HasZeros(a, m1, n1)) {
        for (int i = 0; i < m1; i++) {
            if (HasNegativesInRows(a[i], n1)) {
                fprintf(output_file, "В матрице 1, в %3d строке есть отрицательные элементы.\n", i + 1);
            } else {
                fprintf(output_file, "В матрице 1, в %3d строке нет отрицательных элементов.\n", i + 1);
            }
        }
    } else {
        fprintf(output_file, "В матрице 1 нет нулевых элементов.\n");
    }

    if (HasZeros(b, m2, n2)) {
        for (int i = 0; i < m2; i++) {
            if (HasNegativesInRows(b[i], n2)) {
                fprintf(output_file, "В матрице 2, в %3d строке есть отрицательные элементы.\n", i + 1);
            } else {
                fprintf(output_file, "В матрице 2, в %3d строке нет отрицательных элементов.\n", i + 1);
            }
        }
    } else {
        fprintf(output_file, "В матрице 2 нет нулевых элементов.\n");
    }

    fclose(output_file);
    free(a);
    free(b);
    return 0;
}

bool array_input(const char* filename, int*** x, int* m, int* n) {
    FILE* file;

    if ((file = fopen(filename, "r")) == nullptr) {
        printf("Невозможно открыть файл %s\n", filename);
        return false;
    }

    if (fscanf(file, "%d%d", m, n) < 2) {
        printf("Недостаточно данных в %s\n", filename);
        fclose(file);
        return false;
    }

    if (*m <= 0 || *n <= 0) {
        printf("Некорректный размер матрицы в %s\n", filename);
        fclose(file);
        return false;
    }

    *x = (int**)malloc(*m * sizeof(int*));
    for (int i = 0; i < *m; i++) {
        (*x)[i] = (int*)malloc(*n * sizeof(int));
        for (int j = 0; j < *n; j++) {
            if (fscanf(file, "%d", &(*x)[i][j]) < 1) {
                printf("Невозможно считать элемент в строке %d в %s\n", i, filename);
                fclose(file);
                for (int k = 0; k < i; k++) {
                    free((*x)[k]);
                }
                free(*x);
                return false;
            }
        }
    }

    fclose(file);
    return true;
}

bool HasZeros(int** x, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (x[i][j] == 0) {
                return true;
            }
        }
    }
    return false; // Нулевых элементов нет
}

bool HasNegativesInRows(int* x, int n) {
    for (int i = 0; i < n; i++) {
        if (x[i] < 0) {
            return true;
        }
    }
    return false; // Отрицательных элементов нет
}
