#include <iostream>
#include <fstream>
#include <algorithm>
#include "ForwardedList.h"
#include "ForwardedList.cpp"
#include "Deque.cpp"

#include "Deque.h"
#include <locale.h>
#include <string>


/*
    однонаправленный список;
    дек на основе массива.

    Если в списке из целых чисел количество элементов, кратных 7, больше половины общего количества элементов списка, удалить из списка чётные элементы.
    Если в списке из вещественных чисел есть положительные элементы, удалить из списка элементы, большие заданного числа.

    Создать структуру из символов. Разделить её содержимое на знаки препинания и прочие символы.
    Создать структуру из целых чисел. Разделить её содержимое на числа, кратные и некратные заданному числу.
*/


template <typename T>
std::ifstream& operator >> (std::ifstream& from, ForwardedList<T>& list) {
    T i;
    while (from >> i)
        list.PushBack(i);

    return from;
}


template <typename T>
std::ifstream& operator >> (std::ifstream& from, Deque<T>& deque) {
    T i;
    while (from >> i) {
        if (static_cast<T>(i) == i) {
            deque.PushBack(static_cast<T>(i));
        } else {
            std::cerr << "Введен элемент другого типа" << std::endl;
        }
    }
    return from;
}



template <typename T>
std::ostream& operator << (std::ostream& to, ForwardedList<T>& list) {
    if (list.GetLength() == 0) {
        to << "<Empty List>";
        return to;
    }
    for (typename ForwardedList<T>::Iterator i = list.GetBegin(); i; ++i)
        to << *i << '\t';

    return to;
}


template <typename T>
std::ostream& operator << (std::ostream& to, Deque<T>& deque) {
    if (deque.IsEmpty()) {
        to << "<Empty Deque>";
        return to;
    }

    Deque<T> temp(deque);

    while (!temp.IsEmpty())
        to << temp.PopFront() << '\t';

    return to;
}

//Если в списке из целых чисел количество элементов, кратных 7, больше половины общего количества элементов списка,
bool isMoreThanHalfMultiplesOfSeven(const ForwardedList<int>& numbers) {
    if (numbers.GetLength() == 0) {
        return false;
    }

    int totalElements = 0;
    int multiplesOfSevenCount = 0;

    for (ForwardedList<int>::Iterator i = numbers.GetBegin(); i; ++i) {
        totalElements++;

        if (*i % 7 == 0) {
            multiplesOfSevenCount++;
        }
    }

    return multiplesOfSevenCount > totalElements / 2;
}


// удалить из списка чётные элементы.
template <typename T>
void deleteEvenNumbers(ForwardedList<T>& numbers) {
    typename ForwardedList<T>::Iterator i = numbers.GetBegin();

    while (i) {
        if (*i % 2 == 0) {
            i = numbers.RemoveElement(i);
        } else {
            ++i;
        }
    }
}


//Если в списке из вещественных чисел есть положительные элементы,
bool hasPositive(const ForwardedList<double>& numbers) {
    for (ForwardedList<double>::Iterator i = numbers.GetBegin(); i; ++i) {
        if (*i > 0) {
            return true;
        }
    }

    return false;
}

// удалить из списка элементы, большие заданного числа.
void removeGreaterThan(ForwardedList<double>& numbers, double threshold) {
    ForwardedList<double>::Iterator i = numbers.GetBegin();
    while (i) {
        if (*i > threshold) {
            i = numbers.RemoveElement(i);
        } else {
            ++i;
        }
    }
}


//Создать структуру из целых чисел. Разделить её содержимое на числа, кратные и некратные заданному числу.
void separateMultiples(const Deque<int>& what, int divisor, Deque<int>& multiples, Deque<int>& nonMultiples) {
    Deque<int> temp = what;

    while (!temp.IsEmpty()) {
        int val = temp.PopFront();
        if (val % divisor == 0)
            multiples.PushBack(val);
        else
            nonMultiples.PushBack(val);
    }
}


//Создать структуру из символов. Разделить её содержимое на знаки препинания и прочие символы.
void separatePunctuation(const Deque<char>& characters, Deque<char>& punc, Deque<char>& other) {
    std::string marks(",.!?;:");
    Deque<char> temp = characters;

    while (!temp.IsEmpty()) {
        char val = temp.PopFront();

        if (std::find(marks.begin(), marks.end(), val) != marks.end()) {
            punc.PushBack(val);
        } else {
            other.PushBack(val);
        }
    }
}



int main(int argv, const char* argc[])
{
    setlocale(0, "");

    if (argv < 5) {
        std::cout << "Недостаточно параметров" << std::endl;
        return 0;
    }

    std::ifstream f1(argc[1]);
    if (!f1.is_open()) {
        std::cout << "Не удалось открыть файл " << argc[1] << std::endl;
        return 0;
    } ForwardedList<int> list1;
    f1 >> list1; f1.close();


    std::ifstream f2(argc[2]);
    if (!f2.is_open()) {
        std::cout << "Не удалось открыть файл " << argc[2] << std::endl;
        return 0;
    } ForwardedList<double> list2;
    f2 >> list2; f2.close();


    std::ifstream f3(argc[3]);
    if (!f3.is_open()) {
        std::cout << "Не удалось открыть файл " << argc[3] << std::endl;
        return 0;
    } Deque<int> deque1;
    double te;
    bool flag = false;
    while (f3 >> te) {
        if (static_cast<int>(te) != te) {
            flag = true;
            continue;
        }
        deque1.PushBack(static_cast<int>(te));
    }
    f3.close();


    std::ifstream f4(argc[4]);
    if (!f4.is_open()) {
        std::cout << "Не удалось открыть файл " << argc[4] << std::endl;
        return 0;
    } Deque<char> deque2;
    f4 >> deque2; f4.close();


    std::cout << "Список целых чисел:" << std::endl;
    std::cout << list1 << std::endl;
    if (isMoreThanHalfMultiplesOfSeven(list1)) {
        std::cout << "Чисел делящихся на 7, больше половины; \nУдалили четные числа:" << std::endl;
        deleteEvenNumbers(list1);
        std::cout << list1 << std::endl;
    }
    else
        std::cout << "Чисел делящихся на 7, меньше половины, список не меняем." << std::endl;


    std::cout << "Список вещественных чисел:" << std::endl;
    std::cout << list2 << std::endl;
    if (hasPositive(list2)) {
        std::cout << "Введите число:" << std::endl;
        int div;
        std::cin >> div;
        std::cout << "В списке есть положительные элементы; \nУдалили все элементы больше заданного числа:" << std::endl;
        removeGreaterThan(list2, div);
        std::cout << list2 << std::endl;
    }
    else
        std::cout << "В списке не оказалось положительных элементов, список не меняем" << std::endl;


    std::cout << "Дек из символов:" << std::endl;
    std::cout << deque2 << std::endl;
    Deque<char> punc, other;
    separatePunctuation(deque2, punc, other);
    std::cout << "Разделили дек на два со знаками препинания и с остальными символами:" << std::endl;
    std::cout << punc << std::endl << other << std::endl;


    std::cout << "Дек целых чисел:" << std::endl;
    std::cout << deque1 << std::endl;
    if (flag) {
        std::cout << "Введен другой тип элемента" << std::endl;
    }
    std::cout << "Введите число, кратность на которое будет проверена:" << std::endl;
    int del;
    std::cin >> del;

    Deque<int> d1, d2;
    separateMultiples(deque1, del, d1, d2);
    std::cout << "Разделили дек на два - с некратными числами и кратными числу соответственно:" << std::endl;
    std::cout << d2 << std::endl << d1 << std::endl;

    return 0;
}