#include "SetOfNumbers.h"
#include <iostream>
#include <fstream>

int main() {
    std::ifstream inputFile("input.txt"); // Замените "input.txt" на имя вашего файла

    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return 1;
    }

    int size1, size2;
    SetOfNumbers set1, set2, unionSet, pereSet, diffSet;

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

    std::cout << "Присваивание: ";
    SetOfNumbers sameSet = set2;
    sameSet.printSet();

    std::cout << "Равны ли множества: ";
    if (set1 == set2) {
        std::cout << "Равны\n";
    }
    if (set1 != set2) {
        std::cout << "Не равны\n";
    }

    //Операция объединения
    unionSet = set1 + set2;
    std::cout << "Объединение множеств: ";
    unionSet.printSet();

    //
    pereSet = set1 * set2;
    std::cout << "Пересечение множеств: ";
    pereSet.printSet();

    //
    diffSet = set1 - set2;
    std::cout << "Вычитание множеств: ";
    diffSet.printSet();

    int elem;
    std::cin >> elem;
    set1 += elem;
    std::cout << "Множество 1 после добавления числа:";
    set1.printSet();


    return 0; // Деструктор автоматически уничтожит объект set1 и set2 при завершении программы
}
