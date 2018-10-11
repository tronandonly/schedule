// ConsoleApplication3.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include "Header.h"
#include <fstream>
#include <map>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
//progres is awesome... just need to look into std::bad_alloc at memory location 0x0115EEBC. 8.30

//iterator for while loop
int iter = 0;

std::vector<int> courseNumberVec;
std::map<int, course> courseMap; //map of all courses, keyed by courseNumber
std::map<std::string, student> studentMap; //might be a map off all students keyed by name, not sure if it will ever be necessary to access students in such manner
void readCourses() {
		//importing local files
		std::ifstream ip("courses.csv");
		//variables to get line from
		std::string numOfCourses;
		std::string secC;
		std::string stuC;
		std::string dayM;
		std::string couN;
		std::string teach;
		std::string couNa;
		std::string tempStu;
	//reading the CSV file
	std::getline(ip, numOfCourses, '\n'); //get how many courses we want
	std::cout << "Number of Courses:" << numOfCourses << "\n";
	int intnumOfCourses = std::stoi(numOfCourses, nullptr);//convert into integers
	for (int i = 0; i < intnumOfCourses; i++) {
		iter++;
		std::getline(ip, secC, ',');//look for comma to get the first 6 values
		std::getline(ip, stuC, ',');
		std::getline(ip, dayM, ',');
		std::getline(ip, couN, ',');
		std::getline(ip, teach, ',');
		std::getline(ip, couNa, '\n');//now look for next line

		int intSecC = std::stoi(secC, nullptr);//convert necessary things to integers
		int intStuC = std::stoi(stuC, nullptr);
		int intDayM = std::stoi(dayM, nullptr);
		int intCouN = std::stoi(couN, nullptr);
		course p(intSecC, intStuC, intDayM, intCouN, teach, couNa);//construct a course using ints

		courseMap[p.courseNumber] = p; //insert it into the course map, key it by its number
		courseNumberVec.push_back(p.courseNumber);
		
		courseCount += 1; 
		std::cout << "We have " << iter << " courses processed. " << courseMap[iter].courseName << "\n"; //trouble shooting

	}
}
void readStudents() {
	freePeriod.courseName = "free";
	freePeriod.courseNumber = 0;
	int iterS = 0; // trouble shooting
		std::ifstream ip("students.csv");//import local files
		std::string studentName;
		std::string numberOfStudents;
		std::string coursesTaken;
		std::string tempCourse;
		std::string ID;
		std::string gradYear;
		std::vector<int> tempCourseStorage;
	std::getline(ip, numberOfStudents, '\n');
		int intnumberOfStudents = std::stoi(numberOfStudents, nullptr);
		for (int i = 0; i < intnumberOfStudents; i++) {
			std::getline(ip, studentName, ',');
			student S(5);//declare place holder student
			S.day1Schedule.push_back(freePeriod);
			S.day1Schedule.push_back(freePeriod);
			S.day1Schedule.push_back(freePeriod);
			S.day1Schedule.push_back(freePeriod);
			S.day1Schedule.push_back(freePeriod);
			S.day1Schedule.push_back(freePeriod);
			S.day1Schedule.push_back(freePeriod);
			S.day1Schedule.push_back(freePeriod);
			S.name = studentName; //give it a name
			studentMap[S.name] = S;
			iterS++;
			std::getline(ip, coursesTaken, ','); //figure out courses taken
			int intcoursesTaken = std::stoi(coursesTaken, nullptr); //convert to int
			for (int i = 0; i < intcoursesTaken; i++) {
				std::getline(ip, tempCourse, ',');//add the course to the temp
				int inttempCourse = std::stoi(tempCourse, nullptr);
				tempCourseStorage.push_back(inttempCourse);//push it into the vector
			}
			for (int i = 0; i < tempCourseStorage.size(); ++i) {

				courseMap[tempCourseStorage[i]].students.push_back(S);//pushes each student into the class it belongs in 
				
			}
			


			std::getline(ip, gradYear, '\n');
			tempCourseStorage.clear();
			
		}

}
void checkPeriod(course &checkCourse) {
	//for (int i =0; i <8; ++i)
	//std::cout << studentMap["Sam"].day1Schedule[i].courseName;
	std::vector<int> day1Loc;
	day1Loc.push_back(0);
	day1Loc.push_back(0);
	day1Loc.push_back(0);
	day1Loc.push_back(0);
	day1Loc.push_back(0);
	day1Loc.push_back(0);
	day1Loc.push_back(0);
	day1Loc.push_back(0);
	std::vector<int> periodWork;

	for (int i = 0; i < checkCourse.students.size(); ++i) {//loop through every student
		for (int p = 0; p < 8; ++p) {//loop through every period
			if (checkCourse.students[i].isFree(p) == true) {
				day1Loc[p] += 1;
				std::cout << "Day 1 Period" << p + 1 << " works for " << checkCourse.students[i].name << " they have " << checkCourse.students[i].day1Schedule[p].courseName << "\n";
			}
			else {
				std::cout << "error does not work for" << checkCourse.students[i].name << "\n";
			}
	}
		

	}
	for (int period = 0; period < 8; period++) {
		if (day1Loc[period] == checkCourse.students.size()) {
			std::cout << "Day 1 Period" << period + 1 << " works for " << checkCourse.courseName << "\n";
			periodWork.push_back(period + 1);
			day1Loc[period] = 0;

		}

		else {

			std::cout << "Error: Does not work for all students \n";
		}
	}
	int periodChoose = rand() % periodWork.size() + 1;
	for (int s = 1; s < checkCourse.students.size(); ++s) {
		//checkCourse.students[s].day1Schedule[periodChoose] = *checkCourse;
		checkCourse.students[s].changeClass1(*checkCourse, periodChoose);
		std::cout << "\n" << checkCourse.students[s].name << "has" << checkCourse.courseName << "Period" << periodChoose << "\n";
	 

	}
	
}
void generateSchedule(){
	//create all the day 1 variables
	course courseToCheck = courseMap[courseNumberVec[1]];
	
	checkPeriod(&courseMap[courseNumberVec[0]]);
	//checkPeriod(&courseMap[courseNumberVec[0]]);
	 checkPeriod(&courseMap[courseNumberVec[2]]);

	
	
}
std::vector<int> periodsWork;

int main()
{
//reading CSV files

	readCourses();
	readStudents();
	generateSchedule();

	//checkPeriod(&courseMap[courseNumberVec[2]]);
	
	std::string tacos;//just so this doesnt click us out when we run
	std::cin >> tacos;
	
    return 0;
};

