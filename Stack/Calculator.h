#include "iostream"
#include "vector"
#include "string"
#include "map"
using namespace std;


class Calculator {
public:

	// 判断一个字符串是否能转为数字
	static bool IsDigit(string s) {
		for (char c : s) {
			if(c < 48 || c > 57) return false;
		}
		return true;
	}

	// 后缀表达式计算
	int CalPostfixExpression(vector<string> Expression) {
		vector<int> stack;
		for (string s : Expression) {
			if (IsDigit(s)) {
				stack.push_back(stoi(s));
			}
			else {
				int len = stack.size();
				int a = stack[len-2], b = stack[len-1];
				stack.erase(stack.end()-2, stack.end());
				if (s == "+") stack.push_back(a + b);
				if (s == "-") stack.push_back(a - b);
				if (s == "*") stack.push_back(a * b);
				if (s == "/") stack.push_back(a / b);
			}
		}
		return stack[0];
	}


	// 中缀表达式转后缀表达式
	vector<string> InfixExpressionToPostfix(vector<string> Expression) {
		vector<string> PostfixExpression;
		vector<string> stack;
		for (int i=0; i<Expression.size();i++) {
			string s = Expression[i];
			if (IsDigit(s)) {
				PostfixExpression.push_back(s);
			}
			else {
				map<string, int> power;
				power["*"] = power["/"] = 2;
				power["+"] = power["-"] = 1;
				if (s == "("){
					stack.push_back(s);
				}
				else {
					while (stack.size()) {
						string top = stack.back();
						if(s != ")" && power[top] < power[s]) break;

						if (s == ")" && top == "(") {
							stack.pop_back();
							break;
						}
						
						if (s == ")" || power[top] >= power[s]) {
							stack.pop_back();
							PostfixExpression.push_back(top);
						}
					}
					if(s != ")") stack.push_back(s);
				}
			}
		}
		while (stack.size()) {
			PostfixExpression.push_back(stack.back());
			stack.pop_back();
		}
		return PostfixExpression;
	}

	int CalInfixExpression(vector<string> Expression) {
		return CalPostfixExpression(InfixExpressionToPostfix(Expression));
	}
};


namespace CalculatorSpace {
	void Test() {
		Calculator calculator;
		vector<string> PostfixExpression = {"10", "5", "+", "100", "14", "-", "*"};
		cout << calculator.CalPostfixExpression(PostfixExpression) << endl;

		cout << endl;
		vector<string> InfixExpression = { "10", "+", "5", "*", "(", "100", "-", "32", ")"};  
		vector<string> InfixExpression2 = { "10", "+", "5", "*", "(", "0", "-", "32", ")"};  
		vector<string> InfixExpression3 = { "10", "+","100", "-", "32"};   
		vector<string> InfixExpression4 = { "(", "1", "+", "2", ")", "*", "8", "+", "9", "*", "5" ,"+", "7", "/", "3", "+", "4" };   
		vector<string> InfixExpression5 = { "(", "(", "1", "+", "2", ")", "*", "8", "+", "9", "*", "5" ,"+", "7", ")", "/", "3", "+", "4" };
		cout << calculator.CalInfixExpression(InfixExpression) << endl;
		cout << calculator.CalInfixExpression(InfixExpression2) << endl;
		cout << calculator.CalInfixExpression(InfixExpression3) << endl;
		cout << calculator.CalInfixExpression(InfixExpression4) << endl;
		cout << calculator.CalInfixExpression(InfixExpression5) << endl;
	}
}