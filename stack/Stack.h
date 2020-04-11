#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>

template <class C>

struct Node {
	C data;
	Node<C> *l_node, *r_node;
	Node(C data) {
		this->data = data;
		this->l_node = nullptr;
		this->r_node = nullptr;
	}
};

template <class C>

class Stack {
	public:
		Stack();
		bool isEmpty() const { return !itemCount; }
		int size() const { return itemCount; }
		void push(C);
		void pop();
		C& top();
	private:
		Node<C> *tail;
		unsigned int itemCount;
};

template <class C>
Stack<C>::Stack() {
	this->tail = nullptr;
	this->itemCount = 0;
}

template <class C>
void Stack<C>::push(C item) {
	if(tail == nullptr){
		tail = new Node<C>(item);
	}else{
		tail->r_node = new Node<C>(item);
		tail->r_node->l_node = tail;
		tail = tail->r_node;
	}
	++itemCount;
}

template <class C>
void Stack<C>::pop() {
	if(!itemCount){
		throw std::out_of_range("Error: Stack is empty");
	}else{
		if(itemCount == 1){
			delete tail;
			tail = nullptr;
			--itemCount;
		}else {
			tail = tail->l_node;
			delete tail->r_node;
			--itemCount;
		}
	}
}

template <class C>
C& Stack<C>::top() {
	return this->tail->data;
}

#endif
