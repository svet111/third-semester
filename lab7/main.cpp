#include <iostream>
#include <climits>

//Написать функцию, которая в числе x инвертирует n бит, находящихся справа от позиции p, остальные биты остаются без изменения.

void printBinary(unsigned long long x) {
    /*bool leadingZero = true; // Флаг для отслеживания ведущих нулей
    for (int i = size - 1; i >= 0; i--) {
        bool bit = (x >> i) & 1;
        if (bit || !leadingZero) {
            std::cout << bit;
            leadingZero = false;
        }
    }
    if (leadingZero) {
        std::cout << "0"; // Если число было нулевым, вывести хотя бы один ноль
    }*/
    int size = sizeof(x) * 8;
    for (int i = size - 1; i >= 0; i--) {
        std::cout << ((x >> i) & 1);
    }
}

unsigned long long invertBits(unsigned long long x, int p, int n) {
    unsigned long long mask = ((1ull << (n+1)) - 1) << (p - n);
    return x ^ mask;
}

bool checkBitInversion(unsigned long long original, unsigned long long inverted, int p, int n) {
    unsigned long long mask = ((1ull << (n+1)) - 1) << (p - n);
    return (original ^ inverted) == mask;
}

int main() {
    unsigned long long x;
    int p, n;

    std::cout << "Введите число: ";
    std::cin >> x;
    if (x > ULLONG_MAX) {
        std::cout << "Введено число, которое превышает максимальное значение (" << ULLONG_MAX << ") для 64-битного числа." << std::endl;
        return 1;
    }
    std::cout << "Введите позицию (0 - правый бит): ";
    std::cin >> p;
    std::cout << "Введите количество битов для инвертирования: ";
    std::cin >> n;

    if (p < 0 || n < 0 || p + n > 64) {
        std::cout << "Некорректные значения p и n." << std::endl;
        return 1;
    }

    unsigned long long result = invertBits(x, p, n);
    std::cout << "Исходное число (двоичное): ";
    printBinary(x);
    std::cout << " (десятичное): " << x << " (шестнадцатеричное): " << std::hex << std::uppercase << x << std::dec << std::endl;

    std::cout << "Результат инверсии (двоичный): ";
    printBinary(result);
    std::cout << " (десятичный): " << result << " (шестнадцатеричный): " << std::hex << std::uppercase << result << std::dec << std::endl;

    if (checkBitInversion(x, result, p, n)) {
        std::cout << "Инверсия выполнена корректно." << std::endl;
    } else {
        std::cout << "Ошибка в инверсии." << std::endl;
    }

    return 0;
}
