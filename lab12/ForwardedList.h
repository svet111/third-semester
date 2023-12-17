#pragma once


struct EmptyIteratorRefExc {};
struct AccessingIncorrectElementExc {};


template <typename T>
class ForwardedList {
private:
    class ListNode {
    public:
        ListNode(const T&, ListNode* = nullptr);
        T value;
        ListNode* next = nullptr;
    };

    ListNode* head;
    ListNode* back;
    int length;

public:

    class Iterator {
    private:
        ListNode* cur;

    public:
        Iterator(ListNode* = nullptr);

        Iterator& operator ++ (); // prefix
        Iterator operator ++ (int); // postfix

        T& operator * ();

        operator bool();

        friend class ForwardedList;
    };


    ForwardedList();
    ForwardedList(const ForwardedList&);
    ~ForwardedList();


    void PushBack(const T&);
    void PushFront(const T&);
    void InsertAfter(Iterator, const T&);

    Iterator RemoveElement(const Iterator);
    void Clear();

    Iterator GetBegin() const;
    Iterator GetEnd() const;

    int GetLength() const;

    ForwardedList<T> operator = (const ForwardedList<T>&);
};