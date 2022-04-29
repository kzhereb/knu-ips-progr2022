/*
 * pi13_20220429_binarysearchtree.cpp
 *
 *  Created on: Apr 29, 2022
 *      Author: KZ
 */

#include <iostream>

namespace pi13_20220429_binarysearchtree {

struct TreeNode {
	int data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int data, TreeNode* left=nullptr, TreeNode* right=nullptr) {
		this->data = data;
		this->left = left;
		this->right = right;
	}



};

void add_recursive(TreeNode*& root, int data) {
	if (!root) {
		root = new TreeNode(data);
	} else if (data < root->data) {
		add_recursive(root->left, data);
	} else { // data >= root->data
		add_recursive(root->right, data);
	}
}

void print_as_tree_recursive(TreeNode* node, int indent_level = 0) {
	for(int i=0; i<indent_level; i++) {std::cout<<"  ";}
	if (!node) { std::cout<<"_"<<std::endl;}
	else {
		std::cout<<node->data<<std::endl;
		print_as_tree_recursive(node->left, indent_level+1);
		print_as_tree_recursive(node->right, indent_level+1);
	}

}

struct SearchTree {
	TreeNode* root;

	SearchTree() { root = nullptr;}

	void add(int data) {
		add_recursive(root, data);
	}

	void print_as_tree() {
		print_as_tree_recursive(root);
	}
};



int main() {
	SearchTree tree;

	tree.add(7);
	tree.add(2);
	tree.add(5);
	tree.add(11);

	tree.print_as_tree();


	return 0;
}
}


