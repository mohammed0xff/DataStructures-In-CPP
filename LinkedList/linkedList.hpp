#pragma once
#include <iostream>


template <typename T>
class ListNode {
public:
    ListNode() {};
    ListNode(T val)
        : data(val)
        , next(nullptr)
    {
    }
    ~ListNode() {}

    T data;
    ListNode* next;
};




template <typename T>
class LinkedList {
public:

    LinkedList();
    ~LinkedList();

    void push_front(T val);
    void push_back(T val);

    void pop_back();
    void pop_front();

    void deleteNodeAt(int i);
    void deleteNodesByValue(T val);

    void reverse();
    void sort();
    void clear();

    T& front();
    T& back();

    int  length();
    bool isEmpty();

    void mergeWith(LinkedList& rhs);
    void swap(LinkedList<T>& rhs);

    void printList();


private:
    ListNode<T>* mergeSort(ListNode<T> *head);
    ListNode<T>* getMid   (ListNode<T> *head);
    ListNode<T>* merge    (ListNode<T> *list1, ListNode<T> *list2);


private:
    ListNode<T>* m_head;
    ListNode<T>* m_tail;
    int m_length;
};



template <typename T>
LinkedList<T>::LinkedList()
    : m_head(nullptr)
    , m_tail(nullptr)
    , m_length(0)
{}




template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}


template <typename T>
void LinkedList<T>::push_front(T data) {

    ListNode<T>* newNode = new ListNode<T>(data);
    newNode->next = this->m_head;
    if (isEmpty()) {
        this->m_tail = newNode;
    }
    this->m_head = newNode;
    this->m_length++;
}


template <typename T>
void LinkedList<T>::push_back(T data) {

    ListNode<T>* newNode = new ListNode<T>(data);
    if (isEmpty()) {
        this->m_head = newNode;
        m_tail = newNode;
    }
    else {
        this->m_tail->next = newNode;
        this->m_tail = this->m_tail->next;
    }
    this->m_length++;
}



template <typename T>
void LinkedList<T>::pop_front() {
    if (isEmpty()) {
        return;
    }
    ListNode<T>* temp = m_head;
    m_head = m_head->next;
    delete temp;
    if (isEmpty()) {
        m_tail = nullptr;
    }
    m_length--;

}


template <typename T>
void LinkedList<T>::pop_back() {
    if (isEmpty()) {
        return;
    }
    ListNode<T>* first = nullptr;
    ListNode<T>* second = this->m_head;
    while (second->next != nullptr) {

        first = second;
        second = second->next;
    }
    // got the node so delete it
    delete second;
    // set the tail to the one preceding it 
    m_tail = first;

    if (first == nullptr) {
        m_head = nullptr;
    }
    else {
        m_tail->next = nullptr;
    }

    m_length--;
}


template <typename T>
T& LinkedList<T>::front() {
    if (isEmpty()) {
        std::cerr << "front() called on an empty list!" << std::endl;
        abort();
    }
    return m_head->data;
}



template <typename T>
T& LinkedList<T>::back() {
    if (isEmpty()) {
        std::cerr << "back() called on an empty list!" << std::endl;
        abort();
    }           
    return m_tail->data;

}



template <typename T>
void LinkedList<T>::clear() {

    ListNode<T>* first = this->m_head;
    ListNode<T>* second = nullptr;
    while (first != nullptr) {
        second = first->next;
        delete first;
        first = second;
    }

    m_head = m_tail = nullptr;
    m_length = 0;

    std::cout << "List cleared." << std::endl;
}



template <typename T>
void LinkedList<T>::deleteNodeAt(int idx) {

    if ((idx < 0) || (idx >= this->m_length)) {
        throw std::out_of_range("Index got out of range!");
    }
    else {
        ListNode<T>* node = this->m_head;
        // Update head
        if (idx == 0) {  
            this->m_head = node->next;
            delete node;
            if (isEmpty()) {
                this->m_tail = nullptr;
            }
        } else {
            for (int i = 0; i < idx - 1; i++) {
                node = node->next;
            }
            ListNode<T>* tmp = node->next;
            node->next = node->next->next;
            delete tmp;
            // Update tail 
            if (idx == this->m_length - 1) {  
                this->m_tail = node;
            }
        }
        this->m_length--;
    }
}



template <typename T>
void LinkedList<T>::deleteNodesByValue(T value) {
    if (isEmpty()) {
        return;
    }
    ListNode<T>* curr = this->m_head;
    ListNode<T>* temp;
    while (curr->next) {
        if (curr->next->data == value) {
            temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        }
        else {
            curr = curr->next;
        }
    }
    // update the head if it had to be deleted.
    if (m_head->data == value) {
        temp = m_head;
        this->m_head = m_head->next;
        delete temp;
    }
    // update the tail anyway ..
    m_tail = curr;

}



template <typename T>
bool LinkedList<T>::isEmpty() {
    return (m_head == nullptr);
}


template <typename T>
int LinkedList<T>::length() {
    return m_length;
}



template <typename T>
void LinkedList<T>::mergeWith(LinkedList& rhs) {
    this->m_tail->next = rhs.m_head;
    this->m_tail = rhs.m_tail;
    this->m_length += rhs.length();
    
    rhs.m_head = rhs.m_tail = nullptr;
    rhs.m_length = 0;

}


template <typename T>
void LinkedList<T>::reverse() {
    m_tail = m_head;
    ListNode<T>* temp = nullptr;
    ListNode<T>* prev = nullptr;
    ListNode<T>* current = m_head;
    while (current != nullptr) {
        temp = current->next;
        current->next = prev;
        prev = current;
        current = temp;
    }
    m_head = prev;
}


template <typename T>
void LinkedList<T>::sort() {
    if (!isEmpty()) {
        m_head = mergeSort(m_head);
        // update tail
        ListNode<T>* current = m_head;
        while (current->next != nullptr) {
            current = current->next;
        }
        m_tail = current;
    }
}



template <typename T>
void LinkedList<T>::swap(LinkedList<T>& rhs) {

    ListNode <T>* temp;

    // swap head
    temp = this->m_head;;
    this->m_head = rhs.m_head;
    rhs.m_head = temp;

    // swap tail
    temp = this->m_tail;;
    this->m_tail = rhs.m_tail;
    rhs.m_tail = temp;

    // swap length
    int tempLength = this->m_length;
    this->m_length = rhs.m_length;
    rhs.m_length = tempLength;
}



template <typename T>
ListNode<T>* LinkedList<T>::mergeSort(ListNode<T>* head) {
    if (!head || !head->next)
        return head;
    ListNode<T>* mid   = getMid(head);
    ListNode<T>* left  = mergeSort(head);
    ListNode<T>* right = mergeSort(mid);
    return merge(left, right);
}



template <typename T>
ListNode<T>* LinkedList<T>::merge(ListNode<T>* lhs, ListNode<T>* rhs) {
    ListNode<T> dummyHead(0);
    ListNode<T>* ptr = &dummyHead;
    while (lhs && rhs) {
        if (lhs->data < rhs->data) {
            ptr->next = lhs;
            lhs = lhs->next;
        }
        else {
            ptr->next = rhs;
            rhs = rhs->next;
        }
        ptr = ptr->next;
    }
    if (lhs) {
        ptr->next = lhs;
    }
    else {
        ptr->next = rhs;
    }

    return dummyHead.next;
}



template <typename T>
ListNode<T>* LinkedList<T>::getMid(ListNode<T>* head) {
    ListNode<T>* midPrev = nullptr;
    while (head && head->next) {
        midPrev = (midPrev == nullptr) ? head : midPrev->next;
        head = head->next->next;
    }
    ListNode<T>* mid = midPrev->next;
    midPrev->next = nullptr;
    return mid;
}



template <typename T>
void LinkedList<T>::printList() {
    if (isEmpty()) {
        std::cout << "List is empty." << std::endl;
    }
    else {
        ListNode<T>* node = this->m_head;
        std::cout << "Printing sequence:" << std::endl;
        while (node != nullptr) {
            std::cout << node->data << ' ';
            node = node->next;
        }
        std::cout << std::endl;
    }
}
