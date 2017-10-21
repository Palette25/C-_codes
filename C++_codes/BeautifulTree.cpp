#include "BeautifulTree.hpp"
#include <list>
#include <cstring>
using namespace HFM;
node* getnode(list<node*> &store, int index) {
	list<node*>::iterator iter = store.begin();
	while (index--) {
		iter++;
	}
	node* result = *iter;
	return result;
}
void sort(list<node*> &store) {
	for (int i = 0; i < store.size(); i++) {
		for (int j = i; j < store.size();j++)
			if (getnode(store, i)->weight > getnode(store, j)->weight) {
				node temp = *getnode(store, i);
				*getnode(store, i) = *getnode(store, j);
				*getnode(store, j) = temp;
			}
	}
}
node* BuildTree(vector<pair<int, int> > &vec){
	node* left=NULL, *right=NULL, *parent=NULL;
	list<node*> store;
	for(int i=0;i<vec.size();i++){
		node* new_node = new node(vec[i].first, '0', "", vec[i].second);
		store.push_back(new_node);
	}
	for(int i=0;i<vec.size()-1;i++){
		if(store.size()>1){
		left = store.front();
		store.pop_front();
		right = store.front();
		store.pop_front();
		parent = new node(left->weight+right->weight, '0', "", 0, left, right, NULL);
		left->parent = parent;
		right->parent = parent;
		store.push_back(parent);
		sort(store);
	    }
	}
	return store.front();
}
node* BuildTree(vector<pair<char, int>> &vec){
	node* left = NULL, *right = NULL, *parent = NULL;
	list<node*> store;
	for(int i=0;i<vec.size();i++){
		node* new_node = new node(vec[i].second, vec[i].first);
store.push_back(new_node);
	}
	for (int i = 0; i < vec.size() - 1; i++) {
		if (store.size() > 1) {
			left = store.front();
			store.pop_front();
			right = store.front();
			store.pop_front();
			parent = new node(left->weight + right->weight, '0', "", 0, left, right, NULL);
			left->parent = parent;
			right->parent = parent;
			store.push_back(parent);
			sort(store);
		}
	}
	return store.front();
}

HuffmanCode::HuffmanCode(int weight[], int num) {
	for (int i = 0; i < num; i++) {
		for (int j = i; j < num; j++)
			if (weight[i] > weight[j]) {
				int temp = weight[i];
				weight[i] = weight[j];
				weight[j] = temp;
			}
	}
	count = num;
	for (int i = 0; i < num; i++) {
		weight_[i] = weight[i];
		arr_vec.push_back(make_pair(weight[i], i + 1));
	}
	root = BuildTree(arr_vec);
	text = "";

}

HuffmanCode::HuffmanCode(const string &str) {
	count = str.size();
	memset(weight_, 0, 100);
	for (int i = 0; i < str.size(); i++) {
		if (str[i] != ' ') text += str[i];
	}
	int tag[200] = { 0 };
	for (int i = 0; i < str.size(); i++) {
		tag[str[i]]++;
	}
	for (int i = 0; i <= 200; i++) {
		if (tag[i] > 0) str_vec.push_back(make_pair(i, tag[i]));
	}
	for (int i = 0; i < str_vec.size(); i++) {
		for (int j = i; j < str_vec.size(); j++) {
			if (str_vec[i].second > str_vec[j].second || str_vec[i].second == str_vec[j].second&&
				str_vec[i].first > str_vec[j].first) {
				pair<char, int> temp = str_vec[i];
				str_vec[i] = str_vec[j];
				str_vec[j] = temp;
			}
		}
	}
	root = BuildTree(str_vec);
}
void CodeAllNode(node* root) {
	if (root->left != NULL) {
		root->left->code = root->code;
		root->left->code += '1';
		CodeAllNode(root->left);
	}

	if (root->right != NULL) {
		root->right->code = root->code;
		root->right->code += '0';
		CodeAllNode(root->right);
	}

}
void GetNode(string arr[], node* root) {
	if (root->left != NULL) GetNode(arr, root->left);
	if (root->right != NULL) GetNode(arr, root->right);
	arr[root->flag] = root->code;
}
void GetNode_ch(string arr[], node* root) {
	if (root->left != NULL) GetNode_ch(arr, root->left);
	if (root->right != NULL) GetNode_ch(arr, root->right);
	arr[root->ch] = root->code;
}
void HuffmanCode::DisplayCode() {
	string Code[200];
	int length = 0;
	CodeAllNode(root);
	if (text == "") {
		GetNode(Code, root);
		for (int i = 0; i < 200; i++) {
			for (int j = i; j < 200; j++) {
				int k1 = 0, k2 = 0;
				for (int t = 0; t < arr_vec.size(); t++) {
					if (arr_vec[t].second == i) k1 = arr_vec[t].first;
					if (arr_vec[t].second == j) k2 = arr_vec[t].first;
				}
				if (Code[i] < Code[j] && Code[i].size() == Code[j].size() && Code[i] != ""&&Code[j] != ""&&k1==k2) {
					string temp = Code[i];
					Code[i] = Code[j];
					Code[j] = temp;
				}
				else if (Code[i] != ""&&Code[j] != ""&&Code[i].size() < Code[j].size()&&k1==k2) {
					string temp = Code[i];
					Code[i] = Code[j];
					Code[j] = temp;
				}
			}
		}
		for(int i=0;i<count;i++){
			cout << "Weight = " << arr_vec[i].first << "; Code = " << Code[i+1] << endl;
			length += arr_vec[i].first * Code[i+1].size();
		}
		cout << "Huffman's codeLength = " << length << endl;
	}
	else {
		GetNode_ch(Code, root);
		for (int i = 0; i < 200; i++) {
			for (int j = i; j < 200; j++) {
				int k1 = 0, k2 = 0;
				for (int t = 0; t < str_vec.size(); t++) {
					if (str_vec[t].first == i) k1 = str_vec[t].second;
					if (str_vec[t].first == j) k2 = str_vec[t].second;
				}
				if (Code[i] < Code[j] && Code[i].size() == Code[j].size() && Code[i] != ""&&Code[j] != ""&&k1==k2) {
					string temp = Code[i];
					Code[i] = Code[j];
					Code[j] = temp;
				}
				else if (Code[i] != ""&&Code[j] != ""&&Code[i].size() < Code[j].size() && k1 == k2) {
					string temp = Code[i];
					Code[i] = Code[j];
					Code[j] = temp;
				}
			}
		}
	    for(int i=0;i<str_vec.size();i++){
	    	cout << "(" << str_vec[i].first << ") Weight = " << str_vec[i].second
	    	     <<  "; Code = " << Code[str_vec[i].first] << endl;
	    	length += str_vec[i].second * Code[str_vec[i].first].size();
	    }
	    cout << "Huffman's codeLength = " << length << endl;
	    cout << "Origin Text: " << text << endl;
	    cout << "Huffman's Code: ";
	    for(int i=0;i<text.size();i++)
	    	cout << Code[text[i]];
	    cout << endl;
	}
}