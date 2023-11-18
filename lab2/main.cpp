//Даны две матрицы разного размера. Для той из матриц, в которой есть элементы, равные 0,
// проверить наличие отрицательных элементов в каждой строке.

#include <cstdio>

const int nmax = 100;

bool array_input(const char* filename, int x[][nmax], int* m, int* n);
bool HasZeros(int x[][nmax], int m, int n);
bool HasNegativesInRows(int x[], int n);

int main(int argc, char* argv[]) {
    int a[nmax][nmax];
    int b[nmax][nmax];
    int m1, n1, m2, n2;

    if (argc < 3) {
        printf("Недостаточно параметров!\n");
        return 1;
    }

    if (!array_input(argv[1], a, &m1, &n1)) {
        return 1;
    }

    if (!array_input(argv[2], b, &m2, &n2)) {
        return 1;
    }

    if (m1 <= 0 || m1 > nmax || n1 <= 0 || n1 > nmax || m2 <= 0 || m2 > nmax || n2 <= 0 || n2 > nmax) {
        printf("Некорректный размер матрицы в файле '%s'\n", argv[1]);
        return 1;
    }

    FILE* output_file = fopen(argv[3], "w");
    if (!output_file) {
        printf("Невозможно открыть файл для записи: %s\n", argv[2]);
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
    return 0;
}

bool array_input(const char* filename, int x[][nmax], int* m, int* n) {
    FILE* file;

    if ((file = fopen(filename, "r")) == NULL) {
        printf("Невозможно открыть файл %s\n", filename);
        return false;
    }

    if (fscanf(file, "%d%d", m, n) < 2) {
        printf("Невозможно считать размеры матрицы в %s\n", filename);
        fclose(file);
        return false;
    }

    if (*m <= 0 || *m > nmax || *n <= 0 || *n > nmax) {
        printf("Некорректный размер матрицы в %s\n", filename);
        fclose(file);
        return false;
    }

    for (int i = 0; i < *m; i++) {
        for (int j = 0; j < *n; j++) {
            if (fscanf(file, "%d", &x[i][j]) < 1) {
                printf("Невозможно считать элемент в строке %d, столбце %d в %s\n", i + 1, j + 1, filename);
                fclose(file);
                return false;
            }
        }
    }

    fclose(file);
    return true;
}

bool HasZeros(int x[][nmax], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (x[i][j] == 0) {
                return true;
            }
        }
    }
    return false; // Нулевых элементов нет
}

bool HasNegativesInRows(int x[], int n) {
    for (int i = 0; i < n; i++) {
        if (x[i] < 0) {
            return true;
        }
    }
    return false; // Отрицательных элементов нет
}
