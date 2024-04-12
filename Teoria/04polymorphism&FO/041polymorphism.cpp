// Quick sort in C++
// Polimorfismo

#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <iomanip>

using namespace std;

template <class T>
struct  Cmp {
    virtual bool cm(T a, T b) = 0;
};

template <class T>
struct CLess : Cmp<T>{
    bool cm(T a, T b) {
        return a < b;
    }
};

template <class T>
struct CGreater : Cmp<T>{
    bool cm(T a, T b) {
        return a > b;
    }
};

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

// Lee los números del archivo de texto y los almacena en un array dinámico
long* readArrayFromFile(const std::string& filename, long& size) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        size = 0;
        return nullptr;
    }

    // Contar el número de números en el archivo
    size = 0;
    long num;
    while (inFile >> num) {
        ++size;
    }

    // Restablecer el puntero de archivo para leer desde el principio
    inFile.clear();
    inFile.seekg(0, std::ios::beg);

    // Crear un array dinámico para almacenar los números
    long* numbers = new long[size];

    // Leer los números del archivo y almacenarlos en el array
    for (long i = 0; i < size; ++i) {
        inFile >> numbers[i];
    }

    inFile.close();
    std::cout << "Array read from file: " << filename << std::endl;
    return numbers;
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

// Función para medir el tiempo de ejecución
double measureTime(void (*func)(long[], long, long, Cmp<long>*), long data[], long low, long high, Cmp<long>* C) {
    auto start = std::chrono::high_resolution_clock::now();
    func(data, low, high, C);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

// function to swap elements
void swap(long* a, long* b) {
    long t = *a;
    *a = *b;
    *b = t;
}

// function to print the array
void printArray(long array[], long size) {
    long i;
    for (i = 0; i < size; i++)
        cout << array[i] << " ";
    cout << endl;
}

// function to rearrange array (find the partition point)
long partition(long array[], long low, long high, Cmp<long>* C) {

    // select the rightmost element as pivot
    long pivot = array[high];

    // pointer for greater element
    long i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (long j = low; C->cm(j, high); j++) {
        if (array[j] <= pivot) {

            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;

            // swap element at i with element at j
            swap(&array[i], &array[j]);
        }
    }

    // swap pivot with the greater element at i
    swap(&array[i + 1], &array[high]);

    // return the partition point
    return (i + 1);
}

void quickSort(long array[], long low, long high, Cmp<long>* C) {
    if (C->cm(low, high)) {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on righ of pivot
        long pi = partition(array, low, high, C);

        // recursive call on the left of pivot
        quickSort(array, low, pi - 1, C);

        // recursive call on the right of pivot
        quickSort(array, pi + 1, high, C);
    }
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

// Driver code
int main() {

    CLess<long> L;

    // Nombre del archivo a leer
    std::string filename = "random_numbers.txt";
    long n = 1000000;
    // Leer los números del archivo
    long size;
    long* data = readArrayFromFile(filename, size);
    n = size;
    
    
    // Medir el tiempo de ejecución del algoritmo de ordenamiento
    double elapsedTime = measureTime(quickSort, data, 0, n - 1, &L);

    cout << "Sorted array in ascending order: \n";
    printArray(data, 5);

    // Imprimir el tiempo de ejecución con más decimales
    cout << "Time taken: " << std::fixed << std::setprecision(9) << elapsedTime << " seconds" << endl;

    // Liberar la memoria del array
    delete[] data;
}