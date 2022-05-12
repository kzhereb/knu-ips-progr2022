/*
 * pi12_20220505_23tree.cpp
 *
 *  Created on: May 5, 2022
 *      Author: KZ
 */

#include <iostream>
#include <cassert>

namespace pi12_20220505_23tree {

struct TreeNode {
	int data[2];
	int size; // number of data items
	TreeNode* children[3];
	TreeNode* parent;

	TreeNode(int data1, TreeNode* parent = nullptr) {
		this->data[0] = data1;
		this->size = 1;
		children[0] = children[1] = children[2] = nullptr;
		this->parent = parent;
	}

	TreeNode(int data1, int data2, TreeNode* parent = nullptr) {
		this->data[0] = data1;
		this->data[1] = data2;
		this->size = 2;
		children[0] = children[1] = children[2] = nullptr;
		this->parent = parent;
	}

	TreeNode(int data1, int data2, int data3, TreeNode* parent = nullptr) {
		assert(data1<data2);
		assert(data2<data3);

		this->data[0] = data2;
		this->size = 1;
		this->children[0] = new TreeNode(data1, this);
		this->children[1] = new TreeNode(data3, this);

		this->parent = parent;

	}

	void add_single_data(int data) {
		assert(size == 1);
		if (data > this->data[0]) {
			this->data[1] = data;
			size = 2;
		} else {
			this->data[1] = this->data[0];
			this->data[0] = data;
			size = 2;
		}
	}

	void split(int data, TreeNode* child, TreeNode* new_children[2]) {
		int data3[3];
		TreeNode* child4[4];
		if (data < child->data[0]) {
			data3[0] = data;
			data3[1] = child->data[0];
			data3[2] = child->data[1];

			TreeNode* new_children1[2] = {nullptr, nullptr};
			split(data, child->children[0], new_children1);
			child4[0] = new_children1[0];
			child4[1] = new_children1[1];
			child4[2] = child->children[1];
			child4[3] = child->children[2];
			TreeNode* temp = split(data3, child4);
			new_children[0] = temp->children[0];
			new_children[1] = temp->children[1];
		}
	}

	TreeNode* split(int data[3], TreeNode* children[4]) {
		TreeNode* result = new TreeNode(data[1]);

		result->children[0] = new TreeNode(data[0]);
		result->children[0]->children[0] = children[0];
		result->children[0]->children[1] = children[1];

		result->children[1] = new TreeNode(data[2]);
		result->children[1]->children[0] = children[2];
		result->children[1]->children[1] = children[3];

		return result;
	}

	//return nullptr if added, else "4-node" (2-node with both children as 2-nodes)
	TreeNode* add_and_split(int new_data) {
		if (children[0] == nullptr) {
			if (size == 1) {
				add_single_data(new_data);
				return nullptr;
			} else {
				if (new_data < data[0]) {
					return new TreeNode(new_data, data[0], data[1]);
				} else if (new_data < data[1]) {
					return new TreeNode(data[0], new_data, data[1]);
				} else {
					return new TreeNode(data[0], data[1], new_data);
				}
			}
		}
		TreeNode* extra = nullptr;
		if (size == 1) {
			if (new_data < data[0]) {
				extra = children[0]->add_and_split(new_data);
				if (!extra) { return nullptr;}
				data[1] = data[0];
				data[0] = extra->data[0];
				children[2] = children[1];
				children[0] = extra->children[0];
				children[1] = extra->children[1];
				size = 2;
				return nullptr;
			} else {
				extra = children[1]->add_and_split(new_data);
				if (!extra) { return nullptr;}
				data[1] = extra->data[0];
				children[1] = extra->children[0];
				children[2] = extra->children[1];
				size = 2;
				return nullptr;
			}
		} else {
			if (new_data < data[0]) {
				extra = children[0]->add_and_split(new_data);
				if (!extra) { return nullptr;}
				TreeNode* result = new TreeNode(extra->data[0], data[0], data[1]);
				result->children[0]->children[0] = extra->children[0];
				result->children[0]->children[1] = extra->children[1];
				result->children[1]->children[0] = children[1];
				result->children[1]->children[1] = children[2];
				return result;
			} else if (new_data < data[1]) {
				extra = children[1]->add_and_split(new_data);
				if (!extra) { return nullptr;}
				TreeNode* result = new TreeNode(data[0], extra->data[0], data[1]);
				result->children[0]->children[0] = children[0];
				result->children[0]->children[1] = extra->children[0];
				result->children[1]->children[0] = extra->children[1];
				result->children[1]->children[1] = children[2];
				return result;
			} else {
				extra = children[2]->add_and_split(new_data);
				if (!extra) { return nullptr;}
				TreeNode* result = new TreeNode(data[0], data[1], extra->data[0]);
				result->children[0]->children[0] = children[0];
				result->children[0]->children[1] = children[1];
				result->children[1]->children[0] = extra->children[0];
				result->children[1]->children[1] = extra->children[1];
				return result;
			}
		}
	}

	void print_as_tree() {
		std::cout<<data[0];
		if (size == 2) {
			std::cout<<";"<<data[1];
		}
		std::cout<<"(";
		if (children[0]) {
			children[0]->print_as_tree();
		}
		std::cout<<",";
		if (children[1]) {
			children[1]->print_as_tree();
		}
		std::cout<<",";
		if (children[2]) {
			children[2]->print_as_tree();
		}
		std::cout<<")";
	}

//	bool add_and_split(int data, int child_index) {
//		TreeNode* child = children[child_index];
//		if (children[child_index]->add(data)) { return true;}
//		else {
//			if (this->size == 1) {
//				if (data < child->data[0]) {
//					add_single_data(child->data[0]);
//					child->data[0] = data;
//				} else if (data < child->data[1]) {
//					add_single_data(data);
//				} else { // data > child->data[1]
//					add_single_data(child->data[1]);
//					child->data[1] = data;
//				}
//				return true;
//			} else { //size == 2
//				if (data < child->data[0]) {
//					TreeNode* new_children[2] = new TreeNode*[2];
//					split(data, child->children[0], new_children);
//					data3 = {data, child->data[0], child->data[1]};
//					child4 = {new_children[0], new_children[1], child->children[1], child->children[2]};
//					split(data3, child4);
//
//};
//				}
//			}
//		}
//	}
//
//	//returns true if added without need to rebalance
//	bool add(int data) {
//		if (size == 1) {
//			if (children[0] == nullptr) {
//				add_single_data(data);
//				return true;
//			} else {
//				if (data < this->data[0]) {
//					add_and_split(data, 0);
//					return true;
//				} else {
//					assert(children[1]!=nullptr);
//					add_and_split(data, 1);
//					return true;
//				}
//			}
//		} else { //size == 2
//			if (children[0] == nullptr) {
//				return false;
//			} else {
//				if (data < this->data[0]) {
//					add_and_split(data,0);
//				} else if (data < this->data[1]) {
//					add_and_split(data,1);
//				} else {
//					add_and_split(data,2);
//				}
//			}
//		}
//		if (data < this->data[0]) {
//			if (children[0]) {
//				children[0]->add(data);
//			} else {
//				children[0] = new TreeNode(data, this);
//			}
//		} else if (size == 2) {
//			if (data < this->data[1]) {
//				if (children[1]) {
//					children[1]->add(data);
//				} else {
//					children[1] = new TreeNode(data, this);
//				}
//			} else {
//				if (children[2]) {
//					children[2]->add(data);
//				} else {
//					children[2] = new TreeNode(data, this);
//				}
//			}
//		} else {
//			this->data[1] = data;
//		}
//	}
};

struct B23Tree {
	TreeNode* root;

	B23Tree() {
		root = nullptr;
	}

	void add(int data) {
		if (!root) {
			root = new TreeNode(data);
		} else {
			TreeNode* extra = root->add_and_split(data);
			if (extra) {
				root = extra;
			}
		}

	}

	void print_as_tree() {
		if(root) { root->print_as_tree();}
		else { std::cout<<"empty tree";}
		std::cout<<std::endl;
	}

};


int main(){
	B23Tree tree;

	tree.add(1);
	tree.print_as_tree();
	tree.add(2);
	tree.print_as_tree();
	tree.add(3);
	tree.print_as_tree();
	tree.add(4);
	tree.print_as_tree();
	tree.add(5);
	tree.print_as_tree();
	tree.add(6);
	tree.print_as_tree();
	tree.add(7);
	tree.print_as_tree();

	return 0;
}
}


