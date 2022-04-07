/*
 * pi12_20220407_tree_reverse.cpp
 *
 *  Created on: Apr 7, 2022
 *      Author: KZ
 */

#include <iostream>


namespace pi12_20220407_tree_reverse {

struct TreeNodeReversed {
	int data;
	TreeNodeReversed* parent;
	TreeNodeReversed(int data, TreeNodeReversed* parent = nullptr) {
		this->data = data;
		this->parent = parent;
	}
};

struct TreeReversed {
	TreeNodeReversed** leaf_nodes;
	std::size_t size;
	TreeReversed() { //1(2, 3(5, 6), 4(7)) - example from lecture slides
		size = 4;
		leaf_nodes = new TreeNodeReversed*[size];

		leaf_nodes[0] = new TreeNodeReversed(2);
		leaf_nodes[1] = new TreeNodeReversed(5);
		leaf_nodes[2] = new TreeNodeReversed(6);
		leaf_nodes[3] = new TreeNodeReversed(7);

		leaf_nodes[0]->parent = new TreeNodeReversed(1);
		leaf_nodes[1]->parent = new TreeNodeReversed(3, leaf_nodes[0]->parent);
		leaf_nodes[3]->parent = new TreeNodeReversed(4, leaf_nodes[0]->parent);

		leaf_nodes[2]->parent = leaf_nodes[1]->parent;

	}

	void print_leaves_paths() {
		// example output: 1 2; 1 3 5; 1 3 6; 1 4 7
		for (std::size_t i = 0; i < size; i++) {
			print_node(leaf_nodes[i]);
			std::cout << std::endl;
		}
	}

	void print_node(TreeNodeReversed *current) {
		if (current) {
			print_node(current->parent);
			std::cout << current->data << " ";
		}
	}
};

struct TreeNode { // ternary tree - max 3 child nodes
	int data;
	TreeNode* child_nodes[3];
	TreeNode(int data, TreeNode *left_child = nullptr,
			TreeNode *mid_child = nullptr, TreeNode *right_child = nullptr) {
		this->data = data;
		child_nodes[0] = left_child;
		child_nodes[1] = mid_child;
		child_nodes[2] = right_child;
	}

	void print() {
		std::cout<<data;
		if (! child_nodes[0]) { return; }
		std::cout<<"(";
		for(std::size_t i = 0; i<3; i++) {
			if (!child_nodes[i]) {break;}
			child_nodes[i]->print();
			std::cout<<" ";
		}
		std::cout<<")";

	}

};

TreeNode* example_tree() { //1(2, 3(5, 6), 4(7)) - example from lecture slides
	TreeNode* root = new TreeNode(1,
			new TreeNode(2),
			new TreeNode(3, new TreeNode(5), new TreeNode(6)),
			new TreeNode(4, new TreeNode(7)));
	return root;
}


int main() {

	TreeReversed input_tree;
	input_tree.print_leaves_paths();

	TreeNode* example = example_tree();
	example->print();
	std::cout<<std::endl;

	return 0;
}
}

