#include <iostream>
#include <fstream>
#include "Except.h"

//Необходимо генерировать исключения в следующих ситуациях: попытка повторного добавления элемента в множество;
// попытка добавить в множество элемент, значение которого лежит вне диапазона разрешённых элементов.


int main() {
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return 1;
    }

    int size1, size2;
    SetOfNumbers set1(1, 100), set2(1, 100);

    // Считываем размер первого множества
    inputFile >> size1;

    // Считываем элементы первого множества
    for (int i = 0; i < size1; ++i) {
        int element;
        inputFile >> element;
        set1.addNumber(element);
    }

    // Считываем размер второго множества
    inputFile >> size2;

    // Считываем элементы второго множества
    for (int i = 0; i < size2; ++i) {
        int element;
        inputFile >> element;
        set2.addNumber(element);
    }

    inputFile.close();
    set1.printSet();
    set2.printSet();

    try {
        int n;
        std::cin >> n;
        set1.addNumber(n);
        set1.printSet();
        //(set1 + set2).printSet();
        //(set1 + set2).addNumber(6);
        std::cout << std::endl;
    } catch (const SetException& ex) {
        std::cout << "Исключение: " << ex.GetMessage() << std::endl;
    }

    return 0;
}
