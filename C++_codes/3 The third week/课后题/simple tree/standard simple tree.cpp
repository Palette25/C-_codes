#include "BinaryTree.hpp"

void BinaryTree::preorder(const node* p) {
  if (p == NULL) return;
  cout << p->ele << ' ';
  preorder(p->left);
  preorder(p->right);
}


void BinaryTree::ResetTree(const int* arr, int len) {
  clear();
  BuildTree(arr, len, root);
}

void BinaryTree::print() {
  preorder(root);
  cout << endl;
}

BinaryTree::BinaryTree() {
  root = NULL;
}

void BinaryTree::insert(int ele) {
  node* p = root;
  if (p == NULL) {
    root = new node(ele);
    return;
  }
  while (p->ele != ele) {
    if (ele > p->ele) {
      if (p->right) {
        p = p->right;
      } else {
        p->right = new node(ele);
        break;
      }
    } else {
      if (p->left) {
        p = p->left;
      } else {
        p->left = new node(ele);
        break;
      }
    }
  }
}

void BinaryTree::Delete(int ele) {
  node* p = root, *q = NULL;
  bool flag = true; // if flag == true, p is the left child of q.
  while (p && p->ele != ele) {
    q = p;
    if (ele > p->ele) {
      p = p->right;
      flag = false;
    } else {
      p = p->left;
      flag = true;
    }
  }
  if (p) {
    if (p->left == NULL) {
      if (q == NULL) root = p->right;
      else if (flag) q->left = p->right;
      else q->right = p->right;
    } else {
      node* tmp = p->left;
      node* tmp_par = p;
      while (tmp->right) {
        tmp_par = tmp;
        tmp = tmp->right;
      }
      tmp->right = p->right;
      tmp_par->right = tmp->left;
         if (p->left!= tmp)
         tmp->left = p->left;
      if (q == NULL) root = tmp;
      else if (flag) q->left = tmp;
      else q->right = tmp;
    }
    delete p;
  }
}
BinaryTree::BinaryTree(const BinaryTree& oth) {
  BuildTree(oth.root, this->root);
}
BinaryTree::~BinaryTree() {
  clear();
}
void BinaryTree::clear() {
  MemoryDelete(root);
  root = NULL;
}
void BinaryTree::MemoryDelete(node* t) {
  if (t == NULL) return;
  MemoryDelete(t->left);
  MemoryDelete(t->right);
  delete t;
}
BinaryTree::BinaryTree(const int* arr, int len) {
  BuildTree(arr, len, root);
}
void BinaryTree::BuildTree(const node* Source_Root, node* &Target_Root) {
  if (Source_Root == NULL) {
    Target_Root = NULL;
    return;
  }
  Target_Root = new node(Source_Root->ele);
  BuildTree(Source_Root->left, Target_Root->left);
  BuildTree(Source_Root->right, Target_Root->right);
}

void BinaryTree::BuildTree(const int* arr, int len, node* &root) {
  int index = 0;
  root = NULL;
  while (len--) {
    if (root == NULL) {
      root = new node(arr[index++]);
      continue;
    }
    node* p = root;
     int tmp = arr[index++];
    while (p->ele != tmp) {
      if (tmp > p->ele) {
        if (p->right) {
          p = p->right;
        } else {
          p->right = new node(tmp);
          break;
        }
      } else {
        if (p->left) {
          p = p->left;
        } else {
          p->left = new node(tmp);
          break;
        }
      }
    }
  }
}
