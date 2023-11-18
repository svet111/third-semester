#include <iostream>
#include <dlfcn.h>

extern "C" {
void ProcessString(char* input, char* output);
}

int main() {
    // Загрузка DLL-библиотеки
    void* handle = dlopen("/Users/svetlanazharova/Desktop/labs3/лаб8/библиотека/cmake-build-debug/libspLibrary.dylib", RTLD_LAZY);

    if (!handle) {
        std::cerr << "Ошибка загрузки библиотеки" << std::endl;
        return 1;
    }

    // Загрузка функции из библиотеки
    void (*ProcessStringFunction)(char*, char*);
    ProcessStringFunction = (void (*)(char*, char*))dlsym(handle, "ProcessString");

    if (!ProcessStringFunction) {
        std::cerr << "Ошибка загрузки функции" << std::endl;
        dlclose(handle);
        return 1;
    }

    // Использование функции
    char inputString[1024];
    std::cin.getline(inputString, 1024);
    char output[1024];

    ProcessStringFunction(inputString, output);

    std::cout << "Результат обработки: " << output << std::endl;

    // Выгрузка DLL-библиотеки
    dlclose(handle);

    return 0;
}
