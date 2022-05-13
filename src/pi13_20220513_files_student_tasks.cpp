/*
 * pi13_20220513_files_student_tasks.cpp
 *
 *  Created on: May 13, 2022
 *      Author: KZ
 */

#include <string>
#include <vector>
#include <iostream>

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

void print_type(TaskType type) {
	switch (type)
	  {
	  case 1:
		std::cout << "MultipleChoice" << "  ";
		break;
	  case 2:
		std::cout << "Code" << "  ";
		break;
	  case 3:
		std::cout << "FreeFormText" << "  ";
		break;
	  case 4:
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
		std::cout<<"Type: ";//<<type<<"\n";
		print_type(type);
		std::cout<<"\n";
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


int main() {

	MemoryStorage memory;
	StudentTask task1 {"MyTask","Ivan Petrenko", DateTime(2022, 5, 13, 11, 55, 2), FreeFormText, 5.5};
	memory.add(task1);

	memory.add({"1: a, 2:c, 3:d", "Ivan Petrenko", {2022, 5, 13, 12, 0, 0}, MultipleChoice, 2.1});


	memory.print();

	return 0;
}
}



