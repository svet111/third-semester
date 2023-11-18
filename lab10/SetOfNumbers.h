
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

    // Оператор присваивания
    SetOfNumbers& operator=(const SetOfNumbers &otherSet);

    bool operator==(const SetOfNumbers &otherSet) const;
    bool operator!=(const SetOfNumbers &otherSet) const;

    // Оператор объединения множеств
    SetOfNumbers operator+(const SetOfNumbers &otherSet) const;

    // Оператор пересечения множеств
    SetOfNumbers operator*(const SetOfNumbers &otherSet) const;

    // Оператор вычитания множеств
    SetOfNumbers operator-(const SetOfNumbers &otherSet) const;
    SetOfNumbers& operator+=(int number);

    // Добавление числа в множество
    void addNumber(int number);

    // Удаление числа из множества
    void removeNumber(int number);

    //Вывод множества на экран
    void printSet() const;
    bool containsNumber(int number) const;

private:
    std::vector<int> numbers;
};

#endif

