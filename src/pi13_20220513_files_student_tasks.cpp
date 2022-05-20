/*
 * pi13_20220513_files_student_tasks.cpp
 *
 *  Created on: May 13, 2022
 *      Author: KZ
 */

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>

namespace pi13_20220513_files_student_tasks {

// Working with files (similar to lab1 variant 5)
// Student tasks:
// text of completed task
// author
// date and time when it was sent
// type of task: multiple choice, code, free-form text, link to cloud storage
// evaluation result (real number, range from 0 to 10)

// queries:
// 1) tasks that contain text fragment
// 2) tasks with result in given range and from a given author
// 3) tasks with given type sent before given time

struct DateTime {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

	DateTime(int year=2020, int month=1, int day=1, int hour=0, int minute=0, int second=0) {
		this->year = year;
		this->month = month;
		this->day = day;
		this->hour = hour;
		this->minute = minute;
		this->second = second;
	}

	void print() {
		std::cout<<year<<"."<<month<<"."<<day<<" "<<hour<<":"<<minute<<":"<<second;
	}
};

enum TaskType {
	MultipleChoice=1,
	Code,
	FreeFormText,
	LinkToCloudStorage
};

std::string type_to_string(TaskType type) {
	switch (type) {
	case MultipleChoice:
		return "MultipleChoice";
	case Code:
		return "Code";
	case FreeFormText:
		return "FreeFormText";
	case LinkToCloudStorage:
		return "LinkToCloudStorage";
	default:
		assert(false); //should be unreachable
		return "Unknown";
	}
}

void print_type(TaskType type) {
	switch (type) {
	case MultipleChoice:
		std::cout << "MultipleChoice" << "  ";
		break;
	case Code:
		std::cout << "Code" << "  ";
		break;
	case FreeFormText:
		std::cout << "FreeFormText" << "  ";
		break;
	case LinkToCloudStorage:
		std::cout << "LinkToCloudStorage" << "  ";
		break;
	}
}



struct StudentTask {
	std::string text;
	std::string author;
	DateTime sent_time;
	//int sent_timestamp; // seconds from some fixed date
	TaskType type;
	float evaluation_result;

	StudentTask(std::string text, std::string author, DateTime sent_time, TaskType type, float evaluation_result) {
		this->text = text;
		this->author = author;
		this->sent_time = sent_time;
		this->type = type;
		this->evaluation_result = evaluation_result;
	}

	void print() {
		std::cout<<"Text: "<<text<<"\n";
		std::cout<<"Author: "<<author<<"\n";
		std::cout<<"Sent time: ";		//sent_time<<"\n";
		sent_time.print();
		std::cout<<"\n";
		std::cout<<"Type: "<<type_to_string(type)<<"\n";
		std::cout<<"Evaluation result: "<<evaluation_result<<std::endl;
	}
};

struct MemoryStorage {
	std::vector<StudentTask> tasks;

	void add(StudentTask task) {
		tasks.push_back(task);
	}

	void print() {
		std::cout<<"Total number of tasks stored: "<<tasks.size()<<std::endl;
		for(auto& task: tasks) {
			task.print();
			std::cout<<std::endl;
		}

	}
};

void write_binary(std::ofstream& out, int value) {
	out.write(reinterpret_cast<char*>(&value), sizeof value);
}

void write_binary(std::ofstream& out, float value) {
	out.write(reinterpret_cast<char*>(&value), sizeof value);
}

void write_binary(std::ofstream& out, std::string value) {
	out<<value<<'\0';
}

int read_binary_int(std::ifstream& infile) {
	int value;
	infile.read(reinterpret_cast<char*>(&value), sizeof value);
	return value;
}

float read_binary_float(std::ifstream& infile) {
	float value;
	infile.read(reinterpret_cast<char*>(&value), sizeof value);
	return value;
}

struct BinaryFileStorage {
	MemoryStorage in_memory;
	std::string filename;

	BinaryFileStorage(std::string filename) {
		this->filename = filename;
	}

	void add(StudentTask task) {
		in_memory.add(task);
	}

	void print() {
		in_memory.print();
	}

	void save() {
		std::ofstream outfile {filename, std::ios::binary};



		for(auto& task: in_memory.tasks) {
			write_binary(outfile, task.text);
			write_binary(outfile, task.author);

			write_binary(outfile, task.sent_time.year);
			write_binary(outfile, task.sent_time.month);
			write_binary(outfile, task.sent_time.day);
			write_binary(outfile, task.sent_time.hour);
			write_binary(outfile, task.sent_time.minute);
			write_binary(outfile, task.sent_time.second);

			write_binary(outfile, task.type);
			write_binary(outfile, task.evaluation_result);
		}

		outfile.flush();
	}


};


int main() {

	MemoryStorage memory;
	StudentTask task1 {"MyTask","Ivan Petrenko", DateTime(2022, 5, 13, 11, 55, 2), FreeFormText, 5.5};
	memory.add(task1);

	memory.add({"1: a, 2:c, 3:d", "Ivan Petrenko", {2022, 5, 13, 12, 0, 0}, MultipleChoice, 2.1});


	memory.print();

	BinaryFileStorage binary{"tasks.bin"};
	binary.add(task1);
	binary.add({"1: a, 2:c, 3:d", "Ivan Petrenko", {2020, 5, 13, 12, 0, 0}, MultipleChoice, 2.1});

	binary.print();
	binary.save();
	std::cout<<"binary file saved to "<<binary.filename<<std::endl;

	std::ofstream outfile{"test.bin"};
	write_binary(outfile, 1256);
	write_binary(outfile, 1.23f);
	outfile.flush();

	std::ifstream infile{"test.bin"};
	std::cout<<read_binary_int(infile)<<" "<<read_binary_float(infile);


	return 0;
}
}



