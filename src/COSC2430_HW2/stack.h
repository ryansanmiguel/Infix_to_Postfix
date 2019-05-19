#pragma once

struct Node {
	std::string data;
	Node* link;
};

class Stack {
private:
	Node* top;

	void removeTop();
public:
	Stack();
	~Stack();
	void push(std::string str);
	std::string pop();
	std::string peek();
	void clear();
	bool isEmpty();
	void print();
};
