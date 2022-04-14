/*
 * pi12_20220407_tree_reverse.cpp
 *
 *  Created on: Apr 7, 2022
 *      Author: KZ
 */

#include <iostream>
#include <vector>

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

	void add_child(TreeNode* child) {
		for(std::size_t i = 0; i<3; i++) {
			if (! child_nodes[i]) {
				child_nodes[i] = child;
				return;
			}
		}
		throw std::logic_error("Max number of children exceeded");
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

struct TreeNodePair {
	TreeNodeReversed* reversed;
	TreeNode* node;
	TreeNodePair(TreeNodeReversed* reversed, TreeNode* node):reversed(reversed), node(node) {}
};

TreeNode* find_pair(std::vector<TreeNodePair>& pairs_found, TreeNodeReversed* reversed) {
	for(auto& pair: pairs_found) {
		if (pair.reversed == reversed) { return pair.node;}
	}
	return nullptr; //not found
}

//Code by Mykhailo Tyshchenko

TreeNode* node_from_reversed(TreeNodeReversed* current, std::vector<TreeNodePair>& pairs_found, TreeNode*& root) {
	if (current) {
		TreeNode* node = find_pair(pairs_found, current);
		if (!node) {
			node = new TreeNode(current->data);
			TreeNode* parent = node_from_reversed(current->parent, pairs_found, root);
			pairs_found.emplace_back(TreeNodePair(current, node));
			if (parent) {
				parent->add_child(node);
			}
			else {
				root = node;
			}

		}
		return node;
	}
	return nullptr;
}

TreeNode* from_reversed(const TreeReversed& reversed) {
	std::vector<TreeNodePair> pairs_found;
	TreeNode* root = nullptr;
	for(std::size_t i = 0; i< reversed.size; i++) {
		TreeNodeReversed* current = reversed.leaf_nodes[i];
		node_from_reversed(current, pairs_found, root);
		//TreeNodeReversed* parent = current->parent;
	}
	return root;

}


int main() {

	TreeReversed input_tree;
	input_tree.print_leaves_paths();

	TreeNode* example = example_tree();
	example->print();
	std::cout<<std::endl;

	TreeNode* output = from_reversed(input_tree);
	output->print();
	std::cout<<std::endl;

	return 0;
}
}

