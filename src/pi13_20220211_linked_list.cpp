/*
 * pi13_20220211_linked_list.cpp
 *
 *  Created on: Feb 11, 2022
 *      Author: KZ
 */

#include <iostream>

namespace pi13_20220211_linked_list {

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
void append_item(ListNode*& list_head, int data) {
	ListNode* new_node = new ListNode;
	new_node->data  = data;
	new_node->next = nullptr;

	if (list_head == nullptr) {
		new_node->prev = nullptr;
		list_head = new_node;
		return;
	}
	ListNode* current = list_head;
	while(current->next != nullptr) {
		current = current->next;
	}
	new_node->prev = current;
	current->next = new_node;
//	return list_head;
}


// add item to list after specific position (1 is after first element,  is after second element)
// function written by Mykola Vlasenko
void add_item_after_position(ListNode*& list_head, int data, std::size_t position) {
	ListNode* new_node = new ListNode;
	new_node->data  = data;
	new_node->next = nullptr;

	if (list_head == nullptr) {
		new_node->prev = nullptr;
		list_head = new_node;
		return;
	}

	//insert at start:
	if (position == 0) {
		new_node->prev = nullptr;
		new_node->next = list_head;
		list_head->prev = new_node;
		list_head = new_node;
		return;
	}

	ListNode* current = list_head;
	std::size_t current_position = 1;
	//if position is higher than the number of nodes, just append to end
	while((current->next != nullptr) && (current_position < position)) {
		current = current->next;
		current_position++;
	}
	//changing next/prev parameters, so that current points to new_node, and new_mode node points to the node that the current was pointing to
	new_node->next = current->next;
	new_node->prev = current;
	if (current->next) { current->next->prev = new_node; }
	current->next = new_node;

}

// remove item from list after position (might be a bit buggy though)
// function written by Mykola Vlasenko
void remove_item_at_position(ListNode*& list_head, std::size_t position) {
	if (list_head == nullptr) {
		return;
	}
	ListNode* current = list_head;
	int current_position = 0;
	//if position is higher than the number of nodes - don't remove, output error
	while((current != nullptr) && (current_position < position)) {
		current = current->next;
		current_position++;
	}

	if (current == nullptr) {
		std::cout << "ERROR: trying to delete nonexistent element" << std::endl;
		return;
	}

	if (current == list_head) { //remove from start
        if (current->next == nullptr) { //remove single item, results in empty list
			list_head = nullptr;
        } else {
			list_head = current->next;
			list_head->prev = nullptr;
		}
        delete current;

		return;
	}

    ListNode* prev_node = current->prev;

    if (current->next == nullptr) { //remove from end
        prev_node->next = nullptr;
	} else { //remove in the middle
		ListNode* next_node = current->next;
        prev_node->next = next_node;
        next_node->prev = prev_node;
	}
    delete current;

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

void print_reverse(ListNode* list_head) {
	ListNode* current = list_head;
	if (current == nullptr) { std::cout<<std::endl; return; }
	while (current->next != nullptr) {
		current = current->next;
	}
	while(current != nullptr) {
		std::cout<<current->data<<" ";
		current = current->prev;
	}
	std::cout<<std::endl;
}


// remove entire list


//before: value = 23
void change_value_not_working(int value) {
	//before: value = 23
	value = 125;
	//after: value = 125
}
//after: value = 23 (copy was changed, original not changed)

//before: value = 23
void change_value(int& value) {
	//before: value = 23
	value = 125;
	//after: value = 125
}
//after: value = 125 (original was changed, because it was passed by reference)


//before: p_value = A2, *A2 = 23 = another_value
//WRONG! after: p_value = A3, *A3 = 123 = local_value; another_value = 23
void change_value_of_pointer(int* p_value) {
	int local_value = 123;
	//before: p_value = A2, *A2 = 23 = another_value
	p_value = &local_value;
	//after: p_value = A3, *A3 = 123 = local_value; another_value = 23
	std::cout<<"value from ptr="<<(*p_value)<<std::endl;
}
//after: p_value = A2, *A2 = 23 = another_value; another_value = 23

//before: p_value = A2, *A2 = 23 = another_value
void change_value_through_pointer(int* p_value) {
	int local_value = 123;
	*p_value = local_value;
}
//after: p_value = A2, *A2 = 123; p_value=>another_value; another_value = 123


void test_pointers() {
	int value = 5;
	int *p_value = &value;
	std::cout << "value from ptr=" << (*p_value) << std::endl;
	value = 7;
	std::cout << "value from ptr=" << (*p_value) << std::endl;
	int another_value = 15;
	//before: p_value = A1, *A1 = 7 = value; p_value=>value;
	p_value = &another_value;
	//after: p_value = A2, *A2 = 15 = another_value; p_value=>another_value; value = 7
	std::cout << "value from ptr=" << (*p_value) << std::endl;
	value = 9;
	std::cout << "value from ptr=" << (*p_value) << std::endl;
	another_value = 17;
	std::cout << "value from ptr=" << (*p_value) << std::endl;
	//before: p_value = A2, *A2 = 17 = another_value; p_value=>another_value
	*p_value = 23;
	//after: p_value = A2; *A2 = 23 = another_value; p_value=>another_value
	std::cout << "value from ptr=" << (*p_value) << ", value=" << value
			<< ",another_value=" << another_value << std::endl;
	change_value_not_working(another_value);
	std::cout << "value from ptr=" << (*p_value) << ", value=" << value
			<< ",another_value=" << another_value << std::endl;
	change_value(another_value);
	std::cout << "value from ptr=" << (*p_value) << ", value=" << value
			<< ",another_value=" << another_value << std::endl;
	change_value_of_pointer(p_value);
	std::cout << "value from ptr=" << (*p_value) << ", value=" << value
			<< ",another_value=" << another_value << std::endl;
	change_value_through_pointer(p_value);
	std::cout << "value from ptr=" << (*p_value) << ", value=" << value
			<< ",another_value=" << another_value << std::endl;
}




int main() {

	//test_pointers();


	ListNode* list_head = create_empty_list();

	append_item(list_head, 1);
	append_item(list_head, 5);
	append_item(list_head, 0);
	append_item(list_head, 7);

	print_list(list_head);
	print_reverse(list_head);

	add_item_after_position(list_head, 9, 2);
	print_list(list_head);
	print_reverse(list_head);

	add_item_after_position(list_head, 3, 5);
	print_list(list_head);
	print_reverse(list_head);

	remove_item_at_position(list_head, 0);
	print_list(list_head);
	print_reverse(list_head);

	remove_item_at_position(list_head, 4);
	print_list(list_head);
	print_reverse(list_head);

	remove_item_at_position(list_head, 0);
	print_list(list_head);
	print_reverse(list_head);

	remove_item_at_position(list_head, 1);
	print_list(list_head);
	print_reverse(list_head);

	add_item_after_position(list_head, 1, 0);
	print_list(list_head);
	print_reverse(list_head);


	return 0;
}

}
