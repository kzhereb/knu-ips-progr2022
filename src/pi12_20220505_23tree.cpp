/*
 * pi12_20220505_23tree.cpp
 *
 *  Created on: May 5, 2022
 *      Author: KZ
 */

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

	void add(int data) {
		if (data < this->data[0]) {
			if (children[0]) {
				children[0]->add(data);
			} else {
				children[0] = new TreeNode(data, this);
			}
		} else if (size == 2) {
			if (data < this->data[1]) {
				if (children[1]) {
					children[1]->add(data);
				} else {
					children[1] = new TreeNode(data, this);
				}
			} else {
				if (children[2]) {
					children[2]->add(data);
				} else {
					children[2] = new TreeNode(data, this);
				}
			}
		} else {
			this->data[1] = data;
		}
	}
};



int main(){
	return 0;
}
}


