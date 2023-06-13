#ifndef LINKED_QUEUE
#define LINKED_QUEUE

#include <stdexcept>
#include "DLL.h"

template<typename T>
class LinkedQueue {
public:
    LinkedQueue();
    void enqueue(T data);
    T dequeue();
    T front() const;
    bool isEmpty() const;
    int size() const;
    T remove(T target);

private:
    DLL<T> list;
};

/**
 * Constructor
*/
template<typename T>
LinkedQueue<T>::LinkedQueue():list(){};

/**
 * Function to add element to back of queue
*/
template<typename T>
void LinkedQueue<T>::enqueue(T data) {
    list.addLast(data);
}

/**
 * Function to remove element at the start of queue
*/
template<typename T>
T LinkedQueue<T>::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty.");
    }
    return list.removeFirst();
}

/**
 * Function that returns element at the front of queue
*/
template<typename T>
T LinkedQueue<T>::front() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty.");
    }
    return list.getInfo(0);
}

/**
 * Function to check if queue is empty
*/
template<typename T>
bool LinkedQueue<T>::isEmpty() const {
    return list.getSize() == 0;
}

/**
 * Function that returns the number of elements in queue
*/
template<typename T>
int LinkedQueue<T>::size() const {
    return list.getSize();
}

#endif





