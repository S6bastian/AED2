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

	cout << "First element" << endl;
	if (BinBus(ini, end, pos, 2))
		cout << "Founded: " << *pos << " in position: " << pos - ini << "\n";
	else
		cout << "Not founded";

	cout << "Between first and last"<< end;
	if (BinBus(ini, end, pos, 16))
		cout << "Founded: " << *pos<< " in position: "<<pos - ini<<"\n";
	else 
		cout << "Not founded";
	
	cout << "Last element" << endl;
	if (BinBus(ini, end, pos, 30))
		cout << "Founded: " << *pos << " in position: " << pos - ini << "\n";
	else
		cout << "Not founded";

	cout << "Not in array" << endl;
	if (BinBus(ini, end, pos, 17))
		cout << "Founded: " << *pos << " in position: " << pos - ini << "\n";
	else
		cout << "Not founded";

	return 0;
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

bool BinBus(int* ini, int* end, int*& pos, int key) {
    while (ini <= end) {
        pos = ini + (end - ini) / 2;
        if (*pos == key)
            return true;
        if (*pos < key)
            ini = pos + 1;
        else
            end = pos - 1;
    }
    pos = nullptr;
    return false;
}
