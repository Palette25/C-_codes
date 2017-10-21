#ifndef BEAUTIFULTREE_H
#define BEAUTIFULTREE_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;
struct node{
	char ch;
	int weight;
	int flag;
	node* left;
	node* right;
	node* parent;
	string code;
	node(int val, char ch_='\0', string code_="", int flag_ = 0, node* left_=NULL, node* right_=NULL, node* parent_=NULL){
		weight = val;
		ch = ch_;
		code = code_;
		flag = flag_;
		left = left_;
		right = right_;
		parent = parent_;
	}
	bool operator<(node oth) {
		if (weight<oth.weight) return 1;
		else return 0;
	}
};


namespace HFM{
class HuffmanCode{
public:
	HuffmanCode(int weight[], int num);
	HuffmanCode(const string &str);
	~HuffmanCode(){
		MemoryDelete1(root);
	}
	void MemoryDelete1(node* p) {
		if (p != NULL) {
			if (p->left != NULL) MemoryDelete1(p->left);
			if (p->right != NULL) MemoryDelete1(p->right);
			delete p;
			p = NULL;
		}
	}
	void DisplayCode();
private:
	node* root;
	string text;
	vector<pair<char, int> > str_vec;
	vector<pair<int, int>> arr_vec;
	int weight_[100];
	int count;
};

}
#endif