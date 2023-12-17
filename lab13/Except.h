#ifndef EXCEPT_H
#define EXCEPT_H

#include <vector>

class SetException {
protected:
    char msg_buffer[100];

public:
    virtual const char* GetMessage() const;
    virtual ~SetException() = default;
};

class DuplicateElementException : public SetException {
public:
    DuplicateElementException(int element);
};

class OutOfRangeElementException : public SetException {
public:
    OutOfRangeElementException(int element, int min, int max);
};

class SetOfNumbers {
public:
    SetOfNumbers();
    SetOfNumbers(int number);
    SetOfNumbers(const SetOfNumbers& otherSet);
    ~SetOfNumbers();
    static SetOfNumbers fromInt(int value);
    int toInt() const;

    SetOfNumbers& operator=(const SetOfNumbers& otherSet);

    bool operator==(const SetOfNumbers& otherSet) const;
    bool operator!=(const SetOfNumbers& otherSet) const;

    SetOfNumbers operator+(const SetOfNumbers& otherSet) const;
    SetOfNumbers operator*(const SetOfNumbers& otherSet) const;
    SetOfNumbers operator-(const SetOfNumbers& otherSet) const;
    SetOfNumbers& operator+=(int number);

    void addNumber(int number);
    void removeNumber(int number);
    void printSet() const;
    bool containsNumber(int number) const;
    SetOfNumbers(int min, int max);

private:
    std::vector<int> numbers;
    int minValue;
    int maxValue;
};

#endif
