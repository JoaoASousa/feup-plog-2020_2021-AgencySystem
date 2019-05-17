#include <iostream>

#include "clientRelated.h"
#include "utilities.h"
#include "menus.h"
#include "agencyClass.h"

#include "packagesRelated.h"

using namespace std;

// cout << "\x1B[2J\x1B[H";  --> used to "clear the screen"
// functions related to operations such as "Display All the Packages" return 0 in order to go back a menu; else return -1

int main(){

	string agencyFileName;
	string moreActionsAnswer;
	bool moreActions;

	
	cout << "\nWelcome!\n" << endl;
	
	cout << "You may input '0' (zero) or press Control + z at any time to either go to the previous menu or to quit the program." << endl << endl;

	do {
		cout << "Please insert the name of the Agency's File: ";
		cin >> agencyFileName;

		if (agencyFileName == to_string(0)) {
			return 0;
		}

		if (cin.fail()) {
			if (cin.eof()) {
				return 0;
			}
		}

		cin.clear();
		cin.ignore(1000, '\n');

	} while (!validAgencyFile(agencyFileName));

	cout << "\x1B[2J\x1B[H";

	Agency agency(agencyFileName);

	vector<Client> clientsInfoVector = clientsInfo(agency);
	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	string clientsFileName = agency.getClientsFile();
	string packagesFileName = agency.getPackagesFile();

	string textLine;
	int lastCreated;
	ifstream packagesFile(packagesFileName);

	bool firstLine = true;

	while (getline(packagesFile, textLine)) {

		if (firstLine) {
			lastCreated = abs(stoi(textLine));
			firstLine = false;
			break;
		}
	}

	packagesFile.close();

	int value;

	
	do {
		moreActions = false;
		
		value = mainMenu(agency, clientsInfoVector, packagesInfoVector, lastCreated);

		if (value <= 0 && value > -10) {
			// updating the information in the files
			writeClientsFromVector(clientsFileName, clientsInfoVector);
			writePackagesFromVector(packagesFileName, lastCreated, packagesInfoVector);
			return 0;
		}
		
		cout << "\nMore Actions ? [Y/N] ";
		cin >> moreActionsAnswer;

		if (moreActionsAnswer == "YES" || moreActionsAnswer == "Yes" || moreActionsAnswer == "yes" || moreActionsAnswer == "Y" || moreActionsAnswer == "y") {
			moreActions = true;
		}

		cout << "\x1B[2J\x1B[H";

	} while (moreActions);


	// updating the information in the files 
	writeClientsFromVector(clientsFileName, clientsInfoVector);
	writePackagesFromVector(packagesFileName, lastCreated, packagesInfoVector);

	return 0;

}
