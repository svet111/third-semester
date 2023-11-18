#include "SetOfNumbers.h"
#include <iostream>

int main() {
    // Конструктор по умолчанию создает пустое множество
    SetOfNumbers set1, set2;

    int choice;
    int number;
    int sum = 0;

    while (true) {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Добавить число" << std::endl;
        std::cout << "2. Удалить число" << std::endl;
        std::cout << "3. Показать сумму чисел для 1" << std::endl;
        std::cout << "4. Показать сумму чисел для 2" << std::endl;
        std::cout << "5. Копия 1 в 2" << std::endl;
        std::cout << "6. Выйти" << std::endl;

        std::cin >> choice;

        if (choice == 6) {
            break;  // Завершаем программу
        }

        switch (choice) {
            case 1:
                std::cout << "Введите число для добавления: ";
                std::cin >> number;
                set1.addNumber(number);
                break;
            case 2:
                std::cout << "Введите число для удаления: ";
                std::cin >> number;
                set1.removeNumber(number);
                break;
            case 3:
                sum = set1.toInt();
                std::cout << "Сумма чисел в множестве 1: " << sum << std::endl;
                break;
            case 4:
                sum = set2.toInt();
                std::cout << "Сумма чисел в множестве 2: " << sum << std::endl;
                break;
            case 5:
                set2 = SetOfNumbers(set1);
                break;
            default:
                std::cout << "Неверный выбор. Пожалуйста, выберите снова." << std::endl;
        }
    }

    return 0; // Деструктор автоматически уничтожит объект set1 и set2 при завершении программы
}
