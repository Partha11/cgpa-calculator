#ifndef DATA_H
#define DATA_H

#include <sys/ioctl.h>
#include <cstdio>
#include <string>

static const std::string subName[200][8] = {

		{"Introduction To Computer System(CSE-111)", "Programming Language(CSE-112)", "Physics(CSE-114)", "Differential Calculus And Geometry(CSE-115)", "English(CSE-116)"},

		{"Data Structure(CSE-121)", "Introduction to Electrical Engineering(CSE-123)", "Integral Calculus And Differential(CSE-125)", "Statistics And Probability(CSE-126)", "Discrete Mathematics(CSE-127)"},

		{"Object Oriented Programming(CSE-211)", "Operating System(CSE-213)", "Digital Logic Design(CSE-214)", "Mathematics For CSE(CSE-216)", "Electronic Device And Circuits(CSE-217)", "Basic Accounting(CSE-219)"},

		{"Algorithm Design(CSE-221)", "Database Management System(CSE-223)", "Computer Organization and Architecture(CSE-225)", "Data Communication(CSE-226)", "Economics(CSE-227)"},

		{"Theory Of Computation(CSE-311)", "Microprocessor and Assembly Language(CSE-312)", "Engineering Mathematics(CSE-314)", "Sociology(CSE-315)", "Technical Writing and Communication(CSE-316)"},

		{"Software Engineering(CSE-321)", "Numerical Analysis(CSE-323)", "Computer Graphics(CSE-324)", "Compiler Design(CSE-326)", "System Analysis(CSE-328)"},

		{"Computer Networking(CSE-411)", "A.I. and Neural Network(CSE-413)", "Parallel and Distributed Processing(CSE-414)", "Peripheral and Interfacing(CSE-415)", "Digital Signal Processing(CSE-417)"},

		{"Web Engineering(CSE-421)", "Computer Network and Security(CSE-423)", "Elective Course(CSE-42x)", "Project(CSE-429)"}
	};

static const std::string pracName[200][10] = {

		{"Programming Language Practical(CSE-113)"},

		{"Data Structure Practical(CSE-122)", "Introduction to Electrical Engineering Practical(CSE-124)"},

		{"OOP Practical(CSE-212)", "Digital Logic Design Practical(CSE-215)", "Electronic Device And Circuits Practical(CSE-218)"},

		{"Algorithm Design Practical(CSE-222)", "Database Management System Practical(CSE-224)"},

		{"Assembly Language Practical(CSE-313)"},

		{"Software Engineering Practical(CSE-322)", "Computer Graphics Practical(CSE-325)", "Compiler Design Practical(CSE-327)"},

		{"Computer Networking Practical(CSE-412)", "Peripheral and Interfacing Practical(CSE-416)"},

		{"Web Engineering Practical(CSE-422)"}
	};

static const int subjectNumber[8] = {5, 5, 6, 5, 5, 5, 5, 4};
static const int practicalNumber[8] = {1, 2, 3, 2, 1, 3, 2, 1};
static const double grades[8] = {16.5, 18, 22.5, 18, 16.5, 19.5, 18, 13.5};

const std::string blue("\033[1;36m");
const std::string cyan("\033[1;34m");
const std::string yellow("\033[1;33m");
const std::string red("\033[1;42m");
const std::string redb("\033[1;31m");
const std::string magenta("\033[1;35m");
const std::string reset("\033[0m");

class UserData {

private:

	struct winsize w;

	std::string userGrade;
	double totalObtained;
	double res;
	int semester;
	char choice;

	enum grade {a_plus, a, a_minus, b_plus, b, b_minus, c_plus, c, d, f};

public:

	UserData();
	void welcome();
	void menu();
	void printResult();
	void subjectInput();
	int selectSemester();
	void showSubjects();
	void userSelection(int sem);
	int maxLength();
	int findLength(int row, int col, bool isPractical);
	void loop(int n, char ch);
	double calculateGrade(std::string Grade, bool isPractical);
	void result(double totalMarks, int sem);
	~UserData();
};

#endif