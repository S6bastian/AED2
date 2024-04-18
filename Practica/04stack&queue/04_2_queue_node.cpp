#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;

    Node(int, Node*);
};

struct Queue {
    Node* head, * tail;

    Queue();
    void push(int);
    bool pop(int&);
    void print();
};

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

int main() {
    Queue queue;

    for (int i = 0; i < 10; i++)
        queue.push(i);

    queue.print();

    for (int i = 0, j = 0; i < 5; i++) {
        if (queue.pop(j))
            cout << "Popped: " << j << endl;
    }
      
    queue.print();

    for (int i = 0, j = 0; i < 10; i++) {
        if (queue.pop(j))
            cout << "Popped: " << j << endl;
    }

    queue.print();

    return 0;
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

Node::Node(int v, Node* n = nullptr) {
    value = v;
    next = n;
}

//*********************************************************************************************

Queue::Queue() {
    head = tail = nullptr;
}

void Queue::push(int value) {
    if (head == nullptr) {
        head = tail = new Node(value);
        return;
    }

    tail->next = new Node(value);
    tail = tail->next;
}

bool Queue::pop(int& value) {
    if (head == nullptr)
        return false;

    value = head->value;
    Node* tmp = head;
    head = head->next;
    delete tmp;
    if (head == nullptr)
        tail = nullptr;
    
    return true;
}

void Queue::print() {
    if (head == nullptr) {
        cout << "Empty queue" << endl;
        return;
    }

    cout << "Queue  -->";
    Node* current = head;
    while (current != nullptr) {
        cout << "  " << current->value << "  -->";
        current = current->next;
    }
    cout << "  nullptr" << endl;
}