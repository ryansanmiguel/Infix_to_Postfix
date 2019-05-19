#pragma once
#include <string>
#include "stack.h"

class PostfixCalculator {
private:
	Stack stack;
	std::string infix;
	std::string postfix;
	float value;
	bool invalidExp;

	int convert(std::string infix);
	bool precedence(char op1, char op2);
	int prec(char op);
	bool isBalanced(std::string exp);
	bool arePair(char open, char close);
	bool isOpenParenthesis(char sym);
	bool isCloseParenthesis(char sym);
	bool isOperator(char sym);
	bool isOperand(std::string symbol);
public:
	PostfixCalculator();
	void setInfix(std::string infix);
	bool isValid();
	std::string getPostfix();
	float getValue();
	int convertToPostfix();
	void evaluatePostfix();
};
