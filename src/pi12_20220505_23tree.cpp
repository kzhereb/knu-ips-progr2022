/*
 * pi12_20220505_23tree.cpp
 *
 *  Created on: May 5, 2022
 *      Author: KZ
 */

#include <iostream>
#include <vector>
//#include <iterator>
#include <algorithm>
#include <numeric>
#include <random>
#include <cassert>

namespace pi12_20220505_23tree {

struct TreeNode {
	int data[2];
	int size; // number of data items
	TreeNode* children[3];
	TreeNode* parent; //TODO: can be removed

	TreeNode(int data1, TreeNode* parent = nullptr) {
		this->data[0] = data1;
		this->size = 1;
		children[0] = children[1] = children[2] = nullptr;
		this->parent = parent;
	}

	TreeNode(int data1, int data2, TreeNode* parent = nullptr) {
	  assert(data1<=data2);
		this->data[0] = data1;
		this->data[1] = data2;
		this->size = 2;
		children[0] = children[1] = children[2] = nullptr;
		this->parent = parent;
	}

	TreeNode(int data1, int data2, int data3, TreeNode* parent = nullptr) {
		assert(data1<=data2);
		assert(data2<=data3);

		this->data[0] = data2;
		this->size = 1;
		this->children[0] = new TreeNode(data1, this);
		this->children[1] = new TreeNode(data3, this);
		this->children[2] = nullptr;

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


	TreeNode* find_max_subtree() {
		if (children[2]) {
			assert(size == 2);
			return children[2]->find_max_subtree();
		}
		if (children[1]) {
			assert(size == 1);
			return children[1]->find_max_subtree();
		}
		assert(children[0] == nullptr);
		return this; // no children
	}

	int get_max_data() {
		if (size == 2) {
			return data[1];
		} else {
			return data[0];
		}
	}
	enum RemoveResult {Removed, NotFound, NeedParentRemove};

	//void rebalance(TreeNode* current_child, TreeNode* left_child, TreeNode* right_child) {
	// returns true if rebalance complete - no need to rebalance parent
	bool rebalance(int index_current_child) {
		assert(index_current_child < size + 1);
		TreeNode* current_child = children[index_current_child];
		assert(current_child);
		assert(current_child->size == 0);
		TreeNode* left_child = nullptr;
		if (index_current_child > 0) { left_child = children[index_current_child-1]; }
		TreeNode *right_child = (index_current_child < size) ?
									children[index_current_child + 1] :
									nullptr;
		assert(left_child != nullptr || right_child != nullptr);

		if (left_child && left_child->size == 2) {
			current_child->data[0] = this->data[index_current_child - 1];
			this->data[index_current_child - 1] = left_child->data[1];

			current_child->children[1] = current_child->children[0];
			current_child->children[0] = left_child->children[2];

			current_child->size = 1;
			left_child->size = 1;
			return true;
		}

		if (right_child && right_child->size == 2) {
		  assert(index_current_child < this->size);
			current_child->data[0] = this->data[index_current_child]; // not index + 1
			this->data[index_current_child] = right_child->data[0];
			right_child->data[0] = right_child->data[1];

			current_child->children[1] = right_child->children[0];
			right_child->children[0] = right_child->children[1];
			right_child->children[1] = right_child->children[2];
			right_child->children[2] = nullptr;

			current_child->size = 1;
			right_child->size = 1;
			return true;
		}

		if (left_child) {
			assert(left_child->size == 1);

			left_child->data[1] = this->data[index_current_child - 1];

			left_child->children[2] = current_child->children[0];

			left_child->size = 2;
			this->size--;

			if (this->size == 1 && index_current_child == 1) {
				this->data[0] = this->data[1];
				this->children[1] = this->children[2];
				return true;
			}
			if (this->size == 0) {
				return false;
			} else {
				return true;
			}
		}
		assert(right_child!=nullptr);
		assert(right_child->size == 1);

		right_child->data[1] = right_child->data[0];
		right_child->data[0] = this->data[index_current_child]; // not index + 1!!
		assert(right_child->data[0] < right_child->data[1]);

		if (current_child->children[0] != nullptr) {
		  assert(right_child->children[0] != nullptr);
		  assert(right_child->children[1] != nullptr);
		  // previous tree was balanced, if current_child had children - then right_child must have children too
	    right_child->children[2] = right_child->children[1];
	    right_child->children[1] = right_child->children[0];
	    right_child->children[0] = current_child->children[0];

		} else {
		  assert(current_child->children[0] == nullptr);
      assert(right_child->children[0] == nullptr);
      assert(right_child->children[1] == nullptr);
      // in this case, no need to copy nullptrs - previous code would work, but it is extra work
		}
		right_child->size = 2;
		this->size--;

		if (this->size == 1 && index_current_child == 0) {
			this->data[0] = this->data[1];
			assert(current_child == children[0]);
			delete current_child;
			this->children[0] = this->children[1];
			this->children[1] = this->children[2];
			this->children[2] = nullptr;
			return true;
		}

		if (this->size == 0) {
			this->children[0] = this->children[1];
			return false;
		} else {
			return true;
		}

	}

	// can set size to 0, this means parent needs to fix it
	RemoveResult remove(int data_to_remove){
		if (children[0] == nullptr) {
			if (size == 1) {
				if (data[0] == data_to_remove) {
					size = 0;
					return NeedParentRemove;
				} else {
					return NotFound;
				}
			} else { // size == 2
				if (data[0] == data_to_remove) {
					data[0] = data[1];
					size = 1;
					return Removed;
				} else if (data[1] == data_to_remove) {
					size = 1;
					return Removed;
				} else {
					return NotFound;
				}
			}
		}
		if (size == 1) {
			if (data_to_remove < data[0]) {
				RemoveResult result = children[0]->remove(data_to_remove);
				if (result == NeedParentRemove) {
					rebalance(0);
					if (this->size == 0) {return NeedParentRemove;}
					else { return Removed;}
				} else {
					return result;
				}
			} else if (data_to_remove > data[0]) {
				RemoveResult result = children[1]->remove(data_to_remove);
				if (result == NeedParentRemove) {
					rebalance(1);
					if (this->size == 0) {return NeedParentRemove;}
					else { return Removed;}
				} else {
					return result;
				}
			} else { // removing our only data
				TreeNode* prev = children[0]->find_max_subtree();
				assert(prev->children[0] == nullptr);
				int prev_data = prev->get_max_data();
				data[0] = prev_data;
				//prev->remove(prev_data, parent???)
				RemoveResult result = this->children[0]->remove(prev_data); // because we know prev, but don't know full sequence of parents
				assert(result != NotFound);
				if (result == Removed) { return Removed;}
				rebalance(0);
				if (this->size == 0) {return NeedParentRemove;}
				else { return Removed;}
			}
		}
		if (size == 2) {
			if (data_to_remove < data[0]) {
				RemoveResult result = children[0]->remove(data_to_remove);
				if (result == NeedParentRemove) {
					rebalance(0);
					assert(this->size > 0);
					return Removed;
				} else {
					return result;
				}
			} else if (data_to_remove == data[0]) {
				TreeNode* prev = children[0]->find_max_subtree();
				assert(prev->children[0] == nullptr);
				int prev_data = prev->get_max_data();
				data[0] = prev_data;
				RemoveResult result = this->children[0]->remove(prev_data); // because we know prev, but don't know full sequence of parents
				assert(result != NotFound);
				if (result == Removed) { return Removed;}
				rebalance(0);
				assert(this->size > 0);
				return Removed;
			}
			else if (data_to_remove < data[1]) {
				RemoveResult result = children[1]->remove(data_to_remove);
				if (result == NeedParentRemove) {
					rebalance(1);
					assert(this->size > 0);
					return Removed;
				} else {
					return result;
				}
			} else if (data_to_remove == data[1]) {
				TreeNode* prev = children[1]->find_max_subtree();
				assert(prev->children[0] == nullptr);
				int prev_data = prev->get_max_data();
				data[1] = prev_data;
				RemoveResult result = this->children[1]->remove(prev_data); // because we know prev, but don't know full sequence of parents
				assert(result != NotFound);
				if (result == Removed) { return Removed;}
				rebalance(1);
				assert(this->size > 0);
				return Removed;
			} else { // data_to_remove > data[1]
				RemoveResult result = children[2]->remove(data_to_remove);
				if (result == NeedParentRemove) {
					rebalance(2);
					assert(this->size > 0);
					return Removed;
				} else {
					return result;
				}
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

	void print_in_order() {
		if (children[0]) {
			children[0]->print_in_order();
		}
		std::cout<<data[0]<<" ";
		if (children[1]) {
			children[1]->print_in_order();
		}
		if (size == 2) {
			std::cout<<data[1]<<" ";
			if (children[2]) {
				children[2]->print_in_order();
			}
		}
	}


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

	bool remove(int data) {
		TreeNode::RemoveResult result = root->remove(data);
		if (result == TreeNode::NotFound) {return false;}
		if (result == TreeNode::Removed) {return true;}
		if (result == TreeNode::NeedParentRemove) {
			root = root->children[0];
			return true;
		}
	}

	void print_as_tree() {
		if(root) { root->print_as_tree();}
		else { std::cout<<"empty tree";}
		std::cout<<std::endl;
	}

	void print_in_order() {
		if(root) { root->print_in_order();}
		else { std::cout<<"empty tree";}
		std::cout<<std::endl;
	}

	void print_all() {
		print_as_tree();
		print_in_order();
	}

};





std::vector<int> get_random_shuffle(std::initializer_list<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) {
    std::vector<int> v = values;

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(v.begin(), v.end(), g);

    return v;

//    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
//    std::cout << "\n";
}

std::vector<int> get_random_vector(size_t size, int min_value, int max_value) {
    std::vector<int> result(size);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(min_value, max_value);
    for (size_t i = 0; i<size; i++) {
      result[i] = dist(gen);
    }

    return result;

//    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
//    std::cout << "\n";
}

std::vector<int> get_random_norepeat_vector(int min_value, int max_value) {
  assert(min_value<max_value);
  size_t size = max_value - min_value + 1;

  std::vector<int> result(size);
  std::iota(result.begin(), result.end(), min_value);

  std::random_device rd;
  std::mt19937 gen(rd());

  std::shuffle(result.begin(), result.end(), gen);

  return result;

//    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
//    std::cout << "\n";
}


void test_random_vector() {
  std::cout<<"create large vector of positive and negative values, then remove all positive"<<std::endl;

  B23Tree tree;
  std::vector<int> values = get_random_vector(100, -100, 100);
  for(int item: values) {
    std::cout<<"adding value "<<item<<std::endl;
    tree.add(item);
    tree.print_all();
  }
  for(int i=0; i<=100; i++) {
    std::cout<<"removing value "<<i<<std::endl;
    tree.remove(i);
    tree.print_all();
  }
}

void test_repeated_values() {
  B23Tree tree;
  std::vector<int> values = get_random_shuffle({1, 1, 2, 3, 8, 10, 13, 13, 14, 14, 15, 17, 32});
  // 8, 17, 32, 14, 13, 3, 1, 1, 15, 2, 10, 14, 13
  for(int item: values) {
    std::cout<<"adding value "<<item<<std::endl;
    tree.add(item);
    tree.print_all();
  }
  for(int i=0; i<=100; i++) {
    std::cout<<"removing value "<<i<<std::endl;
    tree.remove(i);
    tree.print_all();
  }
}

void test_norepeated_values() {
  B23Tree tree;
  std::vector<int> values = get_random_norepeat_vector(-5, 5);
  for(int item: values) {
    std::cout<<"adding value "<<item<<std::endl;
    tree.add(item);
    tree.print_all();
  }
  for(int i=0; i<=100; i++) {
    std::cout<<"removing value "<<i<<std::endl;
    tree.remove(i);
    tree.print_all();
  }
}

void test_fixed_vector(std::initializer_list<int> input) {
  B23Tree tree;
  std::vector<int> values = input;
  for(int item: values) {
    std::cout<<"adding value "<<item<<std::endl;
    tree.add(item);
    tree.print_all();
  }
  for(int i=0; i<=5; i++) {
    std::cout<<"removing value "<<i<<std::endl;
    tree.remove(i);
    tree.print_all();
  }
}


int main(){
	B23Tree tree;

	tree.add(1);
	tree.print_all();
	tree.add(2);
	tree.print_all();
	tree.add(3);
	tree.print_all();
	tree.add(4);
	tree.print_all();
	tree.add(5);
	tree.print_all();
	tree.add(6);
	tree.print_all();
	tree.add(7);
	tree.print_all();

	tree.remove(7);
	tree.print_all();
	tree.remove(6);
	tree.print_all();
	tree.remove(5);
	tree.print_all();
	tree.remove(4);
	tree.print_all();
	tree.remove(3);
	tree.print_all();
	tree.remove(2);
	tree.print_all();
	tree.remove(1);
	tree.print_all();

	std::cout<<"random shuffle"<<std::endl;
	B23Tree tree2;
	std::vector<int> random_order = get_random_shuffle();
	for(int item: random_order) {
		tree2.add(item);
		tree2.print_all();
	}

	TreeNode* max_node = tree2.root->find_max_subtree();
	max_node->print_as_tree();
	std::cout<<max_node->get_max_data()<<std::endl;
	TreeNode* root_prev = tree2.root->children[0]->find_max_subtree();
	root_prev->print_as_tree();
	assert(root_prev->get_max_data() == tree2.root->data[0] - 1);

	//test_random_vector();
	//test_repeated_values();
	//test_norepeated_values();
	test_fixed_vector({3, -3, 5, -4, -5, -1, 0, -2, 4, 1, 2});

	return 0;
}
}


