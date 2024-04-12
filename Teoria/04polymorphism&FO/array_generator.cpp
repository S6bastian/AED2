#include <iostream>
#include <fstream>
#include <random>
#include <ctime>


// Genera un array de tamaño 'size' con números enteros aleatorios en el rango [min, max]
long* generateRandomArray(long size, long min, long max) {
    // Semilla para la generación de números aleatorios
    std::mt19937 rng(time(0));
    // Distribución uniforme de los números aleatorios
    std::uniform_int_distribution<long> dist(min, max);

    // Crear el array
    long* array = new long[size];
    // Llenar el array con números aleatorios
    for (long i = 0; i < size; ++i) {
        array[i] = dist(rng);
    }
    return array;
}

// Escribe el array de números en un archivo de texto
void writeArrayToFile(long* array, long size, const std::string& filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int i = 0; i < size; ++i) {
            outFile << array[i] << " ";
        }
        outFile.close();
        std::cout << "Array written to file: " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main() {
    long n = 10000000;
    long min = 0;
    long max = 10000000;
    long* data = generateRandomArray(n, min, max);

    // Nombre del archivo de salida
    std::string filename = "random_numbers.txt";

    // Escribir el array de números en el archivo
    writeArrayToFile(data, n, filename);

    delete[] data;

    return 0;
}