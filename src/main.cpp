#include <iostream>
#include "data.h"

using namespace std;

int main()

{
	char ch;

	while (1) {

		UserData ud;

		system("clear");

		ud.welcome();

		userChoice:

		cout << "Continue? [y/n]: ";
		cin >> ch;

		if (ch == 'n') {

			system("clear");
			ud.welcome();

			break;
		}

		else if (ch == 'y') {

			ud.~UserData();
			continue;
		}

		else {

			cout << "Invalid Selection!!";
			goto userChoice;
		}
	}

	return 0;
}