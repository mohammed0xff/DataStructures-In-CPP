#pragma once

#include <iostream>
using namespace std;


const int MaxSize = 100;


template<typename T>
class stack
{
public:

    stack(int size = MaxSize);
    ~stack();
    // Copy constructor
    stack(const stack& rhs);
    // Move constructor
    stack(stack&& rhs);

    // Copy assignment
    stack<T>& operator= (const stack<T>& rhs);
    // Move assignment
    stack<T>& operator= (const stack<T>&& rhs);

    void push(const T&);
    void pop();
    void swap(stack& rhs);

    bool operator==(const stack& rhs);
    bool operator!=(const stack& rhs);

    T top();
    size_t size() const;
    bool full() const;
    bool empty() const;

private:
    T* m_data;
    size_t m_capacity;
    int m_size;
};



// Constructor
template<typename T>
stack<T>::stack(int size)
    : m_data(new T[size])
    , m_size(0)
    , m_capacity(size)

{};

// Copy Constructor
template<typename T>
stack<T>::stack(const stack<T>& rhs)
    : m_data(new int[MaxSize])
    , m_size(rhs.m_size)
    , m_capacity(rhs.m_capacity)

{
    for (int i = 0; i <= rhs.m_size; i++) {
        this->m_data[i] = rhs.m_data[i];
    }
};

// Move Constructor
template<typename T>
stack<T>::stack(stack<T>&& rhs)
    : m_data(rhs.m_data)
    , m_size(rhs.m_size)
    , m_capacity(rhs.m_capacity)

{
    rhs.m_data = nullptr;
    // so what happens when the desturctor of that stack called ????
    // deleting a nullptr has no effect .. but if you commented this 
    // the data moved will be deleted with the referenced stack rhs.

};



// Copy assignment operator
template<typename T>
stack<T>& stack<T>::operator= (const stack& rhs) {

    if (this != rhs) {
        delete[] this->m_data;
        m_data = new int[MaxSize];
        m_capacity = rhs.m_capacity;

        for (int i = 0; i <= rhs.m_size; i++) {
            push(rhs.m_data[i]);
        }
    }
    return *this;
}



// Move assignment operator 
template<typename T>
stack<T>& stack<T>::operator= (const stack<T>&& rhs)
{
    if (this != rhs) {

        delete[] m_data;

        m_data = rhs.m_data;
        m_capacity = rhs.m_capacity;
        m_size = rhs.m_size;

        rhs.m_data = nullptr;
    }
}

// Destructor
template<typename T>
stack<T>::~stack() {
    // its fine to delete a null pointer, 
    // you dont need to check if it has data or not.
    delete[] m_data;
}


//
// operations
//

template<typename T>
void stack<T>::push(const T& x)
{
    if (full()) {
        std::cerr << "Watch out! Stack Overflow\n";
        exit(EXIT_FAILURE);
    }
    m_data[m_size++] = x;
}

template<typename T>
void stack<T>::pop()
{
    if (empty())
    {
        std::cerr << "pop() called on an empty Stack\n";
        exit(EXIT_FAILURE);
    }
    m_size--;
}


template<typename T>
T stack<T>::top()
{
    if (empty())
    {
        std::cerr << "top() called on an empty Stack\n";
        exit(EXIT_FAILURE);
    }
    return m_data[m_size - 1];
}



template<typename T>
void stack<T>::swap(stack<T>& rhs)
{
    if (rhs != (*this)) {
        stack<T> temp = rhs;
        rhs = *this;
        this = &temp;
    }
}


// 
// Getters 
//

template<typename T>
bool stack<T>::operator==(const stack& rhs) {
    if (this->m_size == rhs.m_size) {
        for (int i = 0; i < m_size; i++) {
            if (this->m_data[i] != rhs.m_data[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

template<typename T>
bool stack<T>::operator!=(const stack& rhs) {
    return !(this == rhs);
}


template<typename T>
size_t stack<T>::size() const
{
    return m_size;
}


template<typename T>
bool stack<T>::empty() const
{
    return size() == 0;
}


template<typename T>
bool stack<T>::full() const
{
    return size() == m_capacity;
}


