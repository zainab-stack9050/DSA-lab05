#include <iostream>
#include <string>
using namespace std;

//Node structure for Stack
class StackNode {
public:
    char data;
    StackNode* next;
    
    StackNode(char val) {
        data = val;
        next = nullptr;}
};

//Implementation of Linked Stack
class LinkedStack {
private:
    StackNode* topNode;

public:
    LinkedStack() { topNode = nullptr; }

    ~LinkedStack() { clearStack(); }

    void push(char val) {
        StackNode* newNode = new StackNode(val);
        newNode->next = topNode;
        topNode = newNode; }

    void pop() {
        if (isEmpty()) return;
        StackNode* temp = topNode;
        topNode = topNode->next;
        delete temp; }

    char top() {
        if (isEmpty()) return '\0';
        return topNode->data; }

    bool isEmpty() {
        return topNode == nullptr; }

    void displayStack() {
        StackNode* curr = topNode;
        cout << "Stack (Top to Bottom): ";
        while (curr != nullptr) {
            cout << curr->data << " ";
            curr = curr->next; }
        cout << endl;
    }

    void clearStack() {
        while (!isEmpty()) {
            pop(); }
    }

    bool checkBalance(string expr) {
        clearStack();
        for (size_t i = 0; i < expr.length(); i++) {
            char ch = expr[i];
            // Push opening brackets
            if (ch == '(' || ch == '{' || ch == '[') {
                push(ch);
            } 
            // Process closing brackets
            else if (ch == ')' || ch == '}' || ch == ']') {
                if (isEmpty()) return false; // Extra closing bracket
                char topChar = top();
                if ((ch == ')' && topChar == '(') ||
                    (ch == '}' && topChar == '{') ||
                    (ch == ']' && topChar == '[')) {
                    pop();
                } else {
                    return false; // Mismatched brackets 
                    }
            }
        }
        return isEmpty(); // True if stack is empty (all matched)
    }
};

int main() {
    LinkedStack stack;
    string testCases[] = {
        "(A+B)",
        "{A+[B*C]}",
        "(A+B]",
        "((A+B)",
        "{[()]}",
        "A+B*C",
        "([A+B])" };

    cout << "=== Task 1: Expression Parentheses Checker ===\n";
    for (const string& expr : testCases) {
        bool balanced = stack.checkBalance(expr);
        cout << "Expression: " << expr << "\n"
             << (balanced ? "Balanced" : "Not Balanced") << "\n\n"; }
    return 0;
}