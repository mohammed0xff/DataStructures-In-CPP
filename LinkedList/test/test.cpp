#include "linkedList.hpp"

int main() {
    LinkedList <int> list1;
    LinkedList <int> list2;

    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(4);
    list1.push_back(5);


    list2.push_back(6);
    list2.push_back(7);
    list2.push_back(8);
    list2.push_back(9);
    list2.push_back(10);

    //std::cout << 
    //list1.front();
    //list1.back();
    //list1.length();
    //list1.isEmpty();

    //list1.pop_front();
    //list1.pop_back();
    //list1.deleteNodeAt(0);
    //list1.deleteNodesByValue(5);
    //list1.clear();

    //list1.sort();
    //list1.swap(list2);
    //list1.mergeWith(list2);


    list1.printList();
    list2.printList();

    return 0;
}
