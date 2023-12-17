#include "Except.h"
#include <iostream>

const char* SetException::GetMessage() const {
    return msg_buffer;
}

DuplicateElementException::DuplicateElementException(int element) : SetException() {
    snprintf(msg_buffer, sizeof(msg_buffer), "Попытка повторного добавления элемента: %d", element);
}

OutOfRangeElementException::OutOfRangeElementException(int element, int min, int max) : SetException() {
    snprintf(msg_buffer, sizeof(msg_buffer), "Элемент %d вне диапазона [%d, %d]", element, min, max);
}

SetOfNumbers::SetOfNumbers(int min, int max) : minValue(min), maxValue(max) {}

SetOfNumbers::SetOfNumbers() {}

SetOfNumbers::SetOfNumbers(int number) {
    numbers.push_back(number);
}

SetOfNumbers::SetOfNumbers(const SetOfNumbers& otherSet) {
    numbers = otherSet.numbers;
}

SetOfNumbers::~SetOfNumbers() {}

SetOfNumbers SetOfNumbers::fromInt(int value) {
    SetOfNumbers set;
    set.addNumber(value);
    return set;
}

int SetOfNumbers::toInt() const {
    int result = 0;
    for (int num : numbers) {
        result += num;
    }
    return result;
}

SetOfNumbers& SetOfNumbers::operator=(const SetOfNumbers& otherSet) {
    if (this == &otherSet) {
        return *this;
    }
    numbers = otherSet.numbers;
    return *this;
}

bool SetOfNumbers::operator==(const SetOfNumbers& otherSet) const {
    return numbers == otherSet.numbers;
}

bool SetOfNumbers::operator!=(const SetOfNumbers& otherSet) const {
    return !(*this == otherSet);
}

SetOfNumbers SetOfNumbers::operator+(const SetOfNumbers& otherSet) const {
    SetOfNumbers result(*this);
    for (int num : otherSet.numbers) {
        bool isDuplicate = false;
        for (int existingNum : result.numbers) {
            if (num == existingNum) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            result.numbers.push_back(num);
        }
    }
    return result;
}

SetOfNumbers SetOfNumbers::operator*(const SetOfNumbers& otherSet) const {
    SetOfNumbers result;
    for (int num : numbers) {
        if (otherSet.containsNumber(num)) {
            result.numbers.push_back(num);
        }
    }
    return result;
}

SetOfNumbers SetOfNumbers::operator-(const SetOfNumbers& otherSet) const {
    SetOfNumbers result;
    for (int num : numbers) {
        if (!otherSet.containsNumber(num)) {
            result.numbers.push_back(num);
        }
    }
    return result;
}

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

void SetOfNumbers::addNumber(int number) {
    if (number < minValue || number > maxValue) {
        throw OutOfRangeElementException(number, minValue, maxValue);
    }

    for (int num : numbers) {
        if (num == number) {
            throw DuplicateElementException(number);
        }
    }
    numbers.push_back(number);
}

void SetOfNumbers::removeNumber(int number) {
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (*it == number) {
            numbers.erase(it);
            return;
        }
    }
}

void SetOfNumbers::printSet() const {
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

bool SetOfNumbers::containsNumber(int number) const {
    return std::find(numbers.begin(), numbers.end(), number) != numbers.end();
}
