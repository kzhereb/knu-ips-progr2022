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

};

TreeNode*& find_max_subtree(TreeNode*& root) {
	if (root->right) {
		return find_max_subtree(root->right);
	} else {
		return root;
	}
}

TreeNode*& find_min_subtree(TreeNode*& root) {
	if (root->left) {
		return find_min_subtree(root->left);
	} else {
		return root;
	}
}

TreeNode* copy(TreeNode* other) {
	if (!other) { return nullptr;}
	return new TreeNode(other->data, copy(other->left), copy(other->right));
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

void print_in_order_removing_recursive(TreeNode* root) {
	if (!root) {std::cout<<std::endl; return;}
	int min = find_min_subtree(root)->data;
	std::cout<<min<<" ";
	remove(root, min);
	print_in_order_removing_recursive(root);
}
// code by Anastasiia Rudenko
void sym_print(TreeNode* root) {
    if (!root) { return; }
    sym_print(root->left);
    std::cout << root->data << " ";
    sym_print(root->right);
}

struct SearchTree {
	TreeNode* root;

	SearchTree() { root = nullptr;}

	SearchTree(const SearchTree& other) {
		root = copy(other.root);
	}

	void add(int data) {
		add_recursive(root, data);
	}

	bool remove(int data) {
		return pi13_20220429_binarysearchtree::remove(root, data);
	}

	void print_as_tree() {
		print_as_tree_recursive(root);
	}

	void print_in_order_removing() {
		print_in_order_removing_recursive(copy(root));
	}

	void print_in_order_symmetric() {
		sym_print(root);
		std::cout << std::endl;
	}

	void print_all() {
		print_as_tree();
		print_in_order_removing();
		print_in_order_symmetric();
	}

};



int main() {
	SearchTree tree;

	tree.add(7);
	tree.add(2);
	tree.add(5);
	tree.add(11);

	tree.print_all();

	std::cout<<"Max data is "<<find_max_subtree(tree.root)->data<<std::endl;
	std::cout<<"Min data is "<<find_min_subtree(tree.root)->data<<std::endl;

	tree.add(1);
	tree.print_all();

	std::cout<<"remove 2"<<std::endl;
	tree.remove(2);
	tree.print_all();

	SearchTree copy = tree;
	copy.add(123);
	copy.remove(7);
	std::cout<<"copy"<<std::endl;
	copy.print_all();
	std::cout<<"original"<<std::endl;
	tree.print_all();



	return 0;
}
}


