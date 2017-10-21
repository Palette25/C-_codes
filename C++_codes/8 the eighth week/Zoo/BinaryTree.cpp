#include "BinaryTree.hpp"
using namespace std;
void MemoryDelete(BinaryTree::Node* p) {
	if (p != NULL) {
		if (p->left != NULL) MemoryDelete(p->left);
		if (p->right != NULL) MemoryDelete(p->right);
		delete p;
		p = NULL;
	}
}
void BuildTree(const BinaryTree::Node* Source_Root, BinaryTree::Node* &Target_Root) {
	if (Source_Root == NULL) Target_Root = NULL;
	else {
		if (Target_Root == NULL) Target_Root = new BinaryTree::Node(Source_Root->val);
		else Target_Root->val = Source_Root->val;
		BuildTree(Source_Root->left, Target_Root->left);
		BuildTree(Source_Root->right, Target_Root->right);
	}
}
void insert(BinaryTree::Node* root, char a) {
	std::queue<BinaryTree::Node*> visited, unvisited;
	BinaryTree::Node* current = root;
	unvisited.push(root);
	while (!unvisited.empty()) {
		current = (unvisited.front());
		if (current->val == '#') {
			unvisited.pop();
			continue;
		}
		if (current->left != NULL)
			unvisited.push(current->left);
		else break;
		if (current->right != NULL)
			unvisited.push(current->right);
		else break;
		visited.push(current);
		unvisited.pop();
	}
	if (current->left == NULL) current->left = new BinaryTree::Node(a);
	else if(current->right==NULL) current->right = new BinaryTree::Node(a);
}
BinaryTree::Node* buildTree(std::vector<char>& preOrder, std::vector<char>& inOrder) {
	if (preOrder.size() == 0) return NULL;
 	BinaryTree::Node* root = new BinaryTree::Node(preOrder[0]);
	int len1 = inOrder.size();
	int len2 = preOrder.size();
	int loc = 0;
	if (len1 >= 1) {
		while (preOrder[0] != inOrder[loc] && loc < len1) {
			loc++;
		}
	}
	vector<char> inOrder_left, inOrder_right, preOrder_left, preOrder_right;
		for (int i = 0; i < loc; i++) {
			inOrder_left.push_back(inOrder[i]);
			preOrder_left.push_back(preOrder[i + 1]);
		}
	for (int i = loc+1; i < len1; i++)
			inOrder_right.push_back(inOrder[i]);
	for (int i = loc + 1; i < len2; i++)
		   preOrder_right.push_back(preOrder[i]);
	root->left = buildTree(preOrder_left, inOrder_left);
	root->right = buildTree(preOrder_right, inOrder_right);
	return root;
}
BinaryTree::BinaryTree(const BinaryTree& tree) {
	root = NULL;
	BuildTree(tree.root, root);
}
BinaryTree::BinaryTree(std::vector<char>& tree) {
	if (tree.size() == 0) root = NULL;
	else {
		root = new Node(tree[0]);
		for (int i = 1; i < tree.size(); i++)
			insert(root, tree[i]);
	}
}
BinaryTree::BinaryTree(const std::vector<char>& preOrder, const std::vector<char>& inOrder) {
	std::vector<char> preorder = preOrder;
	std::vector<char> inorder = inOrder;
	if (preOrder.size() == 0) root = NULL;
	else {
		root = buildTree(preorder, inorder);
	}
}
BinaryTree::~BinaryTree() {
	clear();
}
BinaryTree& BinaryTree::operator=(const BinaryTree& tree) {
	if (tree.root == root) return *this;
	else {
		if(root!=NULL) clear();
		BuildTree(tree.root, root);
		return *this;
	}
}
BinaryTree::Node* BinaryTree::getRoot() const {
	return root;
}
void BinaryTree::clear() {
	MemoryDelete(root);
	root = NULL;
}
void BinaryTree::preOrder(void(*visite)(BinaryTree::Node*), Node* n1) {
	if (n1 == NULL||n1->val=='#') return;
	visite(n1);
	if (n1->left != NULL) preOrder(visite, n1->left);
	if (n1->right != NULL) preOrder(visite, n1->right);
}
void BinaryTree::inOrder(void(*visite)(BinaryTree::Node*), Node* n1) {
	if (n1 == NULL || n1->val == '#') return;
	if (n1->left != NULL) inOrder(visite, n1->left);
	visite(n1);
	if (n1->right != NULL) inOrder(visite, n1->right);
}
void BinaryTree::postOrder(void(*visite)(BinaryTree::Node*), Node* n1) {
	if (n1 == NULL || n1->val == '#') return;
	if (n1->left != NULL) postOrder(visite, n1->left);
	if (n1->right != NULL) postOrder(visite, n1->right);
	visite(n1);
}
