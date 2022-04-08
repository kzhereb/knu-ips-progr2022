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

	std::vector<ComponentNode*> find_by_type(ComponentType type) {
		std::vector<ComponentNode*> result;
		if (this->type == type) {
			result.push_back(this);
		}
		for(std::size_t i = 0; i<subcomponents.size(); i++) {
			std::vector<ComponentNode*> child_result = subcomponents[i]->find_by_type(type);
			result.insert(result.end(), child_result.begin(), child_result.end());
		}
		return result;
	}
	// search by part of name
	// e.g. if name is "basic producer", then it should be searchable by "producer", or "basic", or "basic producer" etc.
	std::vector<ComponentNode*> find_by_name_part(std::string name) {
		std::vector<ComponentNode*> result;
		return result; // TODO: implement me
	}

	int total_cost() {
		int result = this->cost;
		for(std::size_t i = 0; i<subcomponents.size(); i++) {
			result += subcomponents[i]->total_cost();
		}
		return result;
	}

	// returns number of time units before profits from this component exceed its cost
	// e.g. if total cost is 100 and total profit per time unit is 10, then it takes 10 time units
	int time_to_profitability() {
		return -1; //TODO: implement me
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

	std::vector<ComponentNode*> found = system->find_by_type(Basic);
	std::cout<<"found "<< found.size() << " components"<<std::endl;
	for(ComponentNode* result : found) {
		result->print();
		std::cout<<std::endl;
	}

	std::cout<<"Total cost of system: "<<system->total_cost()<<std::endl;

	std::cout<<"removing items"<<std::endl;
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

