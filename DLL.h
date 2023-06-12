#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include <stdexcept>
// class prototype
template <typename T>
class DLL;

template <typename T>
class Iterator;

// Class Node
template <typename T>
class Node {
public:
	Node() {
		next = nullptr;
		pre = nullptr;
	}
	Node(T data, Node<T>* n = nullptr, Node<T>* p = nullptr) {
		info = data;
		next = n;
		pre = p;
	}
	/* Class DLL and Iterator can access all private data members and functions of Node*/
	friend class DLL<T>;
	friend class Iterator<T>;
private:
	T info;
	Node <T>* next;
	Node <T>* pre;
};

// class Iterator
template<typename T>
class Iterator {
public:
	Iterator(Node<T>* p) {
		current = p;
	}
	Iterator next() {
		current = current->next;
		return *this;
	}
	Iterator previous() {
		current = current->pre;
		return *this;
	}
	T content() {
		return current->info;
	}
	bool isEqual(const Iterator<T>& itr) const {
		return current == itr.current;
	}

	bool operator==(const Iterator<T>& itr) const {
		return isEqual(itr);
	}

	bool operator!=(const Iterator<T>& itr) const {
		return !isEqual(itr);
	}

	Iterator operator++() {
		return next();
	}
	Iterator operator--() {
		return previous();
	}
	T& operator*() {
		return current->info;
	}
	/* Class DLL can access all private and protected items of Iterator */
	friend class DLL<T>;
private:
	Node<T>* current;
};

// classs DLL
template<typename T>
class DLL {
public:
	DLL() {
		head = tail = nullptr;
		size = 0;
	}
	~DLL() {
		for (Node<T>* tmp; head != nullptr; ) {
			tmp = head;
			head = head->next;
			delete tmp;
			tmp = nullptr;
		}
	}
	void addFirst(T data);
	void addLast(T data);
	void add(Iterator<T> p, T data);
	T removeFirst();
	T removeLast();
	bool remove(T target);
	//void remove(Iterator p);
	//bool contains(T target) const; 
	Node<T> getObject(int i) const;
	T getInfo(int i) const;
	Iterator<T> begin()const;
	Iterator<T> end()const;
	long getSize() const;

	friend class Iterator<T>;
private:
	Node<T>* head;
	Node<T>* tail;
	long size;
};

template<typename T>
long DLL<T>::getSize() const{
	return size;
}

template<typename T>
void DLL<T>::addFirst(T data) {
	Node<T>* tmp;
	if (head == nullptr) { //special case - empty list
		tmp = new Node<T>(data, nullptr, nullptr);
		head = tail = tmp;
	}
	else {
		tmp = new Node<T>(data, head, nullptr);
		head->pre = tmp;
		head = tmp;
	}
	size++;
}

template<typename T>
void DLL<T>::addLast(T data) {
	Node<T>* tmp; 
	if (head == nullptr) { //special case - empty list
		tmp = new Node<T>(data, nullptr, nullptr);
		head = tail = tmp;
	}
	else {
		tmp = new Node<T>(data, nullptr, tail);
		tail->next = tmp;
		tail = tmp;
	}
	size++;
}

//inserts a node after the given node
template<typename T>
void DLL<T>::add(Iterator<T> p, T data) {
	Node<T>* after = (p.current)->next;
	Node<T>* node = new Node<T>(data, after, p.current);
	(p.current)->next = node;
	after->pre = node; 
}

template<typename T>
T DLL<T>::removeFirst(){
	if (head == nullptr)  //special case - empty list
		throw std::runtime_error("ERROR: Empty List!");
	Node<T>* tmp = head;
	head = head->next;
	if (head == nullptr)  //special case - list of one node
		tail = nullptr;
	else                  //list with more than one node
		head->pre = nullptr;  
	T data = tmp->info;
	delete tmp;
	tmp = nullptr;     //optional, since the scope of tmp is bounded to this function 
	size--;
	return data;
}

template<typename T>
T DLL<T>::removeLast(){
	if (head == nullptr)   //special case - empty list
		throw std::runtime_error("ERROR: Empty List!");
	Node<T>* tmp = head;
	Node<T>* last = tail;
	if (head->next == nullptr) { //special case - list of one node
		head = nullptr;
		tail = nullptr;
	}
	else {   //list with more than one node
		for (int i = 0; i < size - 2; i++)     //finding the node before last node
			tmp = tmp->next;
		tail = tmp; 
		tail->next = nullptr;
	}
	T data = last->info;
	delete last;
	last = nullptr; //optional, since the scope of last is bounded to this function 
	size--;
	return data;
}

//removes the first occurance of target and returns true.
//if target doesn't exist, it returns false
template<typename T>
bool DLL<T>::remove(T target){
	if (head == nullptr) // list is empty
		throw std::runtime_error("ERROR: Empty List!");
	Node<T>* prev = nullptr;
	Node<T>* tmp = head;
	while (tmp != nullptr) {
		if (tmp->info == target) {
			if (tmp == head)  // target is the head
				head = tmp->next;
			else
				prev->next = tmp->next;
			if (tmp == tail)  // target is the tail
				tail = prev;
			else
				tmp->next->pre = prev;  //target found in a list with more than one node
			delete tmp;
			tmp = nullptr;
			--size;
			return true;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return false;
}


//returns the node in i-th position of the list
template<typename T>
Node<T> DLL<T>::getObject(int index) const{
	if (index < 0 || index > size - 1)
		throw std::runtime_error("index out of range");
	Node<T>* current = head;
	for (int i = 0; i < index; i++)
		current = current->next;
	return *current;
}

//returns the information in i-th position of the list
template<typename T>
T DLL<T>::getInfo(int index) const{
	if (index < 0 || index > size - 1)
		throw std::runtime_error("index out of range");
	Node<T>* current = head;
	for (int i = 0; i < index; i++)
		current = current->next;
	return current->info;
}

template<typename T>
Iterator<T> DLL<T>::begin() const {
	return Iterator<T>(head);
}

template<typename T>
Iterator<T> DLL<T>::end()const {
	return Iterator<T>(tail->next);
}

#endif
