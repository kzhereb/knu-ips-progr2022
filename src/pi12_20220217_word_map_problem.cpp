/*
 * pi12_20220217_word_map_problem.cpp
 *
 *  Created on: Feb 17, 2022
 *      Author: KZ
 */

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cctype>

namespace pi12_20220217_word_map_problem {

struct WordTranslation {
	std::string in_word;
	std::string out_word;
	double frequency; // from 0 to 1

	char key() { return in_word[0]; }
};

struct ListNode {
	WordTranslation data;
	ListNode* next;
};

void add_to_list(ListNode* head, WordTranslation data) {
	assert(head!=nullptr);
	ListNode* current = head;
	while (true) {
		if (current->data.frequency <= data.frequency) {
			ListNode* new_node = new ListNode;
			new_node->data = current->data;
			new_node->next = current->next;
			current->data = data;
			current->next = new_node;
			return;
		}
		if (current->next == nullptr)
			break;
		current = current->next;
	}
	ListNode* new_node = new ListNode;
	new_node->data = data;
	new_node->next = nullptr;
	current->next = new_node;
}

struct WordMap {
	std::vector<ListNode*> list_heads;

	void add_translation(WordTranslation translation) {
		char key = translation.key();
		for(ListNode* head: list_heads) {
			if (head->data.key() == key) {
				add_to_list(head, translation);
				return;
			}
		}
		ListNode* new_node = new ListNode;
		new_node->data = translation;
		new_node->next = nullptr;
		list_heads.push_back(new_node);
	}

	std::string translate_single_word(std::string word) {
		assert(word.length()>0);
		char key = word[0];
		for(ListNode* head: list_heads) {
			if (head->data.key() == key) {
				ListNode* current = head;
				while (current) {
					if (current->data.in_word == word) {
						return current->data.out_word;
					}
					current = current->next;
				}
				return word; // no translation found for this key
			}
		}
		return word; // no key found
	}

	bool is_word_char(char ch) {
		// see https://en.cppreference.com/w/cpp/string/byte/isalnum
		return std::isalnum(static_cast<unsigned char>(ch));
	}

	std::string translate_text(std::string input) {
		std::string result;
		std::string current_word;
		std::size_t input_length = input.length();
		for(std::size_t i = 0; i<=input_length; i++) { // for i == length(), must return null char
			char current = input[i];
			if (is_word_char(current)) { current_word += current;}
			else { // space, punctuation, some unknown char
				if (current_word.length() > 0) {
					std::string translated_word = translate_single_word(current_word);
					result += translated_word;
				}
				result += current;
				current_word = "";
			}
		}


		return result;

	}

	void print() {
		for(ListNode* head: list_heads) {
			ListNode* current = head;
			while (current) {
				std::cout<<"("<<current->data.in_word<<", "<<current->data.out_word<<", "<<current->data.frequency<<") ";
				current = current->next;
			}
			std::cout<<std::endl;
		}
	}
};

WordTranslation input_array[] {
		{"abc", "123", 0.2},
		{"ade", "546", 0.7},
		{"ceg", "6232", 0.6},
		{"c", "0", 0.01},
		{"def", "3332", 0.5},
		{"xyz", "999", 0.2}
};


//translate_using_map


int main() {
	WordMap map;
	for (std::size_t i = 0; i< 6; i++) {
		map.add_translation(input_array[i]);
	}
	map.print();
	std::cout<<map.translate_single_word("c")<<" ";
	std::cout<<map.translate_single_word("d")<<" ";
	std::cout<<map.translate_single_word("e")<<" ";
	std::cout<<std::endl;

	std::cout<<map.translate_text("abc aaa!! c a1b2 xyz XYZ ok? a123")<<std::endl;

	return 0;
}
}
