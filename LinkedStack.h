#ifndef LINKED_STACK
#define LINKED_STACK
#include "DLL.h"

template<typename T>
class LinkedStack {
    public:
        LinkedStack();
        int size() const;
        bool empty() const;
        const T top();
        void push(const T& e);
        void pop();
    private:
        DLL<T> S; // linked list of elements
        int n; // number of elements
};

template<typename T>
LinkedStack<T>::LinkedStack():S(), n(0){} //constractor

template<typename T>
int LinkedStack<T>::size()const{
    return n;  // number of items in the stack
}
template<typename T>
bool LinkedStack<T>::empty()const{
    return n == 0; // is the stack empty?
}

template<typename T>
const T LinkedStack<T>::top(){ // return top of stack
    if (empty())
        std::cerr << "Top of empty stack\n";
    return S.getInfo(n - 1); // return the data of the first node in SLL without removing node
}

template<typename T>
void LinkedStack<T>::push(const T& e){ // push element onto stack
    ++n;
    S.addLast(e);
}

template<typename T>
void LinkedStack<T>::pop(){ // pop the stack
    if (empty())
        std::cerr << "Top of empty stack\n";
    --n;
    S.removeLast();
}

#endif