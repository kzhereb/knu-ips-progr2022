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

	void print_leaves_path() {
		// example output: 1 2; 1 3 5; 1 3 6; 1 4 7
	}
};


int main() {

	return 0;
}
}

