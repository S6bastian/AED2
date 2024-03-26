#include <iostream>
using namespace std;

struct cVector {
    int* array, * first, * last, size;

    cVector();
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
    cVector vector;
    for (int i = 0; i < 12; i++) {
        vector.push_front(i);
        vector.print();
    }
    for (int i = 3; i < 12; i++) {
        vector.pop_back();
        vector.print();
    }
    cout << vector[5];
    vector[5] = 20;
    cout << vector[5];
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

cVector::cVector() {
    size = 10;
    array = new int[size];
    first = last = nullptr;
}

void cVector::push_back(int value) {
    if (last == array + size - 1)
        return;
    last == nullptr ? last = first = array : last++;

    *last = value;
}

void cVector::push_front(int value) {
    if (last == array + size - 1)
        return;

    if (first == nullptr) {
        first = last = array;
        *first = value;
        return;
    }

    int* current = last;
    while (current != first - 1) {
        *(current + 1) = *current;
        current--;
    }
    last++;
    *first = value;
}

void cVector::pop_back() {
    if (last == nullptr)
        return;

    last == first ? last = first = nullptr : last--;
}

void cVector::pop_front() {
    if (first == nullptr)
        return;

    if (first == last) {
        first = last = nullptr;
        return;
    }

    for (int* current = array; current != last; current++)
        *current = *(current + 1);
    last--;
}

int& cVector::operator[](int index) {
    return array[index];
}

void cVector::print() {
    cout << "cVector -> [";
    for (int* current = array; current != last + 1; current++)
        cout << " " << *current;
    cout << " ]\n";
}