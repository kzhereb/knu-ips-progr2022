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
};





int main() {

	BitVector vec;
	vec.set(0);
	vec.set(2);

	vec.print();
	vec.print(3);

	vec.set(2, false);
	vec.print(3);

	return 0;
}

}


