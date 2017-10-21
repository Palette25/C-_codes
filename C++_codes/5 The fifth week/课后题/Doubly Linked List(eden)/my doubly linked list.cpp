#include <string>
#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace std;
class list {
 public:
  typedef int data_type;
  struct node {
   public:
    data_type data;
    node* next;
    node* prev;
    node(data_type data = 0, node* next = NULL, node* prev = NULL)
        : data(data), next(next), prev(prev){};
  };
  typedef node listNode;
  typedef node* listPointer;
  typedef unsigned int size_type;

 private:
  listPointer head;
  listPointer tail;
  size_type _size;
  inline listPointer at(int index) {
    if (index >= 0 && index < this->_size) {
      if (index <= this->_size / 2) {
        int counter = 0;
        listPointer p = this->head;
        while (counter != index) {
          counter++;
          p = p->next;
        }
        return p;
      } else {
        int counter = 0;
        listPointer p = this->tail;
        while (counter != this->_size - 1 - index) {
          counter++;
          p = p->prev;
        }
        return p;
      }
    }
    return NULL;
  }

 public:
  list();
  // construct a list from an exist array
  list(const data_type[], int length);
  list(const list&);
  list& operator=(const list&);
  ~list();

  // Capacity
  bool empty(void) const;
  size_type size(void) const;

  // Element access
  data_type& front(void) const;
  data_type& back(void) const;

 public:
  // output
  std::string toString(void) const;

  // Modifiers
  void assign(const list&);
  void assign(const data_type datas[], int length);
  void push_front(const data_type&);
  void push_back(const data_type&);
  void pop_front(void);
  void pop_back(void);

  void insert(int position, const data_type& data);
  void erase(int position);
  void clear(void);

  // Operations
  // split this list into to lists at the given position
  void split(int position, list* des1, list* dest2);
  // merge two list to this list from src1 and src2
  list& merge(const list& src1, const list& src2);
  // remove the elements who satisfy the condition
  list& remove_if(bool (*condition)(listPointer));

  // remove duplicate elements
  list& unique(void);
  // reverse the list
  list& reverse(void);

  // operators
  data_type& operator[](int index);
  list& operator+=(const list&);
  friend std::ostream& operator<<(std::ostream& os, const list& li);
};
using namespace std;

list::list(){
	head = NULL;
	_size = 0;
	tail = NULL;
}
list::list(const data_type arr[], int length){
	if(length>0){
	int i = 0;
	_size = length;
	node* ptr = NULL, *pre = NULL;
	for(i=0;i<length;i++){
		if(i==0) {
			head = new node(arr[i]);
			ptr = head;
		}
		else {
			ptr = new node(arr[i]);
			pre->next = ptr;
			ptr->prev = pre;
		}
		pre = ptr;
		if(i==length-1) tail = ptr;
	}
} 
    else {
    	head = NULL;
	_size = 0;
	tail = NULL;
    }
}
list::list(const list& list1){
	int i = 0;
	_size = list1._size;
	node* ptr = NULL, *pre = NULL, *po = NULL;
	for(i=0;i<_size;i++){
		if(i==0) {
			head = new node(list1.head->data);
			po = head;
			ptr = list1.head;
		}
		else {
			pre = new node(ptr->data);
			po -> next = pre;
			pre -> prev = po;
			po = po -> next;
		}
		if(i==_size-1) tail = po;
		ptr = ptr -> next;
	}
}
list& list::operator=(const list& list1){
	clear();
	int i = 0; 
	_size = list1._size;
	node* ptr = NULL, *pre = NULL, *po = NULL;
	for(i=0;i<_size;i++){
		if(i==0) {
			head = new node(list1.head->data);
			po = head;
			ptr = list1.head;
		}
		else {
			pre = new node(ptr->data);
			po -> next = pre;
			pre -> prev = po;
			po = po -> next;
		}
		if(i==_size-1) tail = po;
		ptr = ptr -> next;
	}
	return *this;
}
list::~list(){
	clear();
}
bool list::empty(void) const{
	if(_size==0) return 1;
	else return 0;
}
list::size_type list::size(void) const{
	return _size;
}
list::data_type& list::front(void) const{
	return (head->data);
}
list::data_type& list::back(void) const{
	return (tail->data);
}
std::string list::toString(void) const{
	string str = "NULL";
	if(_size>0){
		str += "<-";
	node* ptr = head;
	int i = 0;
	char arr[100] = {0};
	for(i=0;i<_size;i++){
		memset(arr, 0, 100);
		int var = ptr->data, j = 0;
		if(var==0) arr[0] = '0';
		while(var!=0){
			arr[j++] = var % 10 + '0';
			var /= 10;
		}
        for(var=0;var<j/2;var++){
        	char temp = arr[j-1-var];
        	arr[j-1-var] = arr[var];
        	arr[var] = temp;
        }
        if(i!=_size-1) {
            str += arr ;
            str += "<->";
        }
        else str += arr;
        ptr = ptr -> next;
	}
	str += "->NULL";
}
	return str;
}
void list::assign(const list& list1){
	*this = list1;
}
void list::assign(const data_type arr[], int length){
	if(length>0){
	clear();
	int i = 0;
	_size = length;
	node* ptr = NULL, *pre = NULL;
	for(i=0;i<length;i++){
		if(i==0) {
			head = new node(arr[i]);
			ptr = head;
		}
		else {
			ptr = new node(arr[i]);
			pre->next = ptr;
			ptr->prev = pre;
		}
		pre = ptr;
		if(i==length-1) tail = ptr;
	}
}
}
void list::push_front(const data_type& num){
	if(head==NULL) {
	   head = new node(num);
	   tail = head;
	   _size++;
}
	else {
	node* ptr = new node(num);
	head -> prev = ptr;
	ptr -> next = head;
	head = ptr;
	_size++;
}
}
void list::push_back(const data_type& num){
	node* ptr = new node(num);
	tail -> next = ptr;
	ptr -> prev = tail;
	tail = ptr;
	_size++;
}
void list::pop_front(void){
	if(head!=NULL) {
	if(head->next!=NULL) {
	node* pre = head -> next;
	delete head;
	head = pre;
	head -> prev = NULL;
	_size--;
}
    else {
     delete head;
     _size--;
     head = NULL;
 }
}
}
void list::pop_back(void){
	if(tail!=NULL) {
	if(_size==1) {
		delete  tail;
		tail = head = NULL;
		_size = 0;
	}
	else {
	node* ptr = tail -> prev;
	delete tail;
	tail = ptr;
	tail -> next = NULL;
	_size--;
}
}
}

void list::insert(int position, const data_type& data){
	if(position>=0&&position<=_size){
	if(position==0) {
	    if(head!=NULL) push_front(data);
	    else {
	       head = new node(data);
	       tail = head;
	       _size = 1;
	   }
	}
	else if(position==_size) {
	      push_back(data);
	      return;
	  }
	if(position>0&&position<_size){
		node* ptr = head, *pre = NULL;
		while(position>1) {
			ptr = ptr -> next;
			position--;
		}
		pre = new node(data);
		pre -> next = ptr -> next;
		(ptr -> next)->prev = pre;
		ptr -> next = pre;
		pre -> prev = ptr;
		_size++;
	}
    }
} 
void list::erase(int position){
	if(_size>0&&position<_size){
	int i = 0;
	node* ptr = head;
	while(i<position){
		ptr = ptr -> next;
		i++;
	}
	if(i==0) pop_front();
	else if(i==_size-1) pop_back();
	else {
		(ptr->prev)->next = ptr->next;
		(ptr->next)->prev = ptr->prev;
		delete ptr;
		ptr = NULL;
		_size--;
	}
}
}
void list::clear(void){
	node* ptr = head, *pre = NULL;
	while(ptr!=NULL){
		pre = ptr -> next;
		delete ptr;
		ptr = pre;
	}
	ptr = NULL;
	head = NULL;
	tail = NULL;
	_size = 0;
}
void list::split(int position, list* dest1, list* dest2){
	int pos = 0;
	dest1->clear();
	dest2->clear();
	int size = _size;
	for(pos=0;pos<position;pos++)
		dest1->insert(pos, at(pos)->data);
	for(pos=position;pos<size;pos++)
	    dest2->insert(pos - position, at(pos)->data);
}
list& list::merge(const list& src1, const list& src2){
	if(src1.head!=NULL||src2.head!=NULL){
		int flag = 0;
	if(src1.head!=head&&src2.head!=head) {
	    clear();
	    flag = 1;
	}
	list list1(src1), list2(src2);
	_size = list1._size + list2._size;
	node* ptr = NULL, *pre = NULL, *ppr = NULL, *po = NULL;
	if(flag==1) {
	head = new node(list1.head->data);
	ptr = head; pre = NULL;
	ppr = list1.head->next; po = list2.head;
	while(ptr!=NULL&&ppr!=NULL) {
		pre = new node(ppr->data);
		ptr -> next = pre;
		pre ->prev = ptr;
		ptr = ptr -> next;
		ppr = ppr -> next;
	}
    }
    else {
       ptr = tail;
       po = list2.head;
   }
	while(ptr!=NULL&&po!=NULL) {
		pre = new node(po->data);
		ptr -> next = pre;
		pre ->prev = ptr;
		ptr = ptr -> next;
		po = po -> next;
	}
	tail = pre;
	return *this;
}
    else {
    	head = NULL;
    	tail = NULL;
     return *this;
 }
}
list& list::remove_if(bool (*condition)(listPointer)){
	node* ptr = head, *pre = NULL;
	int pos = 0;
	while(ptr!=NULL&&pos<_size) {
		pre = ptr -> next;
      if((*condition)(ptr)==1) {
          erase(pos);
          pos--;
      }
      ptr = pre;
      pos++;
    }
    if(_size==0) tail = head = NULL;
    return *this;
} 
list& list::unique(void){
	int i = 0, flag[10000] = {0}, pos = 0;
	node* ptr = head;
	while(ptr!=NULL) {
		flag[ptr->data]++;
		if(flag[ptr->data]>1) {
			flag[ptr->data]--;
			ptr = ptr->next;
			erase(pos);
			pos--;
		}
		else ptr = ptr->next;
		pos++;
	}
	return *this;
}
list& list::reverse(void){
	int arr[1000], i = 0;
	node* ptr = head;
	while(ptr!=NULL) {
		arr[i++] = ptr->data;
		ptr = ptr->next;
	}
	ptr = head;
	while(ptr!=NULL){
		ptr->data = arr[--i];
		ptr = ptr->next;
	}
	return *this;
}
list::data_type& list::operator[](int index){
	int i = 0;
	node* ptr = head;
	for(i=0;i<index;i++)
		ptr = ptr->next;
	return ptr->data;
}
list& list::operator+=(const list& list1){
	int i = 0;
	int num = list1._size, num1 = _size;
	node* ptr = head, *pre = list1.head;
	while(num--) {
	    insert(num1++, pre->data);
	    pre = pre->next;
	}
	return *this;
}
std::ostream& operator<<(std::ostream& os, const list& li){
	os << li.toString();
	return os;
}

bool condition1(list::listPointer p) { return true; }

bool condition2(list::listPointer p) {
  if (p->data % 2 == 0) {
    return false;
  }
  return true;
}

bool condition3(list::listPointer p) {
  if (p->data > 5) {
    return false;
  }
  return true;
}

void outputList(const list& li) {
  cout << li << " size:" << li.size();
  if (&li.front() == NULL) {
    cout << " front:NULL";
  } else {
    cout << " front:" << li.front();
  }

  if (&li.back() == NULL) {
    cout << " back:NULL";
  } else {
    cout << " back:" << li.back();
  }
  cout << endl;
}
int main() {
  int n, m;

  cin >> n >> m;

  int* a = new int[n]();

  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  if(true) {
    list li1(a, n);
    li1.insert(2, 111);
    li1.push_front(150);
    list li2(li1);
    outputList(li1);
    outputList(li2);
  }
  cout << endl;
  if (true) {
    list li1;
    for (int i = 0; i < n; i++) {
      li1.insert(i, a[i]);
    }
    for (int i = 0; i < m; i++) {
      li1.erase(i);
    }
    outputList(li1);
  }

  cout << endl;

  if (true) {
    list li1(a, n), li2, li3;
    li1 = li2 = li3 = li1;
    outputList(li1);
    li1.split(0, &li2, &li3);
    outputList(li1);
    outputList(li2);
    outputList(li3);
    li1.split(li1.size(), &li2, &li3);
    outputList(li1);
    outputList(li2);
    outputList(li3);
    li1.split(li1.size() / 2, &li2, &li3);
    cout << li2.toString() << endl;
    cout << li3.toString() << endl;
    li1 += (li2 += li1).merge(li1, li1);
    outputList(li1);
    li1 += li3;
    li2.merge(li1, li3);
    for (int i = 0; i < li1.size(); i++) {
      cout << li1[i] << " ";
    }
    cout << endl;
    outputList(li2);
  }

  cout << endl;

  cout << endl;

  if (true) {
    list li1(a, n);
    li1.remove_if(condition1);
    cout << li1 << " " << endl;
    li1.assign(a, n);
    li1.remove_if(condition2);
    cout << li1 << endl;
    li1.assign(a, n);
    li1.remove_if(condition3);
    outputList(li1);
}

  cout << endl;

  if (true) {
    list li(a, n);
    li.merge(li, li).merge(li, li).unique();
    outputList(li);
  }

  delete[] a;

  return 0;
}


