#include <iostream>
using namespace std;

struct Node {
    int* array, size;

    Node();
};


struct  cDeque {
    Node** map, ** head_map, ** tail_map;
    int* head_array, * tail_array, size;

    cDeque();
    void push_back(int);
    void push_front(int);
    void pop_back(int);
    void pop_front(int);

    void print();
};

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

int main()
{
    return 0;
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

//Node
Node::Node() {
    size = 5;
    array = new int[size];
}


//cDeque
cDeque::cDeque() {
    size = 10;
    map = new Node* [size];
    head_map = tail_map = nullptr;
    head_array = tail_array = nullptr;
}

void cDeque::push_back(int value) {
    if (tail_map == nullptr) {
        head_map = tail_map = map + size / 2;
        *head_map = *tail_map = new Node();
        head_array = tail_array = (*tail_map)->array + (*tail_map)->size / 2;
        *tail_array = value;
        return;
    }

    if (tail_array == (*tail_map)->array + (*tail_map)->size - 1) {
        tail_map++;
        *tail_map = new Node();
        tail_array = (*tail_map)->array;
        *tail_array = value;
        return;
    }

    tail_array++;
    *tail_array = value;
    return;

    // Falta agrandar map en caso sea necesario************
}

void cDeque::push_front(int value) {
    if (head_map = nullptr) {
        head_map = tail_map = map + size / 2;
        *head_map = new Node();
        head_array = tail_array = (*head_map)->array + (*head_map)->size / 2;
        *head_array = value;
        return;
    }
    
    if (head_array == (*head_map)->array) {
        head_map--;
        *head_map = new Node();
        head_array = (*head_map)->array + (*head_map)->size - 1;
        *head_array = value;
        return;
    }

    head_array--;
    *head_array = value;
    return;
    
    // Falta agrandar map en caso sea necesario************
}

void cDeque::pop_back(int value) {
    if (tail_map == nullptr) {
        throw exception("Nothing to delete");
        return;
    }

    if (tail_array == head_array) {
        delete tail_map;
        head_array = tail_array = nullptr;
        head_map = tail_map = nullptr;
        return;
    }

    if (tail_array == (*tail_map)->array) {
        tail_map--;
        delete (tail_map + 1);
        tail_array = (*tail_map)->array + (*tail_map)->size - 1;
        return;
    }

    tail_array--;
    return;
}

void cDeque::pop_front(int value) {
    if (head_map == nullptr) {
        throw exception("Nothing to delete");
        return;
    }

    if (head_array == tail_array) {
        delete head_map;
        head_map = tail_map = nullptr;
        head_array = tail_array = nullptr;
        return;
    }

    if (head_array == (*head_map)->array + (*head_map)->size - 1) {
        head_map++;
        delete (head_map - 1);
        head_array = (*head_map)->array;
        return;
    }

    head_array++;
    return;
}

void cDeque::print() {
    cout << "cDeque  -->";
    if (head_map == nullptr){
        cout << " nullptr\n";
        return;
    }
        
    cout << "  [";

    int* current_array = head_array;
    Node** current_map = head_map;
    while (current_array != tail_array) {
        if (current_array == (*current_map)->array + (*current_map)->size - 1) {
            current_map++;
            current_array = (*current_map)->array;
            cout << " ] -- [";
        }
        else
            current_array++;

        cout << "  " << *current_array;
    }
    
    cout << " ]\n";
}