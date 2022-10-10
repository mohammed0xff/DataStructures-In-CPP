#include "minHeap.hpp"

int main()
{
    MinHeap heap;

    heap.insert(40);
    heap.insert(3);
    heap.insert(15);
    heap.insert(72);
    heap.insert(2);
    heap.insert(32);


    cout << heap.extractMin() << "\n";
    heap.deleteMin();

    cout << heap.extractMin() << "\n";
    heap.deleteMin();

    heap.print();

    return 0;
}
