/*
 * pi13_20220211_linked_list.cpp
 *
 *  Created on: Feb 11, 2022
 *      Author: KZ
 */

#include <iostream>

struct ListNode {
	int data;
	ListNode* prev;
	ListNode* next;
};

// build list
ListNode* create_empty_list() {
//	ListNode* head = new ListNode;
//	head->prev = nullptr;
//	head->next = nullptr;
//	head->data = 0; //TODO: don't know what to set here?
//	return head;
	return nullptr;
}
// add item to list
ListNode* append_item(ListNode* list_head, int data) {
	ListNode* new_node = new ListNode;
	new_node->data  = data;
	new_node->next = nullptr;
	if (list_head == nullptr) {
		new_node->prev = nullptr;
		return new_node;
	}
	ListNode* current = list_head;
	while(current->next != nullptr) {
		current = current->next;
	}
	new_node->prev = current;
	current->next = new_node;
	return list_head;
}
// print list
void print_list(ListNode* list_head) {
	ListNode* current = list_head;
	while(current != nullptr) {
		std::cout<<current->data<<" ";
		current = current->next;
	}
	std::cout<<std::endl;
}

// remove item from list
// remove entire list


int main() {
	ListNode* list_head = create_empty_list();

	list_head = append_item(list_head, 1);
	list_head = append_item(list_head, 5);
	list_head = append_item(list_head, 0);
	list_head = append_item(list_head, 7);

	print_list(list_head);


	return 0;
}

