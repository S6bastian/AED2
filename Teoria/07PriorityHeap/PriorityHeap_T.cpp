#include <iostream>
#include <vector>
#include <deque>
#include <algorithm> // Para std::swap
using namespace std;

template <class T>
struct Greater {
	bool operator()(T a, T b) {
		return a > b;
	}
};

template <class T>
struct Less {
	bool operator()(T a, T b) {
		return a < b;
	}
};

//*********************************************************************************************

template <class T, class Ctn = vector<T>, class Cmp = Greater<T>>		// <Type, Container, Comparison>
class Priority_heap {
public:
	Ctn container;
	Cmp comparator;

	void push(T);
	void pop();
	T top();
	void print();
};

//*********************************************************************************************

template <class T, class Ctn = vector<T>>
class Max_heap : public Priority_heap < T, Ctn, Greater<T>> {
};

template <class T, class Ctn = vector<T>>
class Min_heap : public Priority_heap < T, Ctn, Less<T>> {
};

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

int main() {
	Priority_heap <int, vector<int>, Greater<int>> test;
	cout << "****************** test ******************" << endl;

	for (int i = 0; i < 61; i += 3) {
		test.push(i);
	}
	test.print();
	cout << "top() = " << test.top() << endl;

	test.pop();
	test.print();

	Max_heap <int, vector<int>> max_test;
	cout << "****************** max_test ******************" << endl;

	for (int i = 1; i < 61; i += 3) {
		max_test.push(i);
	}
	max_test.print();
	cout << "top() = " << max_test.top() << endl;

	max_test.pop();
	max_test.print();

	Min_heap <int, deque<int>> min_test;
	cout << "****************** min_test ******************" << endl;

	for (int i = 2; i < 61; i += 3) {
		min_test.push(i);
	}
	min_test.print();
	cout << "top() = " << min_test.top() << endl;

	min_test.pop();
	min_test.print();

	return 0;
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

template<class T, class Ctn, class Cmp>
void Priority_heap<T, Ctn, Cmp>::push(T value) {
	container.push_back(value);

	int index = container.size() - 1;
	T* relocater = &container[index];
	
	while (index > 0 && comparator(*relocater, container[(index - 1) / 2])) {	// relocater > container
		swap(*relocater, container[(index - 1) / 2]);
		relocater = &container[(index - 1) / 2];
		index = (index - 1) / 2;
	}
}

template<class T, class Ctn, class Cmp>
void Priority_heap<T, Ctn, Cmp>::pop() {
	container.front() = container.back();
	container.pop_back();

	int index = 0;
	T* relocater = &container[index];
	if (index * 2 + 1 >= container.size() || index * 2 + 2 >= container.size())
		return;
		
	index = comparator(container[index * 2 + 1], container[index * 2 + 2]) ? index * 2 + 1 : index * 2 + 2;
	while (index < container.size() && comparator(container[index], *relocater)) {
		swap(*relocater, container[index]);
		relocater = &container[index];
		if (index * 2 + 1 >= container.size() || index * 2 + 2 >= container.size())
			return;
		index = comparator(container[index * 2 + 1], container[index * 2 + 2]) ? index * 2 + 1 : index * 2 + 2;
	}
}

template<class T, class Ctn, class Cmp>
T Priority_heap<T, Ctn, Cmp>::top() {
	return container.front();
}

template<class T, class Ctn, class Cmp>
void Priority_heap<T, Ctn, Cmp>::print() {
	for (int i = 0; i < container.size(); i++) {
		cout << container[i] << " ";
	}
	cout << endl;

}