#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

int calculateSumInRange(const std::vector<int>& arr, int start, int end) {
    int sum = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] >= start && arr[i] <= end) {
            sum += arr[i];
        }
    }
    return sum;
}

void inputOutput(const std::string& filename, std::vector<int>& array) {
    FILE* file = fopen(filename.c_str(), "r");
    if (!file) {
        std::cerr << "Ошибка при открытии файлов." << std::endl;
        return;
    }

    int num;
    while (fscanf(file, "%d", &num) != EOF) {
        array.push_back(num);
    }
    fclose(file);
    return;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Недостаточно параметров.\n");
        return 1;
    }

    std::vector<int> array1, array2, array3;
    int startRange, endRange;

    inputOutput(argv[1], array1);
    inputOutput(argv[2], array2);
    inputOutput(argv[3], array3);

    std::cout << "Введите начало и конец диапазона: ";
    std::cin >> startRange >> endRange;

    int sum1 = calculateSumInRange(array1, startRange, endRange);
    int sum2 = calculateSumInRange(array2, startRange, endRange);
    int sum3 = calculateSumInRange(array3, startRange, endRange);

    std::cout << "Сумма элементов в заданном диапазоне для массива 1: " << sum1 << std::endl;
    std::cout << "Сумма элементов в заданном диапазоне для массива 2: " << sum2 << std::endl;
    std::cout << "Сумма элементов в заданном диапазоне для массива 3: " << sum3 << std::endl;

    if (sum1 > sum2 && sum1 > sum3) {
        std::cout << "Сумма элементов в заданном диапазоне максимальна в массиве 1." << std::endl;
    } else if (sum2 > sum1 && sum2 > sum3) {
        std::cout << "Сумма элементов в заданном диапазоне максимальна в массиве 2." << std::endl;
    } else if (sum3 > sum1 && sum3 > sum2) {
        std::cout << "Сумма элементов в заданном диапазоне максимальна в массиве 3." << std::endl;
    } else if (sum3 == sum1 && sum3 == sum2) {
        std::cout << "Сумма элементов в заданном диапазоне совпадают в трех массивах" << std::endl;
    } else {
        std::cout << "Суммы элементов в заданном диапазоне совпадают в двух массивах." << std::endl;
    }


    return 0;
}
