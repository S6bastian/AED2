/*
    Crear array de 10 que se ordene automaticamente, al llenarse el array se crea otro al que apunta, tiene dos punteros ini, end
    metodos:
    necesita constructor y destructor
    add(int number)
    del(int number)
    find()
    print() solo imprime los numeros que existen, no todos

    USAR BUSQUEDA BINARIA OPCIONAL, y verificar si esta en los bloques antes de la BINBUS, supongo que será el find
*/
#include <iostream>
using namespace std;

struct Node {
    int* array, size;
    Node* next, * previous;

    Node();
    ~Node();
};

struct Elementor { //xd
    int* first_element, * last_element;
    Node* first_array, * last_array;

    Elementor();
    ~Elementor();
    bool find(int, int*&, Node*&);
    void add(int);
    void del(int);
    void print();
};

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

int main(){
    Elementor elementor;
    int i = 0;

    for (; i < 11;i++)
        elementor.add(i);

    elementor.print();

    return 0;
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

//Node
Node::Node() {
    size = 10;
    array = new int[size];
    next = previous = nullptr;
}

Node::~Node() {
    delete[] array;
    next = nullptr;
}


//Elementor
Elementor::Elementor() {
    first_array = last_array = nullptr;
    first_element = last_element = nullptr;
}

Elementor::~Elementor() {
    //solo Dios sabe
}

bool Elementor::find(int value, int*& element_position, Node*& element_array) {
    element_array = first_array;
    element_position = first_element;

    while (value < *element_position && *element_position != *last_element) {
        if (element_position == element_array->array + element_array->size - 1) {
            element_array = element_array->next;
            element_position = element_array->array;
        }
        else
            element_position++;
    }

    if (value == *element_position)
        return true;

    return false;
}

void Elementor::add(int value) {
    if (first_array == nullptr) {
        first_array = last_array = new Node();
        first_element = last_element = first_array->array;
        *first_element = value;
        return;
    }

    if (first_element == last_element) {
        last_element++;

        if (*first_element > value) {
            *last_element = *first_element;
            *first_element = value;
        }
        else
            *last_element = value;
        
        return;
    }

    int* current_element = first_element, tmp1 = value, tmp2;
    Node* current_array = first_array;

    while (current_element != last_element) {
        if (*current_element >= value) {
            tmp2 = *current_element;
            *current_element = tmp1;
            tmp1 = tmp2;
        }
        
        if (current_element == current_array->array + current_array->size - 1) {
            current_array = current_array->next;
            current_element = current_array->array;
        }
        else
            current_element++;
    }

    tmp2 = *current_element;
    *current_element = tmp1;
    tmp1 = tmp2;

    if (current_element == current_array->array + current_array->size - 1) {
        current_array->next = new Node();
        current_array = last_array = current_array->next;
        current_element = last_element = current_array->array;
    }
    else {
        current_element++;
        last_element++;
    }

    *current_element = tmp1;
}

void Elementor::del(int value) {
    Node* element_array = nullptr, * array_backtrack = nullptr;
    int* element_position = nullptr, * element_backtrack = nullptr;
    
    if (find(value, element_position, element_array)) {
        if (first_element == last_element) {
            first_element = last_element = nullptr;
            delete first_array;
            first_array = last_array = nullptr;
            return;
        }

        while (element_position != last_element) {
            element_backtrack = element_position;

            if (element_position == element_array->array + element_array->size - 1) {
                array_backtrack = element_array;
                element_array = element_array->next;
                element_position = element_array->array;
            }
            else
                element_position++;

            *element_backtrack = *element_position;
        }

        if (element_position == last_array->array) {
            delete last_array;
            last_array = array_backtrack;
        }

        last_element = element_backtrack;
        return;
    }
}

void Elementor::print() {
    Node* current_array = first_array;
    int* current_element = first_element;
    
    cout << "Elementor -->  [";
    
    while (current_element != last_element) {
        if (current_element == current_array->array + current_array->size - 1) {
            cout << " " << *current_element << " ]  -->  [";

            current_array = current_array->next;
            current_element = current_array->array;
        }
        else {
            cout << " " << *current_element;
            current_element++;
        }
    }

    cout << " " << *current_element << " ]";
}