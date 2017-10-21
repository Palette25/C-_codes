#ifndef SIMPLE_ITERATOR
#define SIMPLE_ITERATOR

class simple_iterator{
public:
	simple_iterator(){
		pointer = NULL;
		size = pos = 0;
	}
	simple_iterator(char* ptr){
		pointer = ptr;
	}
	simple_iterator prev(){
		return simple_iterator(pointer-1);
	}
	simple_iterator next(){
		return simple_iterator(pointer+1);
	}
	simple_iterator begin(){
		char* ptr = pointer;
		while (*ptr != '\0') {
			ptr--;
		}
		return simple_iterator(++ptr);
	}
	simple_iterator end(){
		char* ptr = pointer;
		while (*ptr != '\0') {
			ptr++;
		}
		return simple_iterator(--ptr);
	}
	friend char operator*(simple_iterator oth){
		return *(oth.pointer);
	}
	simple_iterator operator++(){
		return simple_iterator(++pointer);
	}
	simple_iterator operator--(){
		return simple_iterator(--pointer);
	}
	simple_iterator operator++(int num){
		return simple_iterator(pointer++);
	}
	simple_iterator operator--(int num){
		return simple_iterator(pointer--);
	}
	bool operator==(simple_iterator iter){
		if(*pointer==*iter.pointer) return 1;
		else return 0;
	}
	bool operator!=(simple_iterator iter){
		if(*pointer!=*iter.pointer) return 1;
		else return 0;
	}
	bool operator<=(simple_iterator iter){
		if(*pointer <= *iter.pointer) return 1;
		else return 0;
	}
	bool operator>=(simple_iterator iter){
		if(*pointer >= *iter.pointer) return 1;
		else return 0;
	}
	bool operator<(simple_iterator iter){
		if(*pointer < *iter.pointer) return 1;
		else return 0;
	}
	bool operator>(simple_iterator iter){
		if(*pointer > *iter.pointer) return 1;
		else return 0;
	}
	simple_iterator operator+(int num){
		return simple_iterator(pointer+num);
	}
	simple_iterator operator-(int num){
		return simple_iterator(pointer-num);
	}
private:
	char* pointer;
	int size;
	int pos;
};

#endif