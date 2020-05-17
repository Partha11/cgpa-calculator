#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>
#include <fstream>
#include <sys/ioctl.h>
#include <cstdio>
#include <termcolor/termcolor.hpp>
#include "data.h"

UserData::UserData() {

	totalObtained = 0;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	menu();
}

void UserData::welcome() {

	system("clear");

	std::cout.flush();

	std::string str1 = "Welcome";
	std::string str2 = "To CGPA Calculator";

	loop(w.ws_col / 2 - (40 / 2), ' ');
	loop(40, '-');

	std::cout << "\n";
	
	loop(w.ws_col / 2 - (40 / 2), ' ');

	std::cout << "-" << termcolor::on_grey;
	
	loop(19 - (str1.length() / 2), ' ');

	std::cout << termcolor::blue << str1;
	
	loop(19 - (str1.length() / 2) - 1, ' ');

	std::cout << termcolor::reset << "-\n";

	loop(w.ws_col / 2 - (40 / 2), ' ');

	std::cout << "-" << termcolor::on_grey;
	
	loop(19 - (str2.length() / 2), ' ');

	std::cout << termcolor::blue << str2;
	
	loop(19 - (str2.length() / 2), ' ');

	std::cout << termcolor::reset << "-\n";
	
	loop(w.ws_col / 2 - (40 / 2), ' ');
	loop(40, '-');

	std::cout << "\n\n\n\n";
}

int UserData::maxLength() {

	int maxL(0), curr;

	for (int i = 0; i < 8; i++) {

		for (int j = 0; j < subjectNumber[i]; j++) {

			curr = subName[i][j].length();

			if (curr > maxL) {

				maxL = curr;
			}
		}
	}

	for (int i = 0; i < 8; i++) {

		for (int j = 0; j < practicalNumber[i]; j++) {

			curr = pracName[i][j].length();

			if (curr > maxL) {

				maxL = curr;
			}
		}
	}

	return maxL;
}

int UserData::findLength(int row, int col, bool isPractical) {

	if (!isPractical)

		return subName[row][col].length();

	else

		return pracName[row][col].length();
}

int UserData::selectSemester() {

	semSelection:

	std::string tmpSem;

	system("clear");
	welcome();

	std::cout << "Enter Semester = ";
	std::cin >> tmpSem;

	if (tmpSem[0] < '1' || tmpSem[0] > '8' || tmpSem.length() > 1) {

		std::cout << termcolor::red << "Invalid Semester!!" << termcolor::reset << std::endl;
		std::cout << "Please Wait";

		for (int i = 0; i < 4; i++) {

			std::cout << ".";
			std::cout.flush();
			usleep(500000);
		}

		system("clear");
		tmpSem.erase(tmpSem.begin(), tmpSem.end());
		
		goto semSelection;
	}

	else {

		semester = tmpSem[0] - 48;

		std::cout.flush();

		return semester;
	}
}

void UserData::loop(int n, char ch) {

	for (int i = 0; i < n; i++) {

		std::cout.flush();
		std::cout << ch;
	}
}

void UserData::subjectInput() {

	system("clear");

	int sem = selectSemester();

	userSelection(sem);

	std::string temp;
	double tmp;

	usleep(100000);
	system("clear");
	welcome();

	for (int i = 0; i < subjectNumber[sem - 1]; i++) {

		std::cout << termcolor::blue << subName[sem - 1][i] << ": " << termcolor::reset;
		std::cin >> temp;

		tmp = calculateGrade(temp, false);

		if (tmp == -99) {

			std::cout << termcolor::red << "Invalid Grade!!" << termcolor::reset << std::endl;
			--i;
			continue;
		}

		else

			totalObtained += tmp;
	}

	for (int i = 0; i < practicalNumber[sem - 1]; i++) {

		std::cout << termcolor::green << pracName[sem - 1][i] << ": " << termcolor::reset;
		std::cin >> temp;

		tmp = calculateGrade(temp, true);

		if (tmp == -99) {

			std::cout << termcolor::red << "Invalid Grade!!" << termcolor::reset << std::endl;
			--i;
			continue;
		}

		else

			totalObtained += tmp;
	}

	result(totalObtained, sem);

	//std::cout << totalObtained << std::endl;
}

void UserData::userSelection(int sem) {

	std::string num;

	num = (sem == 1) ? "st" : (sem == 2) ? "nd" : (sem == 3) ? "rd" : "th";

	std::cout << "You Have Selected " << termcolor::green << sem << num << termcolor::reset << " Semester" << std::endl;
	std::cout << "Loading";

	for (int i = 0; i < 4; i++) {

		std::cout << ".";
		std::cout.flush();
		usleep(500000);
	}
}

void UserData::showSubjects() {

	system("clear");
	welcome();

	int sem = selectSemester();

	userSelection(sem);

	system("clear");
	welcome();

	int l = maxLength();

	loop(w.ws_col / 2 - l / 2 - 1, ' ');

	std::cout << "/";

	loop(l + 2, '-');

	std::cout << "\\\n";

	for (int i = 0, j = 0; i < subjectNumber[sem - 1] + practicalNumber[sem - 1]; i++) {

		loop(w.ws_col / 2 - l / 2 - 1, ' ');

		std::cout << "| ";

		if (i < subjectNumber[sem - 1]) {

			std::cout << termcolor::cyan << subName[sem - 1][i] << termcolor::reset;

			int tmp_l = findLength(sem - 1, i, false);

			loop(l - tmp_l + 1, ' ');

			std::cout << "|\n";
		}

		else {

			std::cout << termcolor::magenta << pracName[sem - 1][j] << termcolor::reset;

			int tmp_l = findLength(sem - 1, j, true);

			loop(l - tmp_l + 1, ' ');

			std::cout << "|\n";

			j++;
		}

		usleep(1000000);
	}

	loop(w.ws_col / 2 - l / 2 - 1, ' ');

	std::cout << "\\";

	loop(l + 2, '-');

	std::cout << "/\n";

	std::cout << "\n\n\n";
	std::cin.ignore(1024, '\n');
	std::cout << "Press enter key to continue..";
	std::cin.get();

	menu();
}

double UserData::calculateGrade(std::string Grade, bool isPractical) {

	double multiplier, temp;

	if (!isPractical)

		multiplier = 3;

	else

		multiplier = 1.5;

	if (Grade == "A+" || Grade == "a+")

		temp = 4 * multiplier;

	else if (Grade == "A" || Grade == "a")

		temp = 3.75 * multiplier;

	else if (Grade == "A-" || Grade == "a-")

		temp = 3.50 * multiplier;

	else if (Grade == "B+" || Grade == "b+")

		temp = 3.25 * multiplier;

	else if (Grade == "B" || Grade == "b")

		temp = 3 * multiplier;

	else if (Grade == "B-" || Grade == "b-")

		temp = 2.75 * multiplier;

	else if (Grade == "C+" || Grade == "c+")

		temp = 2.5 * multiplier;

	else if (Grade == "C" || Grade == "c")

		temp = 2.25 * multiplier;

	else if (Grade == "D" || Grade == "d")

		temp = 2 * multiplier;

	else if (Grade == "F" || Grade == "f")

		temp = 0;

	else

		temp = -99;

	return temp;
}

void UserData::result(double totalMarks, int sem) {

	res = totalMarks / grades[sem - 1];

	printResult();
}

UserData::~UserData() {

	totalObtained = 0.0;
	userGrade = " ";
}

void UserData::printResult() {

	std::string cgpa = "Your CGPA Is- ";

	loop(3, '\n');
	loop(w.ws_col / 2 - (40 / 2), ' ');
	loop(40, '-');

	std::cout << "\n";
	
	loop(w.ws_col / 2 - (40 / 2), ' ');

	std::cout << "-" << termcolor::on_grey;

	loop(19 - (cgpa.length() / 2) - 2, ' ');

	if (res > 3)

		std::cout << termcolor::green << cgpa << std::fixed << std::setprecision(2) << res;

	else

		std::cout << termcolor::red << cgpa << std::fixed << std::setprecision(2) << res;

	loop(19 - (cgpa.length() / 2) - 2, ' ');

	std::cout << termcolor::reset << "-\n";

	loop(w.ws_col / 2 - (40 / 2), ' ');
	loop(40, '-');

	std::cout << "\n\n\n";
	std::cin.ignore(1024, '\n');
	std::cout << "Press enter key to continue..";
	std::cin.get();
}

void UserData::menu() {

	mainMenu:

	welcome();

	std::cout << termcolor::cyan << "1.Calculate CGPA" << termcolor::reset << std::endl;
	std::cout << termcolor::yellow << "2.View Subjects" << termcolor::reset << std::endl;
	std::cout << termcolor::yellow << "3.About" << termcolor::reset << std::endl;
	std::cout << termcolor::red << "4.Quit" << termcolor::reset << std::endl;
	std::cout << std::endl;
	std::cout << termcolor::green << "Enter Selection: " << termcolor::reset;

	std::cin >> choice;

	if (choice < '1' || choice > '4') {

		std::cout << termcolor::red << "Invalid Selection!!" << termcolor::reset << std::endl;
		std::cout << "Please Wait";

		for (int i = 0; i < 4; i++) {

			std::cout << ".";
			std::cout.flush();
			usleep(500000);
		}

		goto mainMenu;
	}

	else {

		switch (choice) {

			case '1':

				subjectInput();
				break;

			case '2':

				showSubjects();
				break;

			case '3':

				aboutCalc();

				break;

			case '4':

				system("clear");
				exit(EXIT_SUCCESS);
				break;
		}
	}
}

void UserData::aboutCalc() {

	system("clear");
	welcome();

	std::string credits[5] = {"CGPA Calculator v2.1 alpha",
							  "Coded By Partha",
							  "For Any Suggestions/Help,",
							  "Please Contact http://fb.com/abir.partha.5"};

	int stringLength;

	std::cout << "\n\n";

	for (int i = 0, j = 0; i < 4; i++) {

		stringLength = credits[i].length();

		loop((w.ws_col / 2) - (stringLength / 2 + 1), ' ');

		switch (i) {

			case 0:

				std::cout << termcolor::cyan;

				break;

			case 1:

				std::cout << termcolor::green;

				break;

			case 2:

				std::cout << termcolor::yellow;

				break;

			case 3:

				std::cout << termcolor::red;

				break;
		}

		for (int j = 0; j < credits[i].length(); j++) {

			std::cout.flush();

			std::cout << credits[i][j];
			usleep(100000);
		}

		std::cout << termcolor::reset;
		std::cout << "\n";
	}

	std::cout << "\n\n\n\n";
	std::cin.ignore(1024, '\n');
	std::cout << "Press enter key to continue..";
	std::cin.get();

	menu();
}