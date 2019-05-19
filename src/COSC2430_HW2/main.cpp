#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "ArgumentManager.h"
#include "postfix_calculator.h"

using namespace std;

int main(int argc, char* argv[]) {
	PostfixCalculator calc = PostfixCalculator();

	ArgumentManager am(argc, argv);
	string inFileName = am.get("A");
	string outFileName = am.get("C");

	ifstream fin(inFileName);
	ofstream fout(outFileName);

	string infix = "";
	
	if (fin.is_open()) {
		getline(fin, infix);
		fin.close();
	}
	
	calc.setInfix(infix);
	
	
	int flag = calc.convertToPostfix();

	if (flag == -1) {
		fout.close();
		return 0;
	}
	
	calc.evaluatePostfix();
	
	if (fout.is_open()) {
		fout << calc.getPostfix() << endl;
		fout << fixed << setprecision(2) << calc.getValue();
		fout.close();
	}
	
	return 0;
}