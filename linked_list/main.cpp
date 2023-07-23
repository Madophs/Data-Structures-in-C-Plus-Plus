#include <iostream>
#include "Linkedlist.h"

using namespace std;

static int total_memory = 0, freed_memory = 0;

void *operator new(size_t size){
	cout << "Allocating " << size << " bytes of memory" << endl;
	total_memory += size;
	return malloc(size);
}

void operator delete(void *memory, size_t size){
	cout << "Deallocating " << size << " bytes of memory" << endl;
	freed_memory += size;
	free(memory);
}

int main() {
	{
		LinkedList<int> l;
		for(int i = 1; i < 11; ++i) {
			if(i & 1) {
				l.pushBack(i);
			} else {
				l.pushFront(i);
			}
		}
		cout << "Iterating with auto" << endl;
		for(auto val: l){
			cout << val << " ";
		}
		cout << endl << endl;
		cout << "Traditional iteration" << endl;
		for(LinkedList<int>::iterator iter = l.begin(); iter != l.end(); ++iter){
			cout << *iter << " ";
		}
		cout << endl << endl;
	}
	cout << "Total memory: " << total_memory << " bytes, Memory in usage: " << total_memory-freed_memory << " bytes" << endl;
	return 0;
}

