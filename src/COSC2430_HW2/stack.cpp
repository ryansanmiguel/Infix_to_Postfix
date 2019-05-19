#include <iostream>
#include "stack.h"

using namespace std;

// Default constructor
Stack::Stack() {
	top = NULL;
}

// Destructor
Stack::~Stack() {
	clear();
}

// Adds c to the top of the stack
void Stack::push(string str) {
	Node* newNode = new Node();
	newNode->data = str;
	newNode->link = top;
	top = newNode;
}

// Removes the top element from the stack and returns its value
std::string Stack::pop() {
	if (!isEmpty()) {
		string toReturn = top->data;
		removeTop();
		return toReturn;
	}
	else
		cout << "ERROR: Cannot pop from an empty stack" << endl;
}

// Returns the value of the top element w/o removing it from the stack
string Stack::peek() {
	if (!isEmpty())
		return top->data;
	else
		cout << "ERROR: Cannot peek at an empty stack" << endl;
}

// Removes all of the elements in the stack
void Stack::clear() {
	while (!isEmpty()) {
		removeTop();
	}
}

// Returns true if there are no elements in the stack
bool Stack::isEmpty() {
	return top == NULL;
}

// Prints all of the elements in the stack
void Stack::print() {
	Node* current = top;

	cout << "Stack: ";
	
	while (current != NULL) {
		for (char c : current->data)
			cout << c;
		cout << " ";
		current = current->link;
	}
	cout << endl << endl;
}

// Removes the top element from the stack
void Stack::removeTop() {
	Node* toRemove = top;
	top = top->link;
	delete toRemove;
}
