/*#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "stringprocessing.h"


extern "C" { void ProcessString(char* input, char* output) {
    std::string inputStr(input);
    std::istringstream iss(inputStr);
    std::vector<std::string> words;

    // Разбиваем строку на слова
    for (std::string word; iss >> word; ) {
        words.push_back(word);
    }

    // Сортируем слова по длине в порядке убывания
    std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
        return a.length() > b.length();
    });

    // Формируем выходную строку
    std::string result;
    for (const std::string& word : words) {
        result += word + " ";
    }

    // Копируем результат в выходной буфер
    strcpy(output, result.c_str());
}
bool checkLetter(char chr) {
    return ((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z'));
}

bool checkDigit(char chr) {
    return ((chr >= '0') && (chr <= '9'));
}

bool checkWord(char chr) {
    return (checkLetter(chr) || checkDigit(chr));
}

}
*/
#include <string>

bool checkLetter(char chr) {
    return ((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z'));
}

bool checkDigit(char chr) {
    return ((chr >= '0') && (chr <= '9'));
}

bool checkWord(char chr) {
    return (checkLetter(chr) || checkDigit(chr));
}

extern "C" void ProcessString(char* input, char* output) {
    std::string inputStr(input);
    std::string outputStr;

    std::string currentWord;

    for (char chr : inputStr) {
        if (checkWord(chr)) {
            currentWord += chr;
        } else {
            if (!currentWord.empty()) {
                if (!outputStr.empty()) {
                    outputStr += " ";
                }
                outputStr += currentWord;
                currentWord.clear();
            }
        }
    }

    if (!currentWord.empty()) {
        if (!outputStr.empty()) {
            outputStr += " ";
        }
        outputStr += currentWord;
    }

    std::strcpy(output, outputStr.c_str());
}
