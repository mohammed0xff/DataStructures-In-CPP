#pragma once

#include <iostream>
#include <algorithm>
using namespace std;


template <typename T>
class node {
public:
    node() 
        :next(nullptr)
    {};
    node(T val)
        : data(val)
        , next(nullptr)
    {
    }
    ~node() {}

    T data;
    node* next;
};


template<typename T>
class queue
{
public:

    queue();
    ~queue();

    void push(const T&);
    void pop();

    T& front() const;
    T& back() const;

    size_t size() const;
    bool empty() const;
    void clear();

    void swap(queue& rhs);

private:
    node<T>* head;
    node<T>* tail;

    size_t m_size;
};



template<typename T>
queue<T>::queue()
    : head(nullptr)
    , tail(nullptr)
    , m_size(0)

{};


template<typename T>
queue<T>::~queue() {
    clear();
}




template<typename T>
void queue<T>::push(const T& x)
{
    node<T>* newNode = new node<T>(x);
    if (empty()) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = tail->next;
    }
    m_size++;
}


template<typename T>
void queue<T>::pop()
{
    if (empty())
    {
        std::cerr << "pop() called on an empty queue\n";
        exit(EXIT_FAILURE);
    }

    if (head == tail) {
        tail = nullptr;
    }
    node<T> *temp = head;
    head = head->next;
    delete temp;

    m_size--;
}


template<typename T>
T& queue<T>::front() const {
    if (empty())
    {
        std::cerr << "front() called on an empty queue\n";
        exit(EXIT_FAILURE);
    }
    return head->data;
}


template<typename T>
T& queue<T>::back() const {
    if (empty())
    {
        std::cerr << "back() called on an empty queue\n";
        exit(EXIT_FAILURE);
    }
    return tail->data;
}




template<typename T>
void queue<T>::swap(queue<T>& rhs)
{
    std::swap(this->head, rhs.head);
    std::swap(this->tail, rhs.tail);
    std::swap(this->m_size, rhs.m_size);
}


template<typename T>
size_t queue<T>::size() const
{
    return m_size;
}


template<typename T>
bool queue<T>::empty() const
{
    return head == nullptr;
}


template<typename T>
void queue<T>::clear() {
    if (!empty()) {
        while (head) {
            node<T> * temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
}

