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
void append_item(ListNode** list_head, int data) {
	ListNode* new_node = new ListNode;
	new_node->data  = data;
	new_node->next = nullptr;

	// before: list_head => nullptr
	// after: list_head => new_node => (data=data, next=nullptr)
	if (*list_head == nullptr) {
		new_node->prev = nullptr;
		*list_head = new_node;
		return;
	}
	ListNode* current = *list_head;
	while(current->next != nullptr) {
		current = current->next;
	}
	new_node->prev = current;
	current->next = new_node;
//	return list_head;
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


//before: value = 23
void change_value(int value) {
	//before: value = 23
	value = 125;
	//after: value = 125
}
//after: value = 23 (copy was changed, original not changed)

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
	ListNode** p_head = &list_head;

	append_item(p_head, 1);
	append_item(p_head, 5);
	append_item(p_head, 0);
	append_item(p_head, 7);

	print_list(list_head);


	return 0;
}

