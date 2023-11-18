#include <iostream>
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

// Оператор присваивания
SetOfNumbers& SetOfNumbers::operator=(const SetOfNumbers &otherSet) {
    if (this == &otherSet) {
        return *this;
    }
    numbers = otherSet.numbers;
    return *this;
}
// Оператор сравнения
bool SetOfNumbers::operator==(const SetOfNumbers &otherSet) const {
    return numbers == otherSet.numbers;
}

bool SetOfNumbers::operator!=(const SetOfNumbers &otherSet) const {
    return !(*this == otherSet);
}

// Оператор объединения множеств
SetOfNumbers SetOfNumbers::operator+(const SetOfNumbers &otherSet) const {
    SetOfNumbers result(*this); // Создаем копию текущего множества
    for (int num : otherSet.numbers) {
        bool isDuplicate = false;
        for (int existingNum : result.numbers) {
            if (num == existingNum) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            result.numbers.push_back(num); // Добавляем элементы из другого множества, если их нет в текущем
        }
    }
    return result;
}

// Оператор пересечения множеств
SetOfNumbers SetOfNumbers::operator*(const SetOfNumbers &otherSet) const {
    SetOfNumbers result;
    for (int num : numbers) {
        if (otherSet.containsNumber(num)) {
            result.numbers.push_back(num); // Добавляем элементы, присутствующие в обоих множествах
        }
    }
    return result;
}


// Оператор вычитания множеств
SetOfNumbers SetOfNumbers::operator-(const SetOfNumbers &otherSet) const {
    SetOfNumbers result;
    for (int num : numbers) {
        if (!otherSet.containsNumber(num)) {
            result.numbers.push_back(num); // Добавляем элементы, отсутствующие в другом множестве
        }
    }
    return result;
}


// Оператор добавления нового элемента в множество
SetOfNumbers& SetOfNumbers::operator+=(int number) {
    bool isDuplicate = false;
    for (int num : numbers) {
        if (num == number) {
            isDuplicate = true;
            break;
        }
    }
    if (!isDuplicate) {
        numbers.push_back(number);
    }
    return *this;
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

//Вывод множества на экран
void SetOfNumbers::printSet() const {
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

bool SetOfNumbers::containsNumber(int number) const {
    return std::find(numbers.begin(), numbers.end(), number) != numbers.end();
}
