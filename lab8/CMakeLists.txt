cmake_minimum_required(VERSION 3.25)
project(DynamicLibraryUsage)

set(CMAKE_CXX_STANDARD 11)

add_executable(DynamicLibraryUsage dynamic_main.cpp)

# Укажите путь к библиотеке и имя библиотеки
target_link_libraries(DynamicLibraryUsage /Users/svetlanazharova/Desktop/labs3/лаб8/библиотека/cmake-build-debug/libspLibrary.dylib)
