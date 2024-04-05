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
    
    elementor.print();

    for (int i = 9; i > 0; i -= 2)
        elementor.add(i);

    elementor.print();
    
    for (int i = 0; i < 20; i += 2)
        elementor.add(i);

    elementor.print();

    for (int i = 39; i > 9; i -= 2)
        elementor.add(i);

    elementor.print();

    for (int i = 0; i < 40; i += 5)
        elementor.del(i);

    elementor.print();

    for (int i = 31; i < 40; i++)
        elementor.del(i);

    elementor.print();

    elementor.del(29);

    elementor.print();
    
    for (int i = 0; i < 29; i++)
        elementor.del(i);

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

    if (first_array == nullptr)
        return false;

    while (*element_position < value && *element_position != *last_element) {
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
    //Si la lista está vacía
    if (first_array == nullptr) {
        first_array = last_array = new Node();
        first_element = last_element = first_array->array;
        *first_element = value;
        return;
    }

    //Si contiene algún elemento
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

    if (*current_element >= value) {
        tmp2 = *current_element;
        *current_element = tmp1;
        tmp1 = tmp2;
    }

    if (current_element == current_array->array + current_array->size - 1) {
        current_array->next = new Node();
        current_array->next->previous = current_array;
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
    Node* element_array = nullptr;
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
                element_array = element_array->next;
                element_position = element_array->array;
            }
            else
                element_position++;

            *element_backtrack = *element_position;
        }

        if (element_position == last_array->array) {
            last_array = last_array->previous;
            delete last_array->next;
            last_element = last_array->array + last_array->size - 1;
            return;
        }


        element_backtrack == nullptr ? last_element-- : last_element = element_backtrack;
        return;
    }
}

void Elementor::print() {
    Node* current_array = first_array;
    int* current_element = first_element;
    
    cout << "Elementor -->  ";

    if (current_array == nullptr) {
        cout << "nullptr" << endl;
        return;
    }

    cout << "[";
    
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

    cout << " " << *current_element << " ]" << endl;
}