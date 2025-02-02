#include <iostream>
#include <string>

using namespace std;

class Stack {
public:
    char data[100];
    int top = -1;

    void push(char c) {
        data[++top] = c;
    }

    char pop() {
        return data[top--];
    }

    char getTop() {
        return data[top];
    }

    bool isEmpty() {
        return top == -1;
    }
};

string infixToPostfix(const string& infix) {
    Stack stack;
    string postfix = "";
    for (char c : infix) {
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!stack.isEmpty() && stack.getTop() != '(') postfix += stack.pop();
            stack.push(c);
        } else if (c == '(') stack.push(c);
        else if (c == ')') {
            while (stack.getTop() != '(') postfix += stack.pop();
            stack.pop();
        } else postfix += c;
    }
    while (!stack.isEmpty()) postfix += stack.pop();
    return postfix;
}

string infixToPrefix(const string& infix) {
    string reversedInfix = "";
    for (int i = infix.size() - 1; i >= 0; --i) reversedInfix += infix[i];
    string prefix = infixToPostfix(reversedInfix);
    string reversedPrefix = "";
    for (int i = prefix.size() - 1; i >= 0; --i) reversedPrefix += prefix[i];
    return reversedPrefix;
}

int evaluatePostfix(const string& postfix) {
    Stack stack;
    for (char c : postfix) {
        if (isdigit(c)) stack.push(c - '0');
        else {
            int operand2 = stack.pop();
            int operand1 = stack.pop();
            int result;
            switch (c) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
            }
            stack.push(result);
        }
    }
    return stack.pop();
}

int main() {
    string infix = "A+B*C";
    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);
    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;
    cout << "Postfix Evaluation: " << evaluatePostfix(postfix) << endl;
    return 0;
}