#include "ArrayList.hpp"

ArrayList::ArrayList(){
	storage = NULL;
	_size = 0;
	_maxsize = 64;
}
ArrayList::~ArrayList() {
	delete []storage;
	_size = 0;
}
void ArrayList::add(E e) {
	if (storage == NULL) storage = new int[_maxsize];
	if (_size<_maxsize) {
		storage[_size] = e;
		_size++;
	}
	else if (_size == _maxsize) {
		extend();
		storage[_size] = e;
		_size++;
	}
}
void ArrayList::remove(E e) {
	if (contain(e)) {
		for (int j = 0; j<_size; j++) {
			if (storage[j] == e) {
				for (int i = j; i<_size - 1; i++)
					storage[i] = storage[i + 1];
				_size--;
				j--;
			}
		}
	}
}
void ArrayList::clear() {
	_size = 0;
}
bool ArrayList::contain(E e) {
	for (int i = 0; i<_size; i++)
		if (storage[i] == e) return 1;
	return 0;
}
bool ArrayList::isEmpty() {
	if (_size == 0) return 1;
	else return 0;
}
E& ArrayList::operator[](int index) {
	return storage[index];
}
E& ArrayList::get(int index) {
	return storage[index];
}
int ArrayList::indexOf(E element) {
	if (contain(element)) {
		for (int i = 0; i<_size; i++)
			if (storage[i] == element) return i;
	}
	else return -1;
}
int ArrayList::size() {
	return _size;
}
void ArrayList::extend() {
	int new_size = _maxsize * extend_factor;
	E* new_storage = new E[new_size]();
	for (int i = 0; i < this->_size; i++) {
		new_storage[i] = this->storage[i];
	}
	delete[] storage;
	storage = new_storage;
	_maxsize = new_size;
}
void quicksort(E* storage, int num1, int num2) {
	if (num1 < num2) {
		int i = num1, j = num2, ele = storage[num1];
		while (i < j) {
			while (i < j&&storage[j] >= ele) {
				j--;
			}
			if (i < j) {
				storage[i] = storage[j];
				i++;
			}
			while (i < j&&storage[i] < ele) {
				i++;
			}
			if (i < j) {
				storage[j] = storage[i];
				j--;
			}
		}
		storage[i] = ele;
		quicksort(storage, num1, i - 1);
		quicksort(storage, i + 1, num2);
	}
}
void ArrayList::sort() {
	quicksort(storage, 0, _size - 1);
}