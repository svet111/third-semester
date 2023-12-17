#pragma once


#include <initializer_list>

class PopFromEmptyDequeExc {};


template<typename T>
class Deque {
private:
    const int BLOCK_SIZE = 10;
    T* data;
    int data_size;
    int begin, end;
    bool empty;

    void _setArray(T*, int, const T&);

    void _expandData();

public:
    Deque();
    Deque(const Deque<T>& old);
    ~Deque();

    void PushBack(const T&);
    void PushFront(const T&);

    T PopBack();
    T PopFront();

    bool IsEmpty();

    Deque operator = (const Deque&);

    T *_allocArray(unsigned long n);

    T *_copyArray(T *arr, unsigned long n);

    T *_expandArray(T *oldarray, unsigned long oldsize, unsigned long additional_elements);

    void _freeArray(T *arr, unsigned long n);
};