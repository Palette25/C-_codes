#include <string>
#include <iostream>
 
using std::cin;
using std::cout;
using std::endl;
using std::string;
 
typedef struct node {
  int data;
  struct node* next;
  node(int data = 0, struct node* next = NULL) : data(data), next(next) {}
} node;
 
class list {
 private:
  node* head;
  int _size;
 
 public:
  list();
  list(const list&);
  list& operator=(const list&);
  ~list();
 
  // Capacity
  bool empty(void) const;
  int size(void) const;
 
 public:
  // output
  // list: [1,2,3,4,5]
  // output: 1->2->3->4->5->NULL
  std::string toString(void) const;
 
  void insert(int position, const int& data);
  void erase(int position);
  void clear(void) {
    if (this->head != NULL) {
      node* p = this->head;
      while (p != NULL) {
        node* temp = p;
        p = p->next;
        delete temp;
      }
      this->head = NULL;
    }
    this->_size = 0;
  }
  list& sort(void);
};

list::list(){
	head = NULL;
	_size = 0;
}
list::list(const list& new_list){
	int i = 0;
	head = new node(new_list.head->data);
	_size = new_list._size; 
	if(_size>1){
	node* ptr = new_list.head->next;
	node* temp = NULL, *var = head;
	for(i=0;i<_size-1;i++){
		temp = new node(ptr->data);
		var->next = temp;
		 var = var->next;
		 if(i!=_size-1) ptr = ptr->next;
		 else ptr = NULL;
	 }
	temp -> next = NULL;
     }
     else if(_size==1) {
     	head->next = NULL;
     }
}
list& list::operator=(const list& new_list){
	_size = new_list._size;
	node* ptr = head, *temp = new_list.head;
	if(head!=NULL) {
		while(temp!=NULL){
			ptr->data = temp->data;
			ptr = ptr->next;
			temp = temp->next;
		}
	}
	else if(head==NULL) {
		head = new node(temp->data);
		node* po = head;
		temp = temp->next;
		while(temp!=NULL) {
			ptr = new node(temp->data);
			po->next = ptr;
			po = po->next;
			temp = temp->next;
		}
	}
	return *this;
}
list::~list(){
	if(head!=NULL){
		node* ptr = head;
		while(head!=NULL){
			ptr = head;
			head = head->next;
			delete ptr;
		}
	}
	head = NULL;
}
bool list::empty(void) const{
	if(_size==0) return 1;
	else return 0;
}
int list::size(void) const{
	return _size;
}
std::string list::toString(void) const{
	node* ptr = head;
	std::string str1;
	char str[5000];
	for(int i=0;i<_size;i++)
	  ptr = ptr->next;
	  ptr = NULL;
	int k = 0;
	ptr = head;
	for(int i=0;i<=_size;i++){
		if(ptr!=NULL) {
			if(ptr->data<10) str[k++] = ptr->data + '0';
			if(ptr->data>=10&&ptr->data<100) {
				str[k++] = ptr->data/10 + '0';
				str[k++] = ptr->data%10 + '0';
			}
			if(ptr->data>=100&&ptr->data<1000) {
				str[k++] = ptr->data/100 + '0';
				int num = ptr->data - (str[k-1]-'0')*100;
				str[k++] = num/10 + '0';
				str[k++] = num%10 + '0';
			}
			else {
				str[k++] = ptr->data/1000 + '0';
				int num = ptr->data - (str[k-1]-'0')*1000;
				str[k++] = num/100 + '0';
				num = num - (str[k-1]-'0')*100;
				str[k++] = num/10 + '0';
				str[k++] = num%10 + '0';
			}
			str[k++] = '-';
			str[k++] = '>';
			ptr = ptr->next;
		}
		else {
			str[k++] = 'N';
			str[k++] = 'U';
			str[k++] = 'L';
			str[k++] = 'L';
		}
	}
	str[k] = '\0';
	str1 = str;
	return str1;
}
 
void list::insert(int position, const int& data){
	if(position>=0&&position<=_size)
   {
	node* ptr = NULL, *ptr1 = head, *ptr2 = head;
	ptr = new node(data);
	for(int i=0;i<position-1;i++)
		ptr1 = ptr1->next;
	for(int i=0;i<position;i++)
		ptr2 = ptr2->next;
	if(position!=0&&position!=_size){
		ptr1->next = ptr;
	    ptr->next = ptr2;
	}
	else if(position==0) {
		ptr->next = head;
		head = ptr;
	}
	else if(position==_size){
		ptr1->next = ptr;
		ptr->next = NULL;
	}
	_size++;
}
}
void list::erase(int position){
	if(position==0) {
		node* ptr = head->next;
		delete head;
		head = ptr;
		_size--;
	}
	else if(position<_size){
		node* ptr = head->next, *ptr1 = head;
		for(int i=0;i<position-1;i++){
			ptr = ptr->next;
			ptr1 = ptr1->next;
}
		ptr1->next = ptr->next;
		delete ptr;
		ptr = NULL;
		_size--;
	}
}
list& list::sort(void){
	node* ptr = head, *temp = NULL;
	while(ptr->next!=NULL){
		temp = ptr->next;
		while(temp!=NULL){
			if(ptr->data>temp->data) {
				int var = ptr->data;
				ptr->data = temp->data;
				temp->data = var;
			}
			temp = temp->next;
		}
		ptr = ptr -> next;
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
 
  cout << li.toString() << endl;
 
  cout << li.sort().toString() << endl;
  cout << li2.sort().toString() << endl;
  cout << li3.sort().toString() << endl;
 
  return 0;
}
 
