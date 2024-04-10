#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

int precedence(char ch);
bool isOperator(char ch);
int valueGet(const Map& values, char ch);

int evaluate(string infix, const Map& values, string& postfix, int& result) {
    
    if (infix.size() == 0) return 1; // empty infix expression
    
      // convert infix to postfix
    postfix = "";
    stack<char> operatorStack;
    int paranthesisCount = 0;
    for (int i = 0; i < infix.size(); i++) {
        if (isalpha(infix[i])) {
            if (!islower(infix[i])) return 1;
            if (i == 0 || !isalpha(infix[i-1]) || infix[i-1] == '(') {
                postfix += infix[i];
            }
            else return 1;
        }
        else if (infix[i] == '(') {
            if (i != 0 && !(isOperator(infix[i-1]) || infix[i-1] == '(')) return 1;
            paranthesisCount++;
            operatorStack.push(infix[i]);
        }
        else if (infix[i] == ')') {
            if (isOperator(infix[i-1]) || infix[i-1] == '(') return 1;
            paranthesisCount--;
            while(operatorStack.top() != '(') {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();
        }
        else if (isOperator(infix[i])) {
            if (i == 0 || isOperator(infix[i-1])) return 1;
            while(!operatorStack.empty() && operatorStack.top() != '(' && (precedence(infix[i]) <= precedence(operatorStack.top()))) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(infix[i]);
        }
        else if (infix[i] == ' ') continue;
    }
    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    if (paranthesisCount != 0) return 1;
    
    
      // evalutating postfix expression
    stack<int> operandStack;
    for (char ch : postfix) {
        if (isalpha(ch)) {
            if (!values.contains(ch)) return 2;
            int operand = valueGet(values, ch);
            operandStack.push(operand);
        }
        else {
            
            if (operandStack.empty()) return 1;
            int operand2 = operandStack.top();
            operandStack.pop();
            
            if (operandStack.empty()) return 1;
            int operand1 = operandStack.top();
            operandStack.pop();
            
            if (ch == '+') operandStack.push(operand1+operand2);
            else if (ch == '-') operandStack.push(operand1-operand2);
            else if (ch == '*') operandStack.push(operand1*operand2);
            else if (ch == '/') {
                if (operand2 == 0) return 3;
                operandStack.push(operand1/operand2);
            }
        }
    }
    int answer = operandStack.top();
    operandStack.pop();
    if (!operandStack.empty()) return 1;
    result = answer;
    return 0;
}

int precedence(char ch) {
    if (ch == '+' || ch == '-'){
        return 1;
    }
    else if (ch == '*' || ch == '/') {
        return 2;
    }
    return 0;
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '/' || ch =='*');
}

int valueGet(const Map& values, char ch) {
    int num;
    values.get(ch, num);
    return num;
}


int main() {
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    answer = 999;
    assert(evaluate("((a))", m, pf, answer) == 0  &&
                        pf == "a"  &&  answer == 3);
    assert(evaluate("a+ e", m, pf, answer) == 0  &&
                        pf == "ae+"  &&  answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()o", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(*o)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
        // unary operators not allowed:
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2  &&
                        pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
                        pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
                        pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
                        pf == "a"  &&  answer == 3);
    cout << "Passed all tests" << endl;
}
