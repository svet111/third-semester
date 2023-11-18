#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <clocale>
#include <cwctype>

bool isAlpha(wchar_t chr);
bool isDigit(wchar_t chr);
bool isWord(wchar_t chr);
std::wstring reverseLettersInWords(const std::wstring& input);

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Устанавливаем локаль для корректной обработки кириллицы

    if (argc > 2) {
        FILE* input = fopen(*(argv + 1), "r");
        FILE* output = fopen(*(argv + 2), "w");

        if (input != nullptr && output != nullptr) {
            std::vector<std::wstring> words;

            // Чтение слов из входного файла и сохранение их в векторе
            wchar_t str[256]{};
            while (fgetws(str, 256, input)) {
                std::wstring line(str);
                std::wstring word;
                for (wchar_t chr : line) {
                    if (isWord(chr)) {
                        word += chr;
                    } else if (!word.empty()) {
                        words.push_back(word);
                        word.clear();
                    }
                }
                if (!word.empty()) {
                    words.push_back(word);
                }
            }

            // Сортировка слов в порядке убывания длины
            std::sort(words.begin(), words.end(), [](const std::wstring& a, const std::wstring& b) {
                return a.size() > b.size();
            });

            // Формирование и запись строки в выходной файл
            for (const std::wstring& word : words) {
                fputws(word.c_str(), output);
                fputwc(L' ', output);  // Добавляем пробел между словами
            }

            fclose(input);
            fclose(output);
            return 0;
        } else {
            if (input == nullptr && output == nullptr) {
                printf("Can't open files: %s | %s\n", *(argv + 1), *(argv + 2));
            } else if (output == nullptr) {
                printf("Can't open file: %s\n", *(argv + 2));
                fclose(input);
            } else if (input == nullptr) {
                printf("Can't open file: %s\n", *(argv + 1));
                fclose(output);
            }
            return 3;
        }
    } else {
        printf("Not enough arguments\n");
        return 2;
    }
}

bool isAlpha(wchar_t chr) {
    return (iswalpha(chr) || (chr == L'Ё') || (chr == L'ё'));  // Обработка буквы Ё и её
}

bool isDigit(wchar_t chr) {
    return iswdigit(chr);
}

bool isWord(wchar_t chr) {
    return (isAlpha(chr) || isDigit(chr));
}
