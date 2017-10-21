#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <queue>
using namespace std;

template<typename type>
class Stack {
  public:
    Stack(){
    	count = 0;
    }
    void push(const type& data){
    	q1.push(data);
    	count++;
    }
    type pop(){
    	type top_temp;
    	if(!empty()){
    	int len1 = q1.size();
    	for(int i=0;i<len1-1;i++){
    		q2.push(q1.front());
    		q1.pop();
    	}
    	top_temp = q1.front();
    	q1.pop();
    	int len2 = q2.size();
    	for(int i=0;i<len2;i++){
    		q1.push(q2.front());
    		q2.pop();
    	}
    	count--;
       }
    	return top_temp;
    }
    type top(){
    	return q1.back();
    }
    int size() const{
    	return count;
    }
    bool empty(){
    	if(count==0) return 1;
    	else return 0;
    }
  private:
    queue<type> q1;
    queue<type> q2;
    int count; // the number of elements.
};

template<typename type>
void print(Stack<type>& stack){
	Stack<type> stack1 = stack;
	while(!stack1.empty()){
		cout << stack1.top() << " ";
		stack1.pop();
	}
	cout << endl;
}
#endif