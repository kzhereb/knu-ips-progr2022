/*
 * pi12_20220421_graph.cpp
 *
 *  Created on: Apr 21, 2022
 *      Author: KZ
 */

#include <iostream>
#include <string>
#include <cassert>

namespace pi12_20220421_graph {


struct BitVector {
	unsigned bits;

	BitVector() { bits = 0; }

	bool get(std::size_t index) {
		assert(index < 32);

		return (bits >> index) & 1;
	}

	void set(std::size_t index, bool value=true) {
		assert(index < 32);

		if (value) {
			bits |=  (1 << index);
		} else {
			bits &= ~(1<<index);
		}
	}

	void print(std::size_t size = 32) {
		unsigned current = bits;
		for(std::size_t i = 0; i< size; i++) {
			std::cout<< (current & 1)<<" ";
			current >>= 1;
		}
		std::cout<<std::endl;
	}

	bool is_full(std::size_t size = 32) {
		assert(size<32);

		unsigned mask = ~(~0 << size);

		return (bits & mask) == mask;
	}
};

struct Graph {
	BitVector edges[32];
	std::size_t size;

	Graph (std::size_t size) {
		assert(size<=32);

		this->size = size;
	}

	void add_edge(std::size_t from, std::size_t to) {
		assert(from < size);
		assert(to < size);

		edges[from].set(to);
	}

	void print() {
		for(std::size_t i = 0; i<size; i++) {
			for (std::size_t j = 0; j<size; j++) {
				if (edges[i].get(j)) {
					std::cout<<i<<"->"<<j<<" ";
				}
			}
			std::cout<<std::endl;
		}
	}

	void visit_recursive(BitVector& visited, std::size_t vertex) {
		if (visited.get(vertex)) {
			return;
		}
		visited.set(vertex);
		for(std::size_t i = 0; i< size; i++) {
			if (edges[vertex].get(i)) {
				visit_recursive(visited, i);
			}
		}
	}

	bool is_accessible_from(std::size_t vertex) {
		BitVector visited;

		visit_recursive(visited, vertex);

		return visited.is_full(size);

	}



};



int main() {

	BitVector vec;
	vec.set(0);
	vec.set(2);

	vec.print();
	vec.print(3);
	std::cout<<"full(1)="<<vec.is_full(1)<<", full(3)="<<vec.is_full(3)<<std::endl;

	vec.set(2, false);
	vec.print(3);
	std::cout<<"full(1)="<<vec.is_full(1)<<", full(3)="<<vec.is_full(3)<<std::endl;

	vec.set(1);
	vec.set(2);
	vec.print(3);
	std::cout<<"full(1)="<<vec.is_full(1)<<", full(3)="<<vec.is_full(3)<<std::endl;

	Graph graph(4);
	graph.add_edge(0, 1);
	graph.add_edge(2, 3);
	graph.add_edge(1, 3);

	graph.print();


	return 0;
}

}


