#include <iostream>
#include <stdexcept>
#include <memory>
using namespace std;

class base{
public:
	base(string name_):name(name_){
		cout << "Constructing object....." << endl;
	}
	~base(){
		cout << "Destructing object " << name << endl;
	}
	string b_name()const{
		return name;
	}
private:
	string name;
};

void fun(){
	auto_ptr<base> ptr(new base("clown"));
	cout << "Now Constructing an auto_ptr, who points to an object named " 
	     << ptr->b_name() << endl;
    auto_ptr<base> pre(ptr);
    cout << "Now we copy ptr to pre....." << endl;
	throw 0;
}
int main(){
	try{
		fun(); 
	}
	catch(int){
		cout << "Catching an error........" << endl;
	}
	cout << "End of Main" << endl;
}
