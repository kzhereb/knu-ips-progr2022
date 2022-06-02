/*
 * pi12_20220602_tasks.cpp
 *
 *  Created on: Jun 2, 2022
 *      Author: KZ
 */

#include <iostream>
#include <string>
#include <cassert>
#include <cctype>

namespace pi12_20220602_tasks {

struct ListNode {
	int data;
	ListNode* next;
};

void split_odd_even(ListNode* initial,  ListNode*& even, ListNode*& odd) {
	if (!initial) { // empty list
		odd = even = nullptr;
		return;
	}

	ListNode* current = initial;

	ListNode* current_odd = nullptr;
	ListNode* current_even = nullptr;

	do {
		if (current->data % 2 == 0) { //even
			if (current_even) {
				current_even->next = current;
				current_even = current;
			} else {
				even = current_even = current;
			}
		} else { // odd
			if (current_odd) {
				current_odd->next = current;
				current_odd = current;
			} else {
				odd = current_odd = current;
			}
		}
		current = current->next;
	} while (current != initial);
	if (current_even) {
		current_even->next = even;
	}
	if (current_odd) {
		current_odd->next = odd;
	}

}

void add(ListNode*& start, ListNode*& end, int data) {
	ListNode* new_node = new ListNode;
	new_node->data = data;
	if (start) {
		end->next = new_node;
		new_node->next = start;
		end = new_node;
	} else {
		start = end = new_node;
		new_node->next = new_node;
	}
}

void print(ListNode* start) {
	if (!start) {
		std::cout<<"empty list"<<std::endl;
		return;
	}
	ListNode* current = start;
	do{
		std::cout<<current->data<<" ";
		current = current->next;
	} while(current!=start);
	std::cout<<std::endl;
}

void push(ListNode*& start, int data) {
	ListNode* new_node = new ListNode;
	new_node->data = data;
	new_node->next = start;
	start = new_node;
}

int pop(ListNode*& start) {
	assert(start!=nullptr);
	int result = start->data;
	ListNode* to_delete = start;
	start = start->next;
	delete to_delete;
	return result;

}

int peek(ListNode* start) {
	assert(start!=nullptr);
	return start->data;
}

bool is_empty(ListNode* start) {
	return start == nullptr;
}

std::string infix_to_postfix(std::string infix) {
	std::string current_number="";
	std::string result = "";
	ListNode* stack = nullptr;
	const int DIVIDE = -10;
	const int MINUS = -20;
	for(std::size_t i = 0; i<infix.size(); i++) {
		char current = infix[i];
		if (std::isdigit(static_cast<unsigned char>(current))) {
			current_number+=current;
		} else if (current == '/') {
			//int value = std::stoi(current_number);
			current_number = "";
			result += current_number + " ";
			if (!is_empty(stack) && peek(stack) == DIVIDE) {
				pop(stack);
				result+= "/ ";
			}
			push(stack, DIVIDE);
		} else if (current == '-') {
			//int value = std::stoi(current_number);
			current_number = "";
			result += current_number + " ";
			if (!is_empty(stack)) {
				int prev = pop(stack);
				if (prev == DIVIDE) { result+= "/ ";}
				else if (prev == MINUS) {result+= "- ";}
			}
			push(stack, MINUS);
		}
	}
	// output all operators from stack
}

int main() {
	ListNode* start = nullptr;
	ListNode* end = nullptr;
	add(start, end, 1);
	add(start, end, 3);
	add(start, end, 4);
	add(start, end, 5);
	add(start, end, 10);
	print(start);

	ListNode* even = nullptr;
	ListNode* odd = nullptr;
	split_odd_even(start, even, odd);
	std::cout<<"even: ";
	print(even);
	std::cout<<"odd: ";
	print(odd);
	std::cout<<"old start is not valid anymore: ";
	print(start);


	return 0;
}


}

