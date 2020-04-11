#include <iostream>
#include "Stack.h"


using namespace std;


int main() {
	Stack<int> s;
	for(int i = 0; i <= 10; ++i) {
		s.push(i);
	}
	while(!s.isEmpty()) {
		cout << "Value at the top: " << s.top() << endl;
		s.pop();
	}
	return 0;
}

