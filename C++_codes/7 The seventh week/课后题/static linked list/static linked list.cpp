#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
#include <string>
#define MAX_STORAGE 1000
 class list{
    typedef int data_type;
    typedef int pointer;
    typedef unsigned int size_type;
    static const pointer nullpointer = -1;
    typedef struct node {
        data_type data;
        pointer next;
        node(const node &another) {
          this->operator=(another);
        }
        node& operator=(const node &another) {
          this->data = another.data;
          this->next = another.next;
        }
        node(data_type data = 0, pointer next = nullpointer) : data(data), next(next) {}
    } node;
    node storage[MAX_STORAGE];
    size_type _size;
    pointer head;
    pointer empty_head;
 public:
    list();
    list(const list& another);
    list& operator=(const list&);
    ~list();
     // Capacity
    bool empty(void) const;
    size_type size(void) const;
     // output
    // list: [1,2,3,4,5]
    // output: 1->2->3->4->5->NULL
    std::string toString(void) const;
     void insert(int position, const int& data);
    void erase(int position);
    void clear(void);
    list& sort(void);
};
int nullpointer = -1;
list::list(){
	_size = 0;
	head = -1;
	empty_head = 0;
}
list::list(const list& another){
	_size = another._size;
	head = another.head;
	empty_head = another.empty_head;
	int pos = head;
	while(pos!=-1){
		storage[pos].data = another.storage[pos].data;
		storage[pos].next = another.storage[pos].next;
		pos = storage[pos].next;
	}
}
list& list::operator=(const list& another){
	_size = another._size;
	head = another.head;
	empty_head = another.empty_head;
	int pos = head;
	while(pos!=-1){
		storage[pos].data = another.storage[pos].data;
		storage[pos].next = another.storage[pos].next;
		pos = storage[pos].next;
	}
	return *this;
}
list::~list(){

}
     // Capacity
bool list::empty(void) const{
	if(_size==0) return 1;
	else return 0;
}
list::size_type list::size(void) const{
	return _size;
}
std::string list::toString(void) const{
	std::string str;
	char arr[100];
	int pos = head, size = _size;
	while(pos!=-1&&size--){
		 sprintf(arr, "%d", storage[pos].data);
		 str += arr ;
		 str += "->";
		 pos = storage[pos].next;
	}
	str += "NULL";
	return str;
}
void list::insert(int position, const int& data){
	if(position<0||position>_size) return;
	int pos = head, col = empty_head, pre = head;
    storage[col].data = data;
    if(position==0){
   	 storage[col].next = head;
   	 head = col;
   }
   else {
   	int var = position;
   	while(--var){
		pos = storage[pos].next;
	}
	var = position;
	while(var--){
		pre = storage[pre].next;
	}
	if(position==_size) {
		storage[pos].next = col;
		storage[col].next = -1;
	}
	else {
		storage[pos].next = col;
		storage[col].next = pre;
	}
   }
   empty_head++;
	_size++;
	cout << toString() << endl;
}
void list::erase(int position){
	int pos = head, ptr = head;
	if(position<0||position>=_size) return;
	if(position==0) {
		head = storage[head].next;
		storage[pos].data = 0;
	}
	else{
		int var = position;
		while(position>-1){
		pos = storage[pos].next;
		position--;
	  }
	while(--var){
		ptr = storage[ptr].next;
	 }
	storage[ptr].next = pos;
   }
	_size--;
	empty_head++;
}
void list::clear(void){
	int pos = head, ptr = 0;
	while(pos!=-1){
		ptr = storage[pos].next;
	    storage[pos].data = 0;
		storage[pos].next = -1;
		pos = ptr;
	}
	head = -1;
	_size = 0;
	empty_head = 0;
}
list& list::sort(void){
	int num[1000], pos = head, i = 0, j = 0, len = 0;
	while(pos!=-1){
		num[i++] = storage[pos].data;
		pos = storage[pos].next;
	}
	len = i;
	for(i=0;i<len-1;i++){
		for(j=i+1;j<len;j++)
			if(num[i]>num[j]) {
				int temp = num[i];
				num[i] = num[j];
				num[j] = temp;
			}
	}
	i = 0;
	pos = head;
	while(pos!=-1){
		storage[pos].data = num[i++];
		pos = storage[pos].next;
	}
	return *this;
}
int main() {
    list li;
     int n;
    cin >> n;
     for (int i = 0, data, pos; i < n; i++) {
        cin >> pos >> data;
        li.insert(pos, data);
    }
     cout << li.toString() << " size: " << li.size() << endl;
     list li2(li);
    list li3;
     li = li3 = li2 = li;
     cout << li.toString() << " size: " << li.size() << endl;
    cout << li2.toString() << " size: " << li2.size() << endl;
    cout << li3.toString() << " size: " << li3.size() << endl;
     int m;
    cin >> m;
     for (int i = 0, pos; i < m; i++) {
        cin >> pos;
        li.erase(pos);
    }
     for (int i = 0, temp; i < m; i++) {
      cin >> temp;
      li.insert(0, temp);
    }
     cout << li.toString() << endl;
     cout << li.sort().toString() << endl;
    cout << li2.sort().toString() << endl;
    cout << li3.sort().toString() << endl;
     return 0;
}
