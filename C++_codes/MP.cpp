#include "MP.hpp"
#include <iostream>
using namespace MP;
int MaxPath::findMaxPath(TreeNode* root){
	int result1 = root->val + root->left->val;
	int result2 = root->val + root->right->val;
	TreeNode* ptr = root->left;
	while(ptr!=NULL){
		if (ptr->left != NULL) {
			if (ptr->right != NULL) {
				if (ptr->left->val>ptr->right->val) {
					result1 += ptr->left->val;
					ptr = ptr->left;
					continue;
				}
				else {
					result1 += ptr->right->val;
					ptr = ptr->right;
					continue;
				}
			}
			else {
				result1 += ptr->left->val;
				ptr = ptr->left;
				continue;
			}
		}
		else if (ptr->left == NULL) {
			if (ptr->right == NULL) break;
			else {
				result1 += ptr->right->val;
				ptr = ptr->right;
			}
		}
	 }
	ptr = root->right;
	while (ptr != NULL) {
		if (ptr->left != NULL) {
			if (ptr->right != NULL) {
				if (ptr->left->val>ptr->right->val) {
					result2 += ptr->left->val;
					ptr = ptr->left;
					continue;
				}
				else {
					result2 += ptr->right->val;
					ptr = ptr->right;
					continue;
				}
			}
			else {
				result2 += ptr->left->val;
				ptr = ptr->left;
				continue;
			}
		}
		else if (ptr->left == NULL) {
			if (ptr->right == NULL) break;
			else {
				result2 += ptr->right->val;
				ptr = ptr->right;
			}
		}
	}
	int result = result1 > result2 ? result1 : result2;
    return result;
}