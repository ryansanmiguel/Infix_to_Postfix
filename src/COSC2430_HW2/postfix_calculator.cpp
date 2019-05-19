#include <iostream>
#include <sstream>
#include <string>
#include "postfix_calculator.h"

using namespace std;

// Default constructor
PostfixCalculator::PostfixCalculator() : stack(), infix(""), postfix(""), value(0), invalidExp(false) {}

// Set the infix expression to be converted to postfix
void PostfixCalculator::setInfix(string infix) {
	this->infix = infix;
}

// Returns true if infix expression is valid
bool PostfixCalculator::isValid() {
	return !invalidExp;
}

// Get the resulting postfix expression
string PostfixCalculator::getPostfix() {
	if (invalidExp)
		cout << "No postfix to return" << endl;
	else
		return postfix;
}

// Get the value of the evaluated postfix expression
float PostfixCalculator::getValue() {
	if (invalidExp)
		cout << "No value to return" << endl;
	else
		return value;
}

// Converts the given infix expression (set by setInfix()) to postfix
int PostfixCalculator::convertToPostfix() {
	if (!infix.empty())
		return convert(infix);
	else
		cout << "First, set the infix expression to be converted" << endl;
}

// Converts the given infix expression (passed as param infix) to postfix
int PostfixCalculator::convert(string infix) {
	stack.clear();
	postfix.clear();

	size_t posCE = infix.find("CE");
	size_t posC = infix.find('C');

	if (posCE != string::npos) {
		infix = infix.substr(posCE + 2);
		return convert(infix);
	}
	else if (posC != string::npos) {
		
		size_t pos = posC;
		size_t len = 1;
		
		while (pos != 0 && infix.at(pos - 1) == ' ') {
			pos--;
			len++;
		}
		
		while (pos != 0 && infix.at(pos - 1) != ' ') {
			pos--;
			len++;
		}

		infix.erase(pos, len);
		return convert(infix);
	}

	if (!isBalanced(infix)) {
		//cout << "ERROR: Invalid use of parentheses" << endl;
		invalidExp = true;
		return -1;
	}
	
	istringstream iss(infix);
	string symbol = "";
	char sym = '-';				// first char of symbol
	string previous = " ";		// init value cannot be empty string
	
	while (!iss.eof()) {
		iss >> symbol;
		sym = symbol[0];
		
		// If operand
		if (isOperand(symbol)) {
			if (isOperand(previous)) {
				postfix.clear();
				//cout << "ERROR: Invalid Expression. Missing operator" << endl;
				invalidExp = true;
				return -1;
			}
			
			postfix += symbol;
			postfix += ' ';
		}

		// If operator
		if (isOperator(sym)) {
			if (isOperator(previous[0])) {
				postfix.clear();
				invalidExp = true;
				return -1;
			}
			
			while (!stack.isEmpty())
				if (precedence(sym, stack.peek()[0]) &&
					!isOpenParenthesis(stack.peek()[0])) {
					postfix += stack.pop();
					postfix += ' ';
				}
				else break;

			stack.push(symbol);
		}

		// If parenthesis
		if (isOpenParenthesis(sym))
			stack.push(symbol);
		
		if (isCloseParenthesis(sym)) {
			bool foundPair = false;

			while (foundPair == false)
				if (isOpenParenthesis(stack.peek()[0])) {
					stack.pop();
					foundPair = true;
				}
				else {
					postfix += stack.pop();
					postfix += ' ';
				}
		}
		previous = symbol;
	}
	while (!stack.isEmpty()) {
		postfix += stack.pop();
		postfix += ' ';
	}

	return 0;
}

// Evaluates the resulting postfix expression
void PostfixCalculator::evaluatePostfix() {
	stack.clear();

	istringstream iss(postfix);
	string symbol = "";
	char sym = '-';
	
	while (iss >> symbol) {
		sym = symbol[0];
		
		if (isOperand(symbol))
			stack.push(symbol);
		else {
			float rhs = strtof(stack.pop().c_str(), NULL);	// pop rhs first
			float lhs = strtof(stack.pop().c_str(), NULL);
			float result = 0;

			switch (sym) {
			case '+':
				result = lhs + rhs;
				break;
			case '-':
				result = lhs - rhs;
				break;
			case '*':
				result = lhs * rhs;
				break;
			case '/':
				result = lhs / rhs;
				break;
			}
			stack.push(to_string(result));
		}
	}
	value = strtof(stack.pop().c_str(), NULL);
}

// Returns true if op1 has a precedence less than that of op2
bool PostfixCalculator::precedence(char op1, char op2) {
	int prec1 = prec(op1);
	int prec2 = prec(op2);

	return prec1 <= prec2;
}

// Returns the precedence of op using modified operator precedence
int PostfixCalculator::prec(char op) {
	if (op == '*' || op == '/')
		return 2;
	if (op == '+' || op == '-')
		return 1;
	if (isOpenParenthesis(op) || isCloseParenthesis(op))
		return 0;
}

// Returns true if the infix expression is balanced (all parentheses are paired)
bool PostfixCalculator::isBalanced(string exp) {
	stack.clear();
	
	for (char sym : exp) {
		if (sym == ' ')
			continue;
		if (isOpenParenthesis(sym))
			stack.push(string(1, sym));
		if (isCloseParenthesis(sym)) {
			if (stack.isEmpty() || !arePair(stack.peek()[0], sym))
				return false;
			else
				stack.pop();
		}
	}
	return stack.isEmpty() ? true : false;
}

// Returns true if the parenthesis are a pair (one open, one close)
bool PostfixCalculator::arePair(char open, char close) {
	return (open == '(' && close == ')')
		|| (open == '{' && close == '}')
		|| (open == '[' && close == ']');
}

// Returns true if sym is an open parenthesis
bool PostfixCalculator::isOpenParenthesis(char sym) {
	return (sym == '(' )
		|| (sym == '{' )
		|| (sym == '[');
}

// Returns true if sym is a close parenthesis
bool PostfixCalculator::isCloseParenthesis(char sym) {
	return (sym == ')')
		|| (sym == '}')
		|| (sym == ']');
}

// Returns true if sym is an operator
bool PostfixCalculator::isOperator(char sym) {
	return (sym == '+')
		|| (sym == '-')
		|| (sym == '*')
		|| (sym == '/');
}

// Returns true if symbol is an operand
bool PostfixCalculator::isOperand(string symbol) {
	return symbol.find_first_not_of(".0123456789") == string::npos;
}
