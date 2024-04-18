#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;

    Node(int, Node*);
};

struct Stack {
    Node* top;

    Stack();
    void push(int);
    bool pop(int&);
    void print();
};

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

int main() {
    Stack stack;
    
    for (int i = 0; i < 10; i++)
        stack.push(i);

    stack.print();

    for (int i = 0, j = 0; i < 5; i++) {
        if (stack.pop(j))
            cout << "Popped: " << j << endl;
    }

    stack.print();

    for (int i = 0, j = 0; i < 10; i++) {
        if (stack.pop(j))
            cout << "Popped: " << j << endl;
    }

    stack.print();

    return 0;
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

Node::Node(int v, Node* n = nullptr) {
    value = v;
    next = n;
}

//*********************************************************************************************

Stack::Stack() {
    top = nullptr;
}

void Stack::push(int value) {
    top = new Node(value, top);
}

bool Stack::pop(int& value) {
    if (top == nullptr)
        return false;
    
    value = top->value;
    Node* tmp = top;
    top = top->next;
    delete tmp;
    return true;
}

void Stack::print() {
    if (top == nullptr) {
        cout << "Empty stack" << endl << endl;
        return;
    }

    Node* current = top;
    cout << "Top  -->";
    while (current != nullptr) {
        cout << "  " << current->value << "  -->";
        current = current->next;
    }
    cout << "  nullptr" << endl;
}