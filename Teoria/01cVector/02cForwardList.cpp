#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next, * previous;

    Node(int v, Node* nxt = nullptr, Node* prv = nullptr) {
        value = v;
        next = nxt;
        previous = prv;
    }
};


struct cForwardList {
    Node* head, * tail;

    cForwardList() {
        head = tail = nullptr;
    }

    void push_back(int value) {
        if (head == nullptr) {
            head = tail = new Node(value);
            return;
        }

        tail->next = new Node(value, nullptr, tail);
        tail = tail->next;
    }

    void push_front(int value) {
        if (head == nullptr) {
            head = tail = new Node(value);
            return;
        }

        head->previous = new Node(value, head);
        head = head->previous;
    }

    void pop_back() {
        if (head == nullptr)
            return;

        if (tail == head) {
            delete tail;
            tail = head = nullptr;
            return;
        }

        tail = tail->previous;
        delete tail->next;
        tail->next = nullptr;
    }

    void pop_front() {
        if (head == nullptr)
            return;

        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return;
        }

        head = head->next;
        delete head->previous;
        head->previous = nullptr;
    }

    int& operator[](int index) {
        Node* current = head;
        if (index < 0)
            throw out_of_range("Negative index not supported");

        for (int i = 0; current != nullptr && i < index; i++, current = current->next);
        
        if (current == nullptr)
            throw out_of_range("Index out of range");

        return current->value;
        
    }

    void print() {
        cout << "cForwardList";
        for (Node* current = head; current != nullptr; current = current->next)
            cout << "  -->  " << current->value;
        cout << "  -->  nullptr" << endl;
    }
};

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

int main() {
    cForwardList list;
    for (int i = 0; i < 10; i++)
        list.push_back(i);

    list.print();

    for (int i = 0; i < 5; i++)
        list.pop_back();

    list.print();

    for (int i = 10; i < 20; i++)
        list.push_front(i);

    list.print();

    for (int i = 0; i < 5; i++)
        list.pop_front();

    list.print();

    cout << list[5] << endl;
    list[5] = 777;
    list.print();

    return 0;
}
