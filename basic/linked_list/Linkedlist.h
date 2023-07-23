#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <stdexcept>
#include <algorithm>

// Useful struct to store the list's elements
template <class C>
class Node {
	public:
	C data;
	Node *l_node, *r_node;
	Node(C data):data(data), l_node(nullptr), r_node(nullptr){}
};

template <class C>
class LinkedList {
	public:
		LinkedList();
		~LinkedList();
		void pushBack(C);
		void pushFront(C);
		void popBack();
		void popFront();
		C& front();
		C& back();
		C& get(unsigned int);
		unsigned int size() const { return this->itemCount; }
		bool isEmpty() const { return !this->itemCount; }
		class iterator: public std::iterator<std::input_iterator_tag, Node<C>, ptrdiff_t, const Node<C>*, Node<C>&>{
			Node<C> *nodeIter;
			public:
				explicit iterator(Node<C> *node):nodeIter(node){}
				iterator &operator++(){
					nodeIter = nodeIter->r_node;
					return *this;
				}
				iterator(const iterator &iter):nodeIter(iter.nodeIter){}
				bool operator==(iterator other) const { return nodeIter == other.nodeIter; }
				bool operator!=(iterator other) const { return nodeIter != other.nodeIter; }
				C& operator*() const { return nodeIter->data; }
		};
		iterator begin() {
			return iterator(head);
		}
		iterator end() {
			return iterator(tail->r_node);
		}
	private:
		Node<C> *head; // head: points to the beggining of the list
		Node<C> *tail; // tail: points to the end of the list
		unsigned int itemCount; // Number of items in our list
};

template <class C>
LinkedList<C>::LinkedList() {
	this->head = nullptr;
	this->tail = nullptr;
	this->itemCount = 0;
}

template <class C>
LinkedList<C>::~LinkedList() {
	if(!itemCount) return;
	if(itemCount == 1) {
		delete head;
	} else {
		while(tail->l_node != nullptr) {
			tail = tail->l_node;
			delete tail->r_node;
		}
		delete tail;
	}
}

template <class C>
void LinkedList<C>::pushBack(C item) {
	if(tail == nullptr) {
		head = new Node<C>(item);
		tail = head;
	} else {
		tail->r_node = new Node<C>(item);
		tail->r_node->l_node = tail;
		tail = tail->r_node;
	}
	++itemCount;
}

template <class C>
void LinkedList<C>::pushFront(C item) {
	if(tail == nullptr) {
		head = new Node<C>(item);
		tail = head;
	} else {
		head->l_node = new Node<C>(item);
		head->l_node->r_node = head;
		head = head->l_node;
	}
	++itemCount;
}

template <class C>
void LinkedList<C>::popBack() {
	if(!itemCount)
		throw std::out_of_range("Error: list is empty");
	if(itemCount == 1) {
		delete head;
		head = tail = nullptr;
	} else {
		tail = tail->l_node;
		delete tail->r_node;
	}
	--itemCount;
}

template <class C>
void LinkedList<C>::popFront() {
	if(!itemCount)
		throw std::out_of_range("Error: list is empty");
	if(itemCount == 1) {
		delete head;
		head = tail = nullptr;
	} else {
		head = head->r_node;
		delete head->l_node;
	}
	--itemCount;
}


template <class C>
C& LinkedList<C>::front() {
	return head->data;
}

template <class C>
C& LinkedList<C>::back() {
	return tail->data;
}

template <class C>
C& LinkedList<C>::get(unsigned int index) {
	if(index >= itemCount)
		throw std::out_of_range("Error: index out of range");
	Node<C> *tmp_node = head;
	while(index) {
		tmp_node = tmp_node->r_node;
		--index;
	}
	return tmp_node->data;
}

















#endif
