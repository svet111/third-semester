#include "SetOfNumbers.h"

// Конструктор по умолчанию
SetOfNumbers::SetOfNumbers() {
    // Конструктор по умолчанию создает пустое множество
}

// Конструктор с одним параметром-числом
SetOfNumbers::SetOfNumbers(int number) {
    numbers.push_back(number);
}

// Конструктор копирования
SetOfNumbers::SetOfNumbers(const SetOfNumbers &otherSet) {
    numbers = otherSet.numbers;
}

// Деструктор
SetOfNumbers::~SetOfNumbers() {
    // Деструктор - внутренний вектор будет уничтожен автоматически
}

// Преобразование из переменной типа int в множество
SetOfNumbers SetOfNumbers::fromInt(int value) {
    SetOfNumbers set;
    set.addNumber(value);
    return set;
}

// Преобразование из множества в переменную типа int
int SetOfNumbers::toInt() const {
    int result = 0;
    for (int num : numbers) {
        result += num;
    }
    return result;
}

// Добавление числа в множество
void SetOfNumbers::addNumber(int number) {
    for (int num : numbers) {
        if (num == number) {
            return;
        }
    }
    numbers.push_back(number);
}

// Удаление числа из множества
void SetOfNumbers::removeNumber(int number) {
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (*it == number) {
            numbers.erase(it);
            return;
        }
    }
}

// Оператор присваивания
SetOfNumbers& SetOfNumbers::operator=(const SetOfNumbers &otherSet) {
    if (this == &otherSet) {
        return *this;
    }
    numbers = otherSet.numbers;
    return *this;
}
