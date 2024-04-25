#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;

    Node(int, Node*);
};

struct OrderedList {
    Node* head;

    OrderedList();
    bool find(int, Node**&);
    bool insert(int);
    bool remove(int);
    void print();
};

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------


int main() {
    OrderedList list;
    int i = 0;
    
    for (int i = 0; i < 12; i += 2)
        list.insert(i);

    list.print();

    for (int i = 0; i < 18; i += 3)
        list.insert(i);

    list.print();

    for (int i = 0; i < 18; i += 3)
        list.remove(i);

    list.print();

    for (int i = 0; i < 12; i += 2)
        list.remove(i);

    list.print();

    return 0;
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

Node::Node(int v, Node* n = nullptr) {
    value = v;
    next = n;
}

//*********************************************************************************************

OrderedList::OrderedList() {
    head = nullptr;
}

bool OrderedList::find(int value, Node**& p) {
    for (p = &head; *p && (*p)->value < value; p = &(*p)->next);
    return *p && (*p)->value == value;
}

bool OrderedList::insert(int value) {
    Node** p = nullptr;

    if (find(value, p))
        return false;

    *p = new Node(value, *p);
    return true;
}

bool OrderedList::remove(int value) {
    Node** p = nullptr;

    if (!find(value, p))
        return false;

    Node* tmp = *p;
    *p = (*p)->next;
    delete tmp;
    return true;
}

void OrderedList::print() {
    cout << "OrderedList";
    for (Node** p = &head; *p; p = &(*p)->next)
        cout << "  -->  " << (*p)->value;
    cout << "  -->  nullptr" << endl;
}