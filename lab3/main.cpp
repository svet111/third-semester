//Каждая запись представляет собой 3 числа типа short int.

#include <iostream>

using namespace std;
const int kol = 3;

int ConvertBin (char* fname1, char* fname2);
int Print (char* name);
void ArrayOutput (int n, const short int x[]);
int Seek (int from, int to, char* name);

int main(int argc, char*argv[]) {
    if (argc < 2) {
        printf("Недостаточно параметров.\n");
        return 1;
    }
    if (not ConvertBin(argv[1], argv[2])) {
        return 0;
    }
    Print(argv[2]);
    Seek(1, 2, argv[2]);
    Seek(3, 2, argv[2]);
    //Seek(4, 1, argv[2]);

    Print(argv[2]);
    return 0;
}

int ConvertBin(char* fname1, char* fname2) {
    FILE* file1, *file2;
    short int a[kol];

    if ((file1 = fopen(fname1, "r")) == nullptr) {
        printf("Ошибка при открытии файла %s\n", fname1);
        fclose(file1);
        return 0;
    }

    if ((file2 = fopen(fname2, "wb")) == nullptr) {
        printf("Ошибка при открытии файла %s\n", fname2);
        fclose(file1);
        fclose(file2);
        return 0;
    }

    for (int i = 0; !feof(file1); ++i) {
        for (short int & j : a) {
            if (fscanf(file1, "%hd", &j) < 1) {
                printf("Ошибка при чтении данных из файла %s\n", fname1);
                fclose(file1);
                fclose(file2);
                return 0;
            }
        }
        fwrite(a, sizeof(short int), kol, file2);
    }
    fclose(file1);
    fclose(file2);
    return 1;
}

int Print(char* name) {
    FILE* file;
    short int answer[kol];
    if ((file = fopen(name, "rb")) == nullptr) {
        printf("Невозможно открыть файл.");
        return 0;
    }
    for (;;) {
        fread(answer, sizeof(short int), kol, file);
        if (feof(file)) {
            fclose(file);
            cout << '\n';
            return 0;
        }
        ArrayOutput(kol, answer);
    }
    return 1;
}

void ArrayOutput(int n, const short int x[]) {
    printf("[");
    for (int i = 0; i < n - 1; ++i) {
        printf("%hd, ", x[i]);
    }
    printf("%hd]", x[n - 1]);
    printf("\n");
}

int Seek(int from, int to, char* name)
{
    FILE* file;
    int n;
    short int a[kol], b[kol];
    if ((file = fopen(name, "r+b")) == nullptr)
    {
        printf("Невозможно открыть файл.");
        return 0;
    }
    fseek(file, 0, SEEK_END);
    n = ftell(file) / sizeof(short int) / kol;
    fseek(file, 0, SEEK_SET);
    if ((from > n) || (from < 0) || (to > n) || (to < 0))
    {
        cout << "Ошибка индексации: такого номера в файле нет \n";
        fclose(file);
        return 0;
    }
    fseek(file, (from - 1) * sizeof(short int) * kol, SEEK_SET);
    fread(a, sizeof(short int), kol, file);
    fseek(file, (to - 1) * sizeof(short int) * kol, SEEK_SET);
    fread(b, sizeof(short int), kol, file);
    fseek(file, (to - 1) * sizeof(short int) * kol, SEEK_SET);
    fwrite(a, sizeof(short int), kol, file);
    fseek(file, (from - 1) * sizeof(short int) * kol, SEEK_SET);
    fwrite(b, sizeof(short int), kol, file);

    fclose(file);

    return 1;
}
