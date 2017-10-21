#include "BinaryTree.hpp"
void BinaryTree::MemoryDelete(node* p){
  if(p!=NULL) {
    if(p->left!=NULL) MemoryDelete(p->left);
    if(p->right!=NULL) MemoryDelete(p->right);
    delete p;
    p = NULL;
  }
}
void BinaryTree::BuildTree(const node* Source_Root, node* &Target_Root){
  if(Source_Root==NULL) Target_Root = NULL;
  else {
    if(Target_Root==NULL) Target_Root = new node(Source_Root->ele); 
    else Target_Root->ele = Source_Root->ele;
    BuildTree(Source_Root->left, Target_Root->left);
    BuildTree(Source_Root->right, Target_Root->right);
  }
}
void BinaryTree::BuildTree(const int* arr,int len, node* &root){
	root->ele = arr[0];
	int i=0;
	int tag = 0;
	if(len>1) {
	for(i=1;i<len;i++){
		tag = 0;
        node* p = root;
        while(p!=NULL) {
  	      if(p->ele==arr[i]) {
  	      	tag = 1;
  	        break;
  	 }
        	else if(p->ele>arr[i]) p = p->left;
  	        else p = p->right;
  }
  if(tag==0) {
  	    p = root;
        node *p1 = new node(arr[i]);
        while(p!=NULL) {
         if(p->ele>arr[i]) {
            if(p->left==NULL) {
               p->left=p1;
               break;}
         else p=p->left;
  }
         else {
          if(p->right==NULL) {
          p->right=p1;
          break;}
          else p=p->right;
    }
  }
}
}
}
}
void BinaryTree::preorder(const node* p){
  if(p!=NULL) {
    if(p->ele>0) cout << p->ele << " ";
    if(p->left!=NULL) preorder(p->left);
    if(p->right!=NULL) preorder(p->right);
  }
}
BinaryTree::BinaryTree(){
   root = NULL;
}
BinaryTree::BinaryTree(const BinaryTree& tree){
   root = NULL;
  BuildTree(tree.root, root);
}
BinaryTree::BinaryTree(const int* arr, int len){
  root = new node(0);
  BuildTree(arr, len, root);
}
void BinaryTree::ResetTree(const int* arr, int len){
  clear();
   root = new node(0);
  BuildTree(arr, len, root);
}
BinaryTree::~BinaryTree(){
  MemoryDelete(root);
  root = NULL;
}
void BinaryTree::clear(){
  MemoryDelete(root);
  root = NULL;
}
void BinaryTree::insert(int ele){
  if(root==NULL) root = new node(ele);
  else {
  	node* p =root;
  int tag = 0;
  while(p!=NULL) {
  	if(p->ele==ele) {
  		tag = 1;
  	     break;
  	 }
  	else if(p->ele>ele) p = p->left;
  	else p = p->right;
  }
  if(tag==0){
  	p = root;
  node *p1 = new node(ele);
  while(p!=NULL) {
  if(p->ele>ele) {
    if(p->left==NULL) {
       p->left=p1;
    break;}
      else p=p->left;
  }
  else {
    if(p->right==NULL) {
    p->right=p1;
    break;}
    else p=p->right;
    }
  }
}
  }
}
void BinaryTree::Delete(int ele){
  node** r = &root;
  node** p = NULL;
  int tag = 0;
  while((*r)!=NULL) {
  	if((*r)->ele==ele) {
  		tag = 1;
  		 p = r;
  	     break;
  	 }
  	else if((*r)->ele>ele) r = &(*r)->left;
  	else r = &(*r)->right;
  }//查找ele出现的节点p 
  node* p1 = *r;//若成功找到节点p，tag为1，继续以下操作 
  if(tag==1&&r!=NULL) {
  if((*p)->left==NULL) {
     *p = (*p)->right;
  }//若p左子树不存在，则用p的右孩子替代p 
  else {
    node** p2 = &(*r)->left;
    node* p3 = NULL;
    while((*p2)->right!=NULL) {
	   	p2 = &(*p2)->right;
    }
    p3 = *p2;
    *p2 = p3->left;
    p3->left = (*p)->left;
    p3->right = (*p)->right;
    (*p) = p3;
    p3 = NULL;
    p2 = NULL;
  }
}
   if(tag==1) {
   delete p1;
    p1 =NULL;
    r = p = NULL;
	}
}
void BinaryTree::print(){
  preorder(root);
  cout << "\n";
}