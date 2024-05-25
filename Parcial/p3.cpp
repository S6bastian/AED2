#include <iostream>
#include <stdexcept>

class XVector
{
public:
    XVector(int size_map, int size_vec);
    ~XVector();
    void push_back(int);
    void push_front(int);
    int& operator[](int);
    int** map;
    int size_map, size_vec;

    //
    int** current_map, * current_vector, size;
};

XVector::XVector(int sm, int sv)
{
    size_map = sm;
    size_vec = sv;
    map = current_map = nullptr;
    current_vector = nullptr;
    size = 0;
}

XVector::~XVector()
{
    if (map) {
        while (current_map > map) {
            delete[] * current_map;
            current_map--;
        }
        delete[] * map;
        delete[] map;
    }
}

void XVector::push_back(int value) {
    size++;
    if (!map) {
        map = current_map = new int* [size_map];
        *current_map = current_vector = new int[size_vec];
        *current_vector = value;
        return;
    }

    if (current_vector == *current_map + size_vec - 1) {
        
        if (current_map == map + size_map - 1) {
            int** tmp, ** tmp_map;
            tmp = tmp_map = map;
            map = current_map = new int* [size_map * 2];

            while (tmp_map != tmp + size_map) {
                *current_map = *tmp_map;
                current_map++;
                tmp_map++;
                
                //int i = 0; quizá
                //map[i];
            }

            size_map *= 2;
            *current_map = current_vector = new int[size_vec];
            *current_vector = value;
            delete[] tmp;
            return;
        }
        
        current_map++;
        *current_map = current_vector = new int[size_vec];
        *current_vector = value;
        return;
    }

    current_vector++;
    *current_vector = value;
}

void XVector::push_front(int value) {
    if (!map) {
        push_back(value);
        return;
    }

    push_back(*current_vector);

    int** tmp_map, * tmp_vector, * front_track;
    tmp_map = current_map;
    tmp_vector = current_vector;

    while (tmp_vector != *map) {
        front_track = tmp_vector;

        if (tmp_vector == *tmp_map) {
            tmp_map--;
            tmp_vector = *tmp_map + size_vec - 1;
        }

        else {
            tmp_vector--;
        }

        *front_track = *tmp_vector;
    }

    *tmp_vector = value;
}

int& XVector::operator[](int index) {
    if (index >= size)
        throw ("Out of range");

    int** tmp_map, * tmp_vector, counter;
    tmp_map = map;
    tmp_vector = *map;
    counter = index;
    while (counter > 0) {
        if (counter >= size_vec) {
            tmp_map++;
            tmp_vector = *tmp_map;
            counter -= size_vec;
        }
        else {
            tmp_vector += counter;
            counter = 0;
        }
    }
    return *tmp_vector;
}

void print(XVector* p)
{ //no modificar esta función
    for (int i = 0; i < p->size; i++)
        std::cout << (*p)[i] << " ";
    std::cout << "\n";
}

int main()
{
    //no modificar esta función main
    XVector v(4, 3);
    v.push_back(3); v.push_back(8); v.push_back(1);
    v.push_back(4); v.push_back(9); v.push_back(6);
    v.push_back(7);
    print(&v);
    v.push_front(5); v.push_front(2);
    print(&v);
    v.push_front(11); v.push_front(17);
    v.push_back(22);
    print(&v);
    v.push_front(33); v.push_back(77);
    print(&v);
}