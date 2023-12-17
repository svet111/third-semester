
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
    SetOfNumbers operator-(const SetOfNumbers &otherSet) const ;

    bool operator==(const SetOfNumbers &otherSet) const;
    bool operator!=(const SetOfNumbers &otherSet) const;

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

    friend SetOfNumbers operator+(const SetOfNumbers &set1, const SetOfNumbers &set2);
  //  friend SetOfNumbers operator-(const SetOfNumbers &set1, const SetOfNumbers &set2);
    friend SetOfNumbers operator*(const SetOfNumbers &set1, const SetOfNumbers &set2);

};

#endif

