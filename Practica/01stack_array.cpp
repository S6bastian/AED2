/*
    Crear una pila (stack) del tipo array que tenga push() y pop() como metodos.
*/

#include <iostream>
using namespace std;

struct Stack {
    int array[10];
    int* top;
    int* lastItem;

    Stack();
    bool push(int);
    bool pop(int&);
    void print();

};

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

int main()
{
    Stack stack1;

    for (int i = 0; i < 11; i++)
        stack1.push(i);
    
    stack1.print();

    for (int i = 0, x; i < 3; i++) {
        stack1.pop(x);
        cout << "Popped: " << x << endl;
    }

    stack1.print();

    for (int i = 20; i < 25; i++)
        stack1.push(i);

    stack1.print();
    
    return 0;
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

Stack::Stack() {
    top = nullptr;
    lastItem = array + 10 - 1;
}

bool Stack::push(int value) {
    if (top == lastItem) {
        cout << "Full stack :(" << endl;
        return false;
    }
    top == nullptr ? top = array : top++;
    *top = value;
    return true;
}

bool Stack::pop(int& x) {
    if (top == nullptr) {
        cout << "Empty stack :(" << endl;
        return false;
    }
    x = *top;
    top == array ? top = nullptr : top--;
    return true;
}

void Stack::print() {
    cout << "Stack --> [ ";
    for (int* a = array; a <= top; a++)
        cout << *a << " ";
    cout << "]" << endl;
}
