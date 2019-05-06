#include <iostream>

#include "utilities.h"
#include "menus.h"
#include "agencyClass.h"

using namespace std;


int main(){

	string agencyFileName;
	string moreActionsAnswer;
	bool moreActions;


	cout << "Welcome!" << endl;

	do {
		cout << "Please insert the name of the Agency's File: ";
		cin >> agencyFileName;

		cin.ignore(1000, '\n');
		cin.clear();

	} while (!validAgencyFile(agencyFileName));

	cout << "\x1B[2J\x1B[H";

	Agency agency(agencyFileName);
	int value;
	do {
		moreActions = false;
		
		value = mainMenu(agency);

		if (value <= 0) {
			return 0;
		}

		

		
		cout << "\nMore Actions ? [Y/N] ";
		cin >> moreActionsAnswer;

		if (moreActionsAnswer == "YES" || moreActionsAnswer == "Yes" || moreActionsAnswer == "yes" || moreActionsAnswer == "Y" || moreActionsAnswer == "y") {
			moreActions = true;
		}

		cout << "\x1B[2J\x1B[H";

	} while (moreActions);


	return 0;

}

