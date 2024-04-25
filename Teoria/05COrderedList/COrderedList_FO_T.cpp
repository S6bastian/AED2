#include <iostream>
using namespace std;

template<class T>
struct Greater {
    bool operator()(T a, T b) {
        return a > b;
    }
};

template<class T>
struct Less {
    bool operator()(T a, T b) {
        return a < b;
    }
};

template<class T>
struct Node {
    T value;
    Node<T>* next;

    Node(T);
    Node(T, Node<T>*);
};

template<class T, class C>
struct OrderedList {
    Node<T>* head;

    OrderedList();
    bool find(T, Node<T>**&, C);
    bool insert(T);
    bool remove(T);
    void print();
};



//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------


int main() {

    cout << "OrderedList using Greater functor" << endl;
    OrderedList<int, Greater<int>> list_greater;

    for (int i = 0; i < 12; i += 2)
        list_greater.insert(i);

    list_greater.print();

    for (int i = 0; i < 18; i += 3)
        list_greater.insert(i);

    list_greater.print();

    for (int i = 0; i < 18; i += 3)
        list_greater.remove(i);

    list_greater.print();

    for (int i = 0; i < 12; i += 2)
        list_greater.remove(i);

    list_greater.print();

    cout << endl << "OrderedList using Less functor" << endl;
    OrderedList<int, Less<int>> list_less;

    for (int i = 0; i < 12; i += 2)
        list_less.insert(i);

    list_less.print();

    for (int i = 0; i < 18; i += 3)
        list_less.insert(i);

    list_less.print();

    for (int i = 0; i < 18; i += 3)
        list_less.remove(i);

    list_less.print();

    for (int i = 0; i < 12; i += 2)
        list_less.remove(i);

    list_less.print();

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

template<class T, class C>
OrderedList<T, C>::OrderedList() {
    head = nullptr;
}

template<class T, class C>
bool OrderedList<T, C>::find(T value, Node<T>**& p, C FO) {
    for (p = &head; *p && FO((*p)->value, value); p = &(*p)->next);
    return *p && (*p)->value == value;
}

template<class T, class C>
bool OrderedList<T, C>::insert(T value) {
    Node<T>** p = nullptr;
    C FO;

    if (find(value, p, FO))
        return false;

    *p = new Node<T>(value, *p);
    return true;
}

template<class T, class C>
bool OrderedList<T, C>::remove(T value) {
    Node<T>** p = nullptr;
    C FO;

    if (!find(value, p, FO))
        return false;

    Node<T>* tmp = *p;
    *p = (*p)->next;
    delete tmp;
    return true;
}

template<class T, class C>
void OrderedList<T, C>::print() {
    cout << "OrderedList";
    for (Node<T>** p = &head; *p; p = &(*p)->next)
        cout << "  -->  " << (*p)->value;
    cout << "  -->  nullptr" << endl;
}