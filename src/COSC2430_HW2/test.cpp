#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

int main() {
	Stack stack = Stack();
	string str = "apples";

	for (char c : str) {
		stack.push(c);
		cout << "Pushing " << c << endl;
		stack.print();
	}

	for (char c : str) {
		char d = stack.pop();
		cout << "Popping " << d << endl;
		stack.print();
	}
	stack.pop();

	system("pause");
	return 0;
}