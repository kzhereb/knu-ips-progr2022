/*
 * pi13_20220429_binarysearchtree.cpp
 *
 *  Created on: Apr 29, 2022
 *      Author: KZ
 */

#include <iostream>
#include <cassert>

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

//	TreeNode* find_max_subtree() {
//		if (this->right) {
//			return this->right->find_max_subtree();
//		} else {
//			return this;
//		}
//	}

//	TreeNode*& search(int data) {
//		if (data == this->data) { return this;}
//		if (data < this->data) {
//			if (left) { return left->search(data);}
//			else {return nullptr; }
//		}
//		if (data > this->data) {
//			if (right) { return right->search(data);}
//			else {return nullptr; }
//		}
//	}

//	bool remove(int data) {
//		TreeNode*& to_delete = search(data);
//		if (!to_delete) {return false;}
//		if (to_delete->left) {
//			if (to_delete->right) { // left and right
//				TreeNode*& prev = to_delete->left->find_max_subtree();
//				to_delete->data = prev->data;
//				prev = prev->left;
//			} else { // only left
//				to_delete = to_delete->left;
//			}
//		} else {
//			if (to_delete->right) { // right only
//				to_delete = to_delete->right;
//			} else { // no children
//				to_delete = nullptr;
//			}
//		}
//	}

};

TreeNode*& find_max_subtree(TreeNode*& root) {
	if (root->right) {
		return find_max_subtree(root->right);
	} else {
		return root;
	}
}
// returns reference to found node, or reference to null node if not found
// null node should not be changed!
TreeNode*& search(TreeNode*& root, int data) {
	static TreeNode* null_node = nullptr;
	assert(!null_node);

	if (data == root->data) { return root;}
	if (data < root->data) {
		if (root->left) { return search(root->left, data);}
		else {return null_node; }
	}
	if (data > root->data) {
		if (root->right) { return search(root->left, data);}
		else {return null_node; }
	}
	assert(false); //unreachable
	return null_node;
}

bool remove(TreeNode*& root, int data) {
	TreeNode*& to_delete = search(root, data);
	if (!to_delete) {return false;}
	if (to_delete->left) {
		if (to_delete->right) { // left and right
			TreeNode*& prev = find_max_subtree(to_delete->left);
			to_delete->data = prev->data;
			prev = prev->left;
		} else { // only left
			to_delete = to_delete->left;
		}
	} else {
		if (to_delete->right) { // right only
			to_delete = to_delete->right;
		} else { // no children
			to_delete = nullptr;
		}
	}
	return true;
}



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

	bool remove(int data) {
		return pi13_20220429_binarysearchtree::remove(root, data);
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

	std::cout<<"Max data is "<<find_max_subtree(tree.root)->data<<std::endl;

	tree.add(1);
	tree.print_as_tree();
	std::cout<<"remove 2"<<std::endl;
	tree.remove(2);
	tree.print_as_tree();



	return 0;
}
}


