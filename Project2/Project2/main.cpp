#include <iostream>

#include "agencyClass.h"
#include "menus.h"

using namespace std;


int main(){

	string agencyFileName;
	bool x;

	cout << "Welcome!" << endl;
	cout << "Please insert the name of the Agency's File: ";
	cin >> agencyFileName;

	cin.ignore(1000, '\n');
	cin.clear();

	Agency newAgency(agencyFileName);
	

	if (!(newAgency.getAgencyNameStatus())) {

		do {
			cout << "Invalid File Name." << endl;
			cout << "Please insert the name of the Agency's File: ";
			cin >> agencyFileName;

			cin.ignore(1000, '\n');
			cin.clear();
			cout << "Valid? " << newAgency.getAgencyNameStatus() << endl;
			Agency newAgency(agencyFileName);
			x = newAgency.getAgencyNameStatus() ;
		} while (!x);
	}

	switch (mainMenu()) {
		case 1:
			newAgency.displayAgencyInfo(newAgency);
			break;

		default:
			cout << "idk yet" << endl;
			break;
	}
	
}

