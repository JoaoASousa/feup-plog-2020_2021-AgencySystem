#include <iostream>

#include "agencyClass.h"
#include "menus.h"
#include "utilities.h"

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
	

	Agency newAgency(agencyFileName);
	
	do {
		switch (mainMenu()) {

			case 0:
				return 0;

			case 1:
				newAgency.displayAgencyInfo(newAgency);
				break;


			default:
				cout << "Invalid Option" << endl;
				
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

