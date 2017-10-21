#include "LinkedList.hpp"
#include <cmath>
#include <memory>
#define MAX pow(10, 10)
typedef LinkedList::node node;


LinkedList::LinkedList() {
	head = tail = NULL;
	_size = 0;
}
LinkedList::~LinkedList() {
	node* ptr = head, *pre = NULL;
	while (ptr!= NULL) {
		pre = ptr->next;
		delete ptr;
		ptr = pre;
	}
	head = tail = NULL;
	_size = 0;
}
void LinkedList::add(E e) {
	_size++;
	node* ptr = NULL;
	if (tail == NULL) {
		ptr = new node(e);
		head = tail = ptr;
	}
	else {
		ptr = new node(e);
		tail->next = ptr;
		tail = ptr;
	}
}
void LinkedList::clear(void) {
	_size = 0;
}
bool LinkedList::contain(E e) {
	node* ptr = head;
	while (ptr != NULL) {
		if (ptr->data == e) return 1;
		else ptr = ptr->next;
	}
	return 0;
}
bool LinkedList::isEmpty(void) {
	if (_size == 0) return 1;
	else return 0;
}
void LinkedList::remove(E e) {
	while(contain(e)) {
		node* ptr = head, *pre = head, *po = head;
		int index = indexOf(e);
		if (index == 0) {
			ptr = head->next;
			delete head;
			head = ptr;
			_size--;
			continue;
		}
		while (--index&&ptr!=NULL) {
			ptr = ptr->next;
		}
		po = ptr->next;
		pre = po->next;
		delete po;
		ptr->next = pre;
		_size--;
	}
}
E& LinkedList::operator[](int index) {
	return get(index);
}
E& LinkedList::get(int index) {
	node* ptr = head;
	while (index--) {
		ptr = ptr->next;
	}
	return ptr->data;
}
int LinkedList::indexOf(E element) {
	if (!contain(element)) return -1;
	int index = 0;
	node* ptr = head;
	while (ptr != NULL) {
		if (ptr->data == element) return index;
		else {
			ptr = ptr->next;
			index++;
		}
	}
}
node* Merge(node* l1, node* l2) {
	if (l1 == NULL) return l2;
	if (l2 == NULL) return l1;
	if (l1->data < l2->data) {
		l1->next = Merge(l1->next, l2);
		return l1;
	}
	else {
		l2->next = Merge(l1, l2->next);
		return l2;
	}
}
node* Mergesort(node* head) {
	if (head == NULL || head->next == NULL) return head;
	node* ptr = head, *pre = head, *po = head;
	while (po != NULL&&po->next != NULL) {
		ptr = pre;
		pre = pre->next;
		po = po->next->next;
	}
	ptr->next = NULL;
	node* l1 = Mergesort(head);
	node* l2 = Mergesort(pre);
	return Merge(l1, l2);
}
void LinkedList::sort(void) {
	head = Mergesort(head);
}
int LinkedList::size(void) {
	return _size;
}