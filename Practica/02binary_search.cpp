/*
    Crear una funcion de Busqueda binaria BinBus(int* ini, int* end, int*& pos, int key)
*/

#include <iostream>
using namespace std;

bool BinBus(int*, int*, int*&, int);

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

int main()
{
	int array[15];

	for (int i = 0; i < 15; i++) {
		*(array + i) = (i + 1) * 2;
	}

	int* ini = array;
	int* end = array + 14;
	int* pos = nullptr;

	for (int i = 0; i < 15; i++) {
		cout << *(array + i) << " \n";
	}

	if (BinBus(ini, end, pos, 16)) {
		cout << "Founded\n";
	}
	else {
		cout << "Not founded";
	}
    
    return 0;
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

bool BinBus(int* ini, int* end, int*& pos, int key) {
    pos = ini;
    pos += (ini - end) / 2;
    while (pos <= end) {
        pos = ini;
        if (*pos == key)
            return true;
        pos += (ini - end) / 2;
        *pos < key ? ini = pos + 1 : end = pos - 1;
    }
    pos = nullptr;
    return false;
}