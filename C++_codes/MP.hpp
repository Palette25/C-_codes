#ifndef MP_HPP
#define MP_HPP
#include <iostream>
namespace MP {
struct TreeNode{
 	int val;
 	int id;
 	TreeNode* left;
 	TreeNode* right;
 	TreeNode(int x, int i){
 		val = x;
 		id = i;
		left = NULL;
		right = NULL;
 	}
 };
class MaxPath {
private:
    int max;
public:
    MaxPath() : max(0) {}
    int findMaxPath(TreeNode *root);
};
}

#endif