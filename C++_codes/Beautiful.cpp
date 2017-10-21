#include "BeautifulTree.hpp"
#include <queue>
node* BuildTree(int num, int weight[]){
	node* left=NULL, *right=NULL, *parent=NULL;
	list<node*> store;
	for(int i=0;i<num;i++){
		node* new_node = new node(weight[i]);
		store.push(new_node);
	}
	for(int i=0;i<num-1;i++){
		if(store.size()>1){
		left = store.top();
		store.pop();
		right = store.top();
		store.pop();
		parent = new node(left->weight+right->weight, '0', "", left, right, NULL);
		left->parent = parent;
		right->parent = parent;
		store.push(parent);
		store.sort();
	    }
	}
	return store.front();
}

node* BuildTree(vector<pair<char, int>> vec, int tag[]){
	node* left = NULL, *right = NULL, *parent = NULL;
	list<node*> store;
	for(int i=0;i<vec.size();i++){
		node* new_node = new node(tag[i], vec[i].first);
		store.push(new_node);
	}
	for(int i=0;i<vec.size()-1;i++){
		if(store.size()>1){
		left = store.top();
		store.pop();
		right = store.top();
		store.pop();
		parent = new node(left->weight+right->weight, '0', "", left, right, NULL);
		left->parent = parent;
		right->parent = parent;
		store.push(parent);
	}
	}
	return store.front();
}
HuffmanCode::HuffmanCode(int weight[], int num){
	for(int i=0;i<num;i++){
		for(int j=i;j<num;j++)
			if(weight[i]>weight[j]){
				int temp = weight[i];
				weight[i] = weight[j];
				weight[j] = temp; 
			}
	}
	count = num;
	for(int i=0;i<num;i++)
		weight_[i] = weight[i];
	root = BuildTree(num, weight);
	text = "";
}

HuffmanCode::HuffmanCode(const string &str){
	for(int i=0;i<str.size();i++){
		if(str[i]!=' ') text += str[i];
	}
	int tag[200] = {0};
	for(int i=0;i<str.size();i++){
		tag[str[i]]++;
	}
	for(char i='a';i<='z';i++){
		if(tag[i]>0) str_vec.push_back(make_pair(i, tag[i]));
	}
	for(int i=0;i<str_vec.size();i++){
		for(int j=i;j<str_vec.size();i++){
			if(str_vec[i].second>str_vec[j].second||str_vec[i].second==str_vec[j].second&&
				     str_vec.first>str_vec[j].first){
				pair<char, int> temp = str_vec[i];
				str_vec[i] = str_vec[j];
				str_vec[j] = temp;
			}
		}
	}
	root = BuildTree(str_vec, tag);
}
void CodeAllNode(node* root){
	if(root->left!=NULL) {
		root->left->code = root->code;
		root->left->code += '1';
		CodeAllNode(root->left);
	}

	if(root->right!=NULL) {
		root->left->code = root->code;
		root->left->code += '0';
		CodeAllNode(root->right);
	}
	
}
void GetNode(string arr[], node* root){
	if(root->left!=NULL) GetNode(arr, root->left);
	if(root->right!=NULL) GetNode(arr, root->right);
	arr[root->weight] = root->code;
}
void HuffmanCode::DisplayCode(){
	string Code[200];
	int length = 0;
	CodeAllNode(root);
	GetNode(Code, root);
	if(text==""){
		for(int i=0;i<count;i++){
			cout << "Weight = " << weight_[i] << "; Code = " << Code[weight_[i]] << endl;
			length += weight_[i]*Code[weight_[i]].size();
		}
		cout << "Huffman's codeLength = " << length << endl;
	}
	else {
	    for(int i=0;i<str_vec.size();i++){
	    	cout << "(" << str_vec[i].first << ") Weight = " << str_vec[i].second 
	    	     <<  "; Code = " << Code[str_vec[i].second] << endl;
	    	length += str_vec[i].second*Code[str_vec[i].second];
	    }
	    for(int i=0;i<count;i++){
	    	Code[str_vec[i].first] = Code[str_vec[i].second];
	    }
	    cout << "Huffman's codeLength = " << length << endl;
	    cout << "Origin Text: " << text << endl;
	    cout << "Huffman's Code: ";
	    for(int i=0;i<text.size();i++)
	    	cout << Code[text[i]];
	    cout << endl;
	}
}