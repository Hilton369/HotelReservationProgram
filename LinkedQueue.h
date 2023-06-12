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

template<typename T>
LinkedQueue<T>::LinkedQueue():list(){};

template<typename T>
void LinkedQueue<T>::enqueue(T data) {
    list.addLast(data);
}

template<typename T>
T LinkedQueue<T>::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty.");
    }
    return list.removeFirst();
}

template<typename T>
T LinkedQueue<T>::front() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty.");
    }
    return list.getInfo(0);
}

template<typename T>
bool LinkedQueue<T>::isEmpty() const {
    return list.getSize() == 0;
}

template<typename T>
int LinkedQueue<T>::size() const {
    return list.getSize();
}

#endif





