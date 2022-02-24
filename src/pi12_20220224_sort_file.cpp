/*
 * pi12_20220224_sort_file.cpp
 *
 *  Created on: Feb 24, 2022
 *      Author: KZ
 */

#include <fstream>
#include <string>

namespace pi12_20220224_sort_file {

void sort_file(std::string file_path) {

}

void generate_example_file(std::string file_path) {
	// from lecture slides
	int array[] {2, 8, 3, 7, 6, 5, 3, 4, 1};
	std::ofstream out_file(file_path);
	for (std::size_t i = 0; i< sizeof(array)/sizeof(int); i++) {
		out_file<<array[i]<<" ";
	}
	out_file.close();


}


int main() {
	std::string file_path = "example.txt";
	generate_example_file(file_path);

	return 0;
}
}



