#include <iostream>

#include "clientRelated.h"
#include "utilities.h"
#include "menus.h"
#include "agencyClass.h"

#include "packagesRelated.h"

using namespace std;


int main(){

	string agencyFileName;
	string moreActionsAnswer;
	bool moreActions;

	
	cout << "\nWelcome!" << endl;
	
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

		// fix ?
		if (value <= 0 && value > -10) {
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


	
	writeClientsFromVector(clientsFileName, clientsInfoVector);
	writePackagesFromVector(packagesFileName, lastCreated, packagesInfoVector);

	return 0;

}

