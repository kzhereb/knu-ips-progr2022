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

// returns true if only one output file was written (sorted)
bool merge_runs(std::string in_path1, std::string in_path2, std::string out_path1, std::string out_path2) {
	std::ifstream in_files[] {std::ifstream(in_path1), std::ifstream(in_path2)};
	std::ofstream out_files[] {std::ofstream(out_path1), std::ofstream(out_path2)};
	int previous[] {std::numeric_limits<int>::min(), std::numeric_limits<int>::min()};
	int current[2];
	bool can_read[] {true, true};
	bool file_end[] {false, false};
	std::size_t current_out = 0;

	while(true) {
		in_files[0]>>current[0];
		if (in_files[0].eof()) {
			file_end[0] = true;
			if (file_end[1]) { return false; }
		}
		in_files[1]>>current[1];
		if (in_files[1].eof()) {
			file_end[1] = true;
			if (file_end[0]) { return false; }
		}


		if (current[0] <= previous[0]) {
			can_read[0] = false;
			if (!can_read[1]) {
				current_out++;
				if (current_out > 1) { current_out = 0;}
				can_read[0] = can_read[1] = true;
			}
		}
		if (current[1] <= previous[1]) {
			can_read[1] = false;
			if (!can_read[0]) {
				current_out++;
				if (current_out > 1) { current_out = 0;}
				can_read[0] = can_read[1] = true;
			}
		}
		if (current[0] < current[1]) {
			out_files[current_out]<<current[0]<<" ";
		} else {
			out_files[current_out]<<current[1]<<" ";
		}

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
	merge_runs("example3.txt", "example4.txt", "example1.txt", "example2.txt");

	return 0;
}
}



