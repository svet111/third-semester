
#ifndef SETOFNUMBERS_H
#define SETOFNUMBERS_H

#include <vector>

class SetOfNumbers {
public:
    // Конструктор по умолчанию
    SetOfNumbers();

    // Конструктор с одним параметром-числом
    SetOfNumbers(int number);

    // Конструктор копирования
    SetOfNumbers(const SetOfNumbers &otherSet);

    // Деструктор
    ~SetOfNumbers();

    // Преобразование из переменной типа int в множество
    static SetOfNumbers fromInt(int value);

    // Преобразование из множества в переменную типа int
    int toInt() const;

    // Добавление числа в множество
    void addNumber(int number);

    // Удаление числа из множества
    void removeNumber(int number);

    // Оператор присваивания
    SetOfNumbers& operator=(const SetOfNumbers &otherSet);

private:
    std::vector<int> numbers;
};

#endif

