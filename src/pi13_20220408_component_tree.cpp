/*
 * pi13_20220408_component_tree.cpp
 *
 *  Created on: Apr 8, 2022
 *      Author: KZ
 */

#include <string>
#include <vector>
#include <iostream>


namespace pi13_20220408_component_tree {

enum ComponentType {Basic=1, // no subcomponents, basic functionality
	Container, // contains subcomponents
	Advanced,  // may contain subcomponents, adds extra functionality
	Control    // controls its subcomponents
};

struct ComponentNode {
	std::string name;
	ComponentType type;
	int cost;
	int profit_per_time;
	std::vector<ComponentNode*> subcomponents;

	ComponentNode(std::string name, ComponentType type, int cost, int profit_per_time) {
		this->name = name;
		this->type = type;
		this->cost = cost;
		this->profit_per_time = profit_per_time;
	}

	void add_subcomponent(ComponentNode* subcomponent) {
		subcomponents.push_back(subcomponent);
	}

	bool remove_subcomponent(ComponentNode* subcomponent) { //removes from tree, but does not delete
		for(std::size_t i=0; i<subcomponents.size(); i++) {
			if (subcomponents[i] == subcomponent) {
				subcomponents.erase(subcomponents.begin()+i);
				return true;
			}
			if (subcomponents[i]->remove_subcomponent(subcomponent)) {
				return true;
			}
		}
		return false;
	}

	void print(int indent_level=0) {
		for(int i=0; i<indent_level; i++) {std::cout<<"  ";}
		std::cout<<"{Name="<<name<<",type="<<type<<",cost="<<cost<<",profit="<<profit_per_time;
		if (subcomponents.size() == 0) {
			std::cout<<", no children}";
			return;
		}
		std::cout<<",children:"<<std::endl;
		for(std::size_t i=0; i<subcomponents.size(); i++) {
			subcomponents[i]->print(indent_level+1);
			std::cout<<std::endl;
		}
		for(int i=0; i<indent_level; i++) {std::cout<<"  ";}
		std::cout<<"} ";
	}
};


int main() {
	ComponentNode* system = new ComponentNode("entire system",Control,100, 0);
	ComponentNode* profit_center = new ComponentNode("profit generator", Basic, 30, 10);
	ComponentNode* producers = new ComponentNode("producers", Container, 40, 0);
	ComponentNode* basic_producer = new ComponentNode("basic producer", Basic, 10, 1);
	ComponentNode* advanced_producer = new ComponentNode("advanced producer", Advanced, 25, 5);

	producers->add_subcomponent(basic_producer);
	producers->add_subcomponent(advanced_producer);
	system->add_subcomponent(producers);
	system->add_subcomponent(profit_center);

	system->print();
	std::cout<<std::endl;

	system->remove_subcomponent(basic_producer);

	system->print();
	std::cout<<std::endl;

	if (system->remove_subcomponent(basic_producer)) {
		std::cout<<"error! removed twice"<<std::endl;
	} else {
		std::cout<<"trying to remove subcomponent that is not in tree, nothing happens"<<std::endl;
	}
	system->print();
	std::cout<<std::endl;



	return 0;
}
}

