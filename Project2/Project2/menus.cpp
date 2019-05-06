#include <iostream>
#include <vector>
#include <cmath>

#include "utilities.h"

#include "menus.h"

using namespace std;

// IR ATUALIZANDO À MEDIDA QUE SE VAI ADICIONANDO FUNCIONALIDADES AO MENU
vector<int> menuOptions = { 0, 1, 2 };


int mainMenu(Agency agency) {

	bool mainMenuFailFlags;
	int mainOperationSelector;
	
	do {
		mainMenuFailFlags = false;

		cout << "\nMain Menu\n" << endl;

		cout << "  1. Agency" << endl;
		cout << "  2. Packages" << endl;
		cout << "  0. Quit" << endl;

		cout << endl;

		cout << "Please insert the corresponding number: ";
		cin >> mainOperationSelector;

		if ((cin.fail()) || (count(menuOptions.begin(), menuOptions.end(), mainOperationSelector) == 0)) {

			if (cin.eof()) {
				// cout << "\nStopping the program . . ." << endl;
				return -1;
			}

			mainMenuFailFlags = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		cout << "\x1B[2J\x1B[H";
		
	} while (mainMenuFailFlags);
	
	
	int goBack = -1;

	switch (mainOperationSelector) {

		case 1:
			cout << agency << endl;
			break;

		case 2:
			goBack = packageMenu(agency);
			break;

		default:
			break;
	}

	if (goBack == 0) {
		if (mainMenu(agency) == 0) {
			return -1;
		};

	}

	return mainOperationSelector;
}


int packageMenu(Agency agency) {

	bool packageMenuFailFlags;
	int packageOperationSelector;

	do {
		packageMenuFailFlags = false;

		cout << "\nPackage Menu\n" << endl;

		cout << "  1. Display All Packages" << endl;
		cout << "  2. Display a Package of choice" << endl;
		cout << "  0. Go back to Main Menu" << endl;

		cout << endl;

		cout << "Please insert the corresponding number: ";
		cin >> packageOperationSelector;

		if ((cin.fail()) || (count(menuOptions.begin(), menuOptions.end(), packageOperationSelector) == 0)) {

			if (cin.eof()) {
				cout << "\nStopping the program . . ." << endl;
				return -1;
			}

			packageMenuFailFlags = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		cout << "\x1B[2J\x1B[H";

	} while (packageMenuFailFlags);



	vector <int> packageNumbers;

	switch (packageOperationSelector) {

		case 1:
			for (int i = 0; i < packagesInfo(agency.getPackagesFile()).size(); i++) {
				cout << packagesInfo(agency.getPackagesFile()).at(i) << endl;
				cout << endl;
			}

		case 2:
			for (int i = 0; i < packagesInfo(agency.getPackagesFile()).size(); i++) {
				cout << "Package #" << abs(packagesInfo(agency.getPackagesFile()).at(i).getId()) << " (" << packagesInfo(agency.getPackagesFile()).at(i).getPlaces().at(0) << ")";
				if (packagesInfo(agency.getPackagesFile()).at(i).getId() < 0) {
					cout << "\t[Unavailable Package]";
				}
				cout << endl;
			}

			cout << "\nPlease insert the corresponding number: ";
			//cin >>

	}


	return packageOperationSelector;
}