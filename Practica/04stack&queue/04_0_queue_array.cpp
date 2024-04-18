#include <iostream>
using namespace std;

class Queue {
    int size;
    int A[10];
    int* head, * tail;

public:
    Queue();
    bool push(int value);
    bool pop(int& value);
    void print();
};

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

int main() {
    Queue queue;
    
    int i = 0;

    for (int j = 0; j < 6; j++, i++) {
        if (!queue.push(i)) {
            cout << "Full queue" << endl;
            break;
        }
    }

    queue.print();

    for (int j = 0, k = 0; j < 3; j++) {
        if (queue.pop(k))
            cout << "Popped: " << k << endl;
        else
            break;
    }
    
    queue.print();

    for (int j = 0; j < 10; j++, i++) {
        if (!queue.push(i)) {
            cout << "Full queue" << endl;
            break;
        }
    }

    queue.print();

    for (int j = 0, k = 0; j < 8; j++) {
        if (queue.pop(k))
            cout << "Popped: " << k << endl;
        else
            break;
    }

    queue.print();

    for (int j = 0, k = 0; j < 1; j++) {
        if (queue.pop(k))
            cout << "Popped: " << k << endl;
        else
            break;
    }

    queue.print();

    for (int j = 0, k = 0; j < 1; j++) {
        if (queue.pop(k))
            cout << "Popped: " << k << endl;
        else
            break;
    }

    queue.print();

    return 0;
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

Queue::Queue() {
    size = 10;
    head = tail = nullptr;
}

bool Queue::push(int value) {
    if (head == nullptr) {
        head = tail = A;
        *head = value;
        return true;
    }

    if (tail == A + size - 1) {
        if (head == A)
            return false;
        tail = A;
        *tail = value;
        return true;
    }

    if (tail + 1 == head)
        return false;

    tail++;
    *tail = value;
    return true;
}

bool Queue::pop(int& value) {
    if (head == nullptr)
        return false;

    if (head == tail) {
        value = *head;
        head = tail = nullptr;
        return true;
    }

    if (head == A + size - 1) {
        value = *head;
        head = A;
        return true;
    }

    value = *head;
    head++;
    return true;
}

void Queue::print() {
    if (head == nullptr) {
        cout << "Empty queue" << endl;
        return;
    }

    int* current = A;
    cout << "Queue Array  -->  [";
    while (current != A + size) {
        cout << "  ";
        if (current == head)
            cout << "H_";
        if (current == tail)
            cout << "T_";
        cout << *current;
        current++;
    }
    cout << "  ]" << endl << endl;
}