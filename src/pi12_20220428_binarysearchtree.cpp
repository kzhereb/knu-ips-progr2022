/*
 * pi12_20220428_binarysearchtree.cpp
 *
 *  Created on: Apr 28, 2022
 *      Author: KZ
 */

#include <iostream>
#include <cassert>

namespace pi12_20220428_binarysearchtree {

struct TreeNode {
	int data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int data, TreeNode* left=nullptr, TreeNode* right=nullptr) {
		this->data = data;
		this->left = left;
		this->right = right;
	}

	void print_as_tree() {
		std::cout<<data<<"(";
		if (left) {
			left->print_as_tree();
		}
		std::cout<<",";
		if (right) {
			right->print_as_tree();
		}
		std::cout<<")";
	}
};

struct BinarySearchTree {
	TreeNode* root;

	BinarySearchTree() { root = nullptr;}

	void add(int data) {
		root = add_recursive(data, root);
	}

	TreeNode* add_recursive(int data, TreeNode* current) {
		if (!current) {
			current = new TreeNode(data);
			return current;
		}
		if (current->data < data) {
			current->right = add_recursive(data, current->right);

		} else if (current->data >= data) {
			current->left = add_recursive(data, current->left);

		}
		return current;
	}

	TreeNode* search(int data) { //return nullptr if not found
		return search_recursive(data, root);

	}

	TreeNode* search_recursive(int data, TreeNode* current) {
		if (!current) {return nullptr;}
		if (current->data == data) {return current;}
		if (current->data < data) {return search_recursive(data, current->right);}
		if (current->data > data) {return search_recursive(data, current->left);}
		assert(false); //should not reach this
		return nullptr;
	}


	void print_as_tree() {
		if(!root) {
			std::cout<<"empty tree"<<std::endl;
		}
		root->print_as_tree();
		std::cout<<std::endl;
	}
};



int main() {
	BinarySearchTree bst;
	bst.add(5);
	bst.add(1);
	bst.add(7);

	bst.print_as_tree();

	if (bst.search(7)) { std::cout<<"7 found"<<std::endl;}
	else { std::cout<<"7 not found"<<std::endl;}

	if (bst.search(3)) { std::cout<<"3 found"<<std::endl;}
	else { std::cout<<"3 not found"<<std::endl;}


	return 0;
}
}


