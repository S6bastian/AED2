#include <iostream>
using namespace std;

template<class T>
struct Node {
    T value;
    Node<T>* next;

    Node(T);
    Node(T, Node<T>*);
};

template<class T>
struct OrderedList {
    Node<T>* head;

    OrderedList();
    bool find(T, Node<T>**&);
    bool insert(T);
    bool remove(T);
    void print();
};

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------


int main() {
    OrderedList<int> list;
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

template<class T>
Node<T>::Node(T v) {
    value = v;
    next = nullptr;;
}

template<class T>
Node<T>::Node(T v, Node<T>* n) {
    value = v;
    next = n;
}

//*********************************************************************************************

template<class T>
OrderedList<T>::OrderedList() {
    head = nullptr;
}

template<class T>
bool OrderedList<T>::find(T value, Node<T>**& p) {
    for (p = &head; *p && (*p)->value < value; p = &(*p)->next);
    return *p && (*p)->value == value;
}

template<class T>
bool OrderedList<T>::insert(T value) {
    Node<T>** p = nullptr;

    if (find(value, p))
        return false;

    *p = new Node<T>(value, *p);
    return true;
}

template<class T>
bool OrderedList<T>::remove(T value) {
    Node<T>** p = nullptr;

    if (!find(value, p))
        return false;

    Node<T>* tmp = *p;
    *p = (*p)->next;
    delete tmp;
    return true;
}

template<class T>
void OrderedList<T>::print() {
    cout << "OrderedList";
    for (Node<T>** p = &head; *p; p = &(*p)->next)
        cout << "  -->  " << (*p)->value;
    cout << "  -->  nullptr" << endl;
}