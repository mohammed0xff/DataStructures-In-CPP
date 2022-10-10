#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

struct MinHeap
{
public:
    void insert(int val);
    void deleteMin();
    int extractMin();
    void print();
    size_t size();
    bool empty();

private:
    int parent(int i);
    int leftChild(int i);
    int rightChild(int i);
    void heapifyDown(int i);
    void heapify_up(int i);

private:
    vector<int> m_arr;
};


int MinHeap::parent(int i) {
    return (i - 1) / 2;
}

int MinHeap::leftChild(int i) {
    return (2 * i + 1);
}

int MinHeap::rightChild(int i) {
    return (2 * i + 2);
}

// Maintain Heap Structure top down
void MinHeap::heapifyDown(int i)
{
    // get left and right child of node at index `i`
    int left = leftChild(i);
    int right = rightChild(i);

    int smallest = i;

    // compare `A[i]` with its left and right child
    // and find the smallest value
    if (left < size() && m_arr[left] < m_arr[i]) {
        smallest = left;
    }

    if (right < size() && m_arr[right] < m_arr[smallest]) {
        smallest = right;
    }

    // swap with a child having lesser value and
    // call heapify-down on the child
    if (smallest != i)
    {
        swap(m_arr[i], m_arr[smallest]);
        heapifyDown(smallest);
    }
}

// Maintain Heap Structure bottom up
void MinHeap::heapify_up(int i)
{
    // check if the node at index `i` and its parent violate the heap property
    if (m_arr[parent(i)] > m_arr[i])
    {
        // swap the two if heap property is violated
        swap(m_arr[i], m_arr[parent(i)]);

        // call heapify-up on the parent
        heapify_up(parent(i));
    }
}


size_t MinHeap::size() {
    return m_arr.size();
}

bool MinHeap::empty() {
    return m_arr.size() == 0;
}

void MinHeap::insert(int val)
{
    m_arr.push_back(val);
    int index = size() - 1;
    heapify_up(index);
}

void MinHeap::deleteMin()
{
    try {
        // throw an exception if the heap has no elements
        if (size() == 0)
        {
            throw out_of_range("Index is out of range.");
        }
        m_arr[0] = m_arr.back();
        m_arr.pop_back();

        heapifyDown(0);
    }
    catch (const out_of_range& oor) {
        cout << endl << oor.what();
    }
}

int MinHeap::extractMin()
{
    try {
        // throw an exception if the heap has no elements
        if (size() == 0)
        {
            throw out_of_range("Index is out of range.");
        }
        return m_arr.at(0);
    }
    catch (const out_of_range& err) {
        cout << err.what() << endl;
    }
}

void MinHeap::print()
{
    vector <int>::iterator pos = m_arr.begin();
    while (pos != m_arr.end())
    {
        cout << *pos << " ";
        pos++;
    }
    cout << endl;
}
