/*
 * pi12_20220224_sort_file.cpp
 *
 *  Created on: Feb 24, 2022
 *      Author: KZ
 */

#include <fstream>
#include <string>
#include <limits>

namespace pi12_20220224_sort_file {

void split_into_runs(std::string in_path, std::string out_path1, std::string out_path2) {
	std::ifstream in_file(in_path);
	std::ofstream out_files[] {std::ofstream(out_path1), std::ofstream(out_path2)};
	std::size_t current_out = 0;
	int current;
	int previous = std::numeric_limits<int>::min();
	while(true) {
		in_file>>current;
		if (in_file.eof()) {break;}
		if (current > previous) {
			out_files[current_out] << current<<" ";
		} else {
			current_out++;
			if (current_out > 1) { current_out = 0;}
			out_files[current_out] << current<<" ";
		}
		previous = current;
	}
}

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

	split_into_runs("example.txt", "example3.txt", "example4.txt");

	return 0;
}
}



