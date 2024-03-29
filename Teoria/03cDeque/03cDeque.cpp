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
    void pop_back();
    void pop_front();
    int& operator[](int);

    void print();
};

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

int main() {
    cDeque deque;
    
    int i = 0;

    for (int j = i; i < j + 14; i++)
        deque.push_back(i);
    
    deque[5] = 55;
    cout << "Updated:" << deque[5] << endl;

    deque.print();

    for (int j = i; i < j + 8; i++)
        deque.pop_front();

    deque[5] = 130;
    cout << "Updated:" << deque[5] << endl;

    deque.print();

    for (int j = i; i < j + 11; i++)
        deque.push_front(i);

    deque[6] = 260;
    cout << "Updated:" << deque[6] << endl;

    deque.print();

    for (int j = i; i < j + 6; i++)
        deque.pop_back();

    deque[0] = 320;
    cout << "Updated:" << deque[0] << endl;

    deque.print();

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
    if (head_map == nullptr) {
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

void cDeque::pop_back() {
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
        delete *(tail_map--);
        tail_array = (*tail_map)->array + (*tail_map)->size - 1;
        return;
    }

    tail_array--;
    return;
}

void cDeque::pop_front() {
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
        delete *(head_map++);
        head_array = (*head_map)->array;
        return;
    }

    head_array++;
    return;
}

int& cDeque::operator[](int index) {
    if (head_map == nullptr)
        throw exception("Null cDeque");

    Node** current_map = head_map;
    int current_size = 0, offset;

    if (head_map == tail_map) {
        current_size += tail_array - head_array;
        if (index <= current_size)
            return *(head_array + index);
    }

    
    else {
        current_size += (*current_map)->array + (*current_map)->size - head_array;
        if (index <= current_size)
            return *(head_array + index);
        current_map++;

        while (current_map != tail_map) {
            current_size += (*current_map)->size;
            if (index <= current_size)
                return *((*current_map)->array + index - (current_size - (*current_map)->size));
            current_map++;
        }

        current_size += tail_array - (*tail_map)->array;
        if (index <= current_size)
            return *((*current_map)->array + index - (current_size - (tail_array - (*tail_map)->array)));
    }

    if (index <= current_size)
        throw out_of_range("Index out of range");
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
        cout << "  " << *current_array;
        
        if (current_array == (*current_map)->array + (*current_map)->size - 1) {
            current_map++;
            current_array = (*current_map)->array;
            cout << " ] -- [";
        }
        else
            current_array++;
    }
    
    cout << "  " << *current_array << "  ]\n";
    cout << "Head: " << *head_array << endl;
    cout << "Tail: " << *tail_array << endl << endl;
    return;
}