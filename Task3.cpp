#include <iostream>
#include <string>
#include <cctype>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class Stack {
private:
    Node<T>* topNode;
public:
    Stack() : topNode(nullptr) {}
    ~Stack() { clear(); }
    // Adds a new value to the top of the stack
    void push(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = topNode;
        topNode = newNode;
    }
    // Removes the top value from the stack
    void pop() {
        if (isEmpty()) return;
        Node<T>* temp = topNode;
        topNode = topNode->next;
        delete temp; }

    // Returns the value at the top of the stack
    T top() {
        return isEmpty() ? T() : topNode->data; }

    // Checks if the stack is empty
    bool isEmpty() { return topNode == nullptr; }

    // Removes all elements from the stack
    void clear() {
        while (!isEmpty()) pop();}
};

// Returns the precedence of an operator
int prec(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0; }

// Checks whether a character is an operator
bool isOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%'; }
string infixToPostfix(string infix, bool& ok) {
    Stack<char> s;
    string postfix = "";
    ok = true;

    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];
        if (c == ' ') continue;
        // Reads complete numbers and adds them to postfix
        if (isdigit(c)) {
            while (i < infix.length() && isdigit(infix[i])) postfix += infix[i++];
            i--;
            postfix += ' ';
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            // Removes operators until the opening bracket is found
            while (!s.isEmpty() && s.top() != '(') {
                postfix += s.top(); postfix += ' ';
                s.pop();
            }
            if (s.isEmpty()) { ok = false; return ""; }
            s.pop();
        } else if (isOp(c)) {           //handles the operators by precedence
            while (!s.isEmpty() && prec(s.top()) >= prec(c)) {
                postfix += s.top(); postfix += ' ';
                s.pop();
            }
            s.push(c);
        } else {
            ok = false; return "";}
    }

    // Moves remaining operators from the stack to postfix
    while (!s.isEmpty()) {
        if (s.top() == '(') { ok = false; return ""; }
        postfix += s.top(); postfix += ' ';
        s.pop(); }
    return postfix;
}

int evaluatePostfix(string postfix, bool& ok) {
    Stack<int> s;
    ok = true;
    for (size_t i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        if (c == ' ') continue;
        if (isdigit(c)) {
            int num = 0;
            while (i < postfix.length() && isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;}
            i--;
            s.push(num);
        } else if (isOp(c)) {
            // Gets the two values needed for the operation
            if (s.isEmpty()) { ok = false; return 0; }
            int v2 = s.top(); s.pop();
            if (s.isEmpty()) { ok = false; return 0; }
            int v1 = s.top(); s.pop();

            // Checks for division or modulo by zero
            if (c == '/' && v2 == 0) { cout << "Error: Division by zero!\n"; ok = false; return 0; }
            if (c == '%' && v2 == 0) { cout << "Error: Modulo by zero!\n"; ok = false; return 0; }

            int res = 0;
            if (c == '+') res = v1 + v2;
            else if (c == '-') res = v1 - v2;
            else if (c == '*') res = v1 * v2;
            else if (c == '/') res = v1 / v2;
            else if (c == '%') res = v1 % v2;
            s.push(res); }
    }
    if (s.isEmpty()) { ok = false; return 0; }
    int finalRes = s.top(); s.pop();
    // Extra values mean the expression is invalid
    if (!s.isEmpty()) ok = false;
    return finalRes;
}

void runTest(string expr) {         //helper function to test the expressions
    bool ok = true;
    cout << "Infix:   " << expr << "\n";
    string post = infixToPostfix(expr, ok);
    if (!ok) { cout << "Result:  Failed (Invalid/Mismatched)\n\n"; return; }
    cout << "Postfix: " << post << "\n";
    int ans = evaluatePostfix(post, ok);
    if (ok) cout << "Result:  " << ans << "\n\n";
    else cout << "Result:  Failed\n\n";
}

int main() {
    cout << "========== Task 3: Infix to Postfix & Evaluation ============\n\n";
    // Tests different expressions and error cases
    runTest("2 + 3 * 4");
    runTest("(2 + 3) * 4");
    runTest("10 + 2 * 6");
    runTest("(10 + 2) * (6 - 3)");
    runTest("20 / 5 + 3");
    runTest("10 / 0");
    runTest("(2 + 3");
    return 0;
}