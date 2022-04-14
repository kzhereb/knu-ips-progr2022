/*
 * pi12_20220414_sparse_matrix.cpp
 *
 *  Created on: Apr 14, 2022
 *      Author: KZ
 */

#include <iostream>
#include <cassert>


namespace pi12_20220414_sparse_matrix{

struct MatrixNode {
	int data;
	std::size_t column_index;
	MatrixNode* next;

	MatrixNode(int data, std::size_t column_index, MatrixNode* next = nullptr) {
		this->data = data;
		this->column_index = column_index;
		this->next = next;
	}
};
const std::size_t MAX_ROWS = 10;
struct SparseMatrix {
	MatrixNode* rows[MAX_ROWS];
	std::size_t num_rows;
	std::size_t num_cols;

	SparseMatrix(std::size_t num_rows, std::size_t num_cols) {
		this->num_rows = num_rows;
		this->num_cols = num_cols;
		for(std::size_t i = 0; i<num_rows; i++) {
			rows[i] = nullptr;
		}
	}

	void set(int data, std::size_t row, std::size_t column) {
		assert(row < num_rows);
		assert(column < num_cols);

		MatrixNode* current = rows[row];
		if (!current) {
			MatrixNode* new_node = new MatrixNode(data, column);
			rows[row] = new_node;
			return;
		}
		while (current->next) {
			if (current->column_index == column) {
				current->data = data;
				return;
			}
			if (current->next->column_index > column) {
				MatrixNode* new_node = new MatrixNode(data, column, current->next);
				current->next = new_node;
				return;
			}
			current = current->next;
		}
		if (current->column_index == column) {
			current->data = data;
			return;
		}
		current->next = new MatrixNode(data, column);
	}

	void print() {
		for(std::size_t i = 0; i < num_rows; i++) {
			MatrixNode* current = rows[i];
			for (std::size_t j = 0; j < num_cols; j++) {
				if (current && current->column_index == j) {
					std::cout<<current->data<<" ";
					current = current->next;
				} else {
					std::cout<<"0 ";
				}


			}
			std::cout<<std::endl;
		}
	}

};


int main() {
	SparseMatrix matrix(4,4);

	matrix.print();
	std::cout<<std::endl;

	matrix.set(1, 1, 0);
	matrix.set(2, 1, 1);
	matrix.set(3, 1, 2);
	matrix.set(4, 1, 3);
	matrix.set(5, 1, 3);

	matrix.set(6, 2, 0);
	matrix.set(7, 2, 2);

	matrix.set(8, 3, 1);


	matrix.print();
	return 0;
}
}

