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

		if (data == 0) {
			return;
		}

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

SparseMatrix sum(SparseMatrix a, SparseMatrix b) {
	assert(a.num_cols == b.num_cols);
	assert(a.num_rows == b.num_rows);

	SparseMatrix result(a.num_rows, a.num_cols);
	for(std::size_t i = 0; i< a.num_rows; i++) {
		MatrixNode* current_a = a.rows[i];
		MatrixNode* current_b = b.rows[i];
		for (std::size_t j = 0; j<a.num_cols; j++) {
			int result_data = 0;
			if (current_a && current_a->column_index == j) {
				result_data += current_a->data;
				current_a = current_a->next;
			}
			if (current_b && current_b->column_index == j) {
				result_data += current_b->data;
				current_b = current_b->next;
			}
			result.set(result_data, i, j);
		}
	}

	return result;
}


int main() {
	SparseMatrix matrix(4,4);

	matrix.print();
	std::cout<<"matrix:"<<std::endl;

	matrix.set(1, 1, 0);
	matrix.set(2, 1, 1);
	matrix.set(3, 1, 2);
	matrix.set(4, 1, 3);
	matrix.set(5, 1, 3);

	matrix.set(6, 2, 0);
	matrix.set(7, 2, 2);

	matrix.set(8, 3, 1);

	matrix.print();

	SparseMatrix matrix2(4,4);


	matrix2.set(6, 2, 0);
	matrix2.set(7, 2, 2);

	matrix2.set(8, 3, 1);

	std::cout<<"matrix2:"<<std::endl;
	matrix2.print();

	SparseMatrix matrix3 = sum(matrix, matrix2);
	std::cout<<"sum:"<<std::endl;
	matrix3.print();

	return 0;
}
}

