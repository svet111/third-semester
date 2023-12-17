#include "ForwardedList.h"


template <typename T>
ForwardedList<T>::ListNode::ListNode(const T& val, ListNode* n) {
    value = val;
    next = n;
}


template <typename T>
ForwardedList<T>::Iterator::Iterator(ListNode* node) {
    cur = node;
}


template <typename T>
typename ForwardedList<T>::Iterator& ForwardedList<T>::Iterator::operator++() {
    if (cur) {
        cur = cur->next;
    }
    return *this;
}

template <typename T>
typename ForwardedList<T>::Iterator ForwardedList<T>::Iterator::operator ++ (int) { // postfix
    Iterator copy = *this; // ���������� � ���������� �� �� �� ����
    cur = cur->next;
    return copy;
}


template <typename T>
ForwardedList<T>::Iterator::operator bool() {
    return cur != nullptr;
}


template <typename T>
T& ForwardedList<T>::Iterator::operator*() {
    if (cur == nullptr) throw EmptyIteratorRefExc();

    return cur->value;
}


template <typename T>
ForwardedList<T>::ForwardedList() {
    head = nullptr;
    length = 0;
}


template <typename T>
ForwardedList<T>::ForwardedList(const ForwardedList& old) {
    head = nullptr;
    length = 0;

    for (Iterator el = old.GetBegin(); el; ++el) PushBack(*el);
}


template <typename T>
ForwardedList<T>::~ForwardedList<T>() {
    for (Iterator i = GetBegin(); i; i = RemoveElement(i)) {};
}


template <typename T>
void ForwardedList<T>::PushBack(const T& element) {
    ListNode* newnode = new ListNode(element);


    if (head == nullptr) {
        head = newnode;
    }
    else {
        ListNode* tail = head;
        while (tail->next != nullptr) tail = tail->next;

        tail->next = newnode;
    }

    length++;
}


template <typename T>
void ForwardedList<T>::PushFront(const T& element) {
    ListNode* newnode = new ListNode(element);

    newnode->next = head;
    head = newnode;

    length++;
}


template <typename T>
void ForwardedList<T>::InsertAfter(Iterator element, const T& newelement) {
    if (!element) throw AccessingIncorrectElementExc();

    ListNode* newnode = new ListNode(newelement);

    ListNode* cur = element.cur;

    newnode->next = cur->next;
    cur->next = newnode;

    length++;
}


template <typename T>
void ForwardedList<T>::Clear() {
    for (Iterator i = GetBegin(); i; i = RemoveElement(i)) {};
}


template <typename T>
typename ForwardedList<T>::Iterator ForwardedList<T>::RemoveElement(const Iterator element) {
    if (element.cur == head) {
        ListNode* oldhead = head;
        head = head->next;
        delete oldhead;
        length--;
        return Iterator(head);
    }
    else {
        ListNode* prev = head;
        while (prev->next != element.cur) prev = prev->next;

        if (prev == nullptr) throw AccessingIncorrectElementExc();
        prev->next = element.cur->next;
        delete element.cur;

        length--;
        if (prev->next)
            return Iterator(prev->next);
        else
            return Iterator(prev);
    }
}


template <typename T>
typename ForwardedList<T>::Iterator ForwardedList<T>::GetBegin() const {
    return Iterator(head);
}

template <typename T>
typename ForwardedList<T>::Iterator ForwardedList<T>::GetEnd() const {
    return Iterator(back->next);
}


template <typename T>
int ForwardedList<T>::GetLength() const {
    return length;
}


template <typename T>
ForwardedList<T> ForwardedList<T>::operator=(const ForwardedList<T>& rvalue) {
    if (&rvalue == this) return *this;

    for (Iterator i = GetBegin(); i; i = RemoveElement(i)) {};

    for (Iterator i = rvalue.GetBegin(); i; ++i) {
        PushBack(*i);
    }

    return *this;
}