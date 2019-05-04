#include <iostream>
#include "agencyClass.h"

using namespace std;


int main(){

	string agencyFileName;


	cout << "Welcome!" << endl;
	cout << "Please insert the name of the Agency's File: ";
	cin >> agencyFileName;

	cin.ignore(1000, '\n');
	cin.clear();
	
	Agency newAgency(agencyFileName);
	
	/*
	if (true) {

		do {
			cout << "Invalid File Name." << endl;
			cout << "Please insert the name of the Agency's File: ";
			cin >> agencyFileName;

			cin.ignore(1000, '\n');
			cin.clear();
			Agency newAgency(agencyFileName);

		} while (false);
	}

	cout << "Agency Name: " << newAgency.getName() << endl;
	cout << "Agency NIF: " << newAgency.getNif() << endl;
	cout << "Agency Url: " << newAgency.getUrl() << endl;
	cout << "Agency's Clients File Name: " << newAgency.getClientsFile() << endl;
	cout << "Agency's Packages File Name: " << newAgency.getPackagesFile() << endl;
	*/
}

