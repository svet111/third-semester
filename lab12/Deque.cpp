#include "Deque.h"
#include <new>
#include <cstring>


template<typename T>
T* Deque<T>::_copyArray(T* arr, size_t n) {
    void* newdata = operator new[](sizeof(T)*n);
    return reinterpret_cast<T*>(std::memmove(newdata, arr, sizeof(T) * n));
}


template<typename T>
T* Deque<T>::_allocArray(size_t n) {
    return reinterpret_cast<T*>(operator new[](sizeof(T)* n));
}


template<typename T>
T* Deque<T>::_expandArray(T* oldarray, size_t oldsize, size_t additional_elements) {
    void* newdata = operator new[](sizeof(T)* (oldsize + additional_elements));
    T* res = reinterpret_cast<T*>(std::memmove(newdata, oldarray, sizeof(T) * oldsize));

    operator delete[](oldarray, sizeof(T)* oldsize);

    return res;
}


template<typename T>
void Deque<T>::_setArray(T* arr, int index, const T& element) {
    new(arr + index) T(element);
}


template<typename T>
void Deque<T>::_freeArray(T* arr, size_t n) {
    operator delete[](arr, sizeof(T)* n);
}


template<typename T>
Deque<T>::Deque() {
    data = _allocArray(BLOCK_SIZE);
    data_size = BLOCK_SIZE;
    begin = end = 0;
    empty = true;
}


template<typename T>
Deque<T>::~Deque() {
    while (!IsEmpty()) PopBack();
    _freeArray(data, data_size);
}


template<typename T>
Deque<T>::Deque(const Deque<T>& old) {
    data_size = old.data_size;
    data = new T[data_size];

    // Use std::copy to copy elements
    bcopy(old.data, data, sizeof(T) * data_size);

    begin = old.begin;
    end = old.end;
    empty = old.empty;
}


template <typename T>
void Deque<T>::_expandData() {
    if (end != begin) return;
    int newspace = BLOCK_SIZE * (begin / BLOCK_SIZE + 1);
    data = _expandArray(data, data_size, newspace);
    std::memmove(data + data_size, data, begin * sizeof(T));
    end = data_size + begin;
    data_size += newspace;
}


template<typename T>
void Deque<T>::PushBack(const T& element) {
    if (!empty && (begin == end)) { // ��� �����
        _expandData();
    }

    _setArray(data, end, element);

    end = (end + 1) % data_size;

    empty = false;
}


template<typename T>
void Deque<T>::PushFront(const T& element) {
    if (!empty && (begin == end)) { // ��� �����
        _expandData();
    }

    if (begin == 0)
        begin = data_size - 1;
    else
        begin--;

    _setArray(data, begin, element);

    empty = false;
}


template<typename T>
T Deque<T>::PopBack() {
    if (empty) throw PopFromEmptyDequeExc();

    if (end == 0)
        end = data_size - 1;
    else
        end--;

    empty = begin == end;
    T res(data[end]);

    data[end].~T();

    return res;
}


template<typename T>
T Deque<T>::PopFront() {
    if (empty) throw PopFromEmptyDequeExc();

    T res(data[begin]);
    data[begin].~T();
    begin = (begin + 1) % data_size;
    empty = begin == end;
    return res;
}


template<typename T>
bool Deque<T>::IsEmpty() {
    return empty;
}


template<typename T>
Deque<T> Deque <T>::operator =(const Deque<T>& rvalue) {
    if (&rvalue == this) return *this;

    _freeArray(data, data_size);

    data = _copyArray(rvalue.data, rvalue.data_size);
    data_size = rvalue.data_size;
    begin = rvalue.begin;
    end = rvalue.end;
    empty = rvalue.empty;

    return *this;
}