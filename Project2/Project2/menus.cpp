#include <iostream>
#include <vector>
#include <cmath>

#include "utilities.h"

#include "menus.h"

using namespace std;

// IR ATUALIZANDO À MEDIDA QUE SE VAI ADICIONANDO FUNCIONALIDADES AO MENU
vector<int> mainMenuOptions = { 0, 1, 2 };
vector<int> packageMenuOptions = { 0,1,2 };


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

		if ((cin.fail()) || (count(mainMenuOptions.begin(), mainMenuOptions.end(), mainOperationSelector) == 0)) {

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

	bool flag = false;

	switch (mainOperationSelector) {

		case 1:
			cout << agency << endl;
			break;

		case 2:
			// goBack = packageMenu(agency);
			do {
				switch (packageMenu(agency)) {
					flag = false;
					case 0:
						if (mainMenu(agency) == 0) {
							return 0;
						}

					case 1:
						packageDisplayAll(agency);
						break;

					case 2:
						switch (packageDisplayOne(agency)) {
							case 0:
								flag = true;
						}

				}
				
			} while (flag);
			break;

		default:
			break;
	}

	/*if (goBack == 0) {
		if (mainMenu(agency) == 0) {
			return -1;
		};

	}*/

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

		if ((cin.fail()) || (count(packageMenuOptions.begin(), packageMenuOptions.end(), packageOperationSelector) == 0)) {

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

	return packageOperationSelector;

}

void packageDisplayAll(Agency agency) {

	vector <int> packageNumbers;
	int packageSelection;

	for (int i = 0; i < packagesInfo(agency.getPackagesFile()).size(); i++) {

		cout << packagesInfo(agency.getPackagesFile()).at(i) << endl;
		cout << endl;

	}
}


int packageDisplayOne(Agency agency) {
	bool packageSelectorFailFlag = false;
	vector <int> packageNumbers;
	int packageSelection;

	do {
		packageSelectorFailFlag = false;
		for (int i = 0; i < packagesInfo(agency.getPackagesFile()).size(); i++) {

			cout << "Package #" << abs(packagesInfo(agency.getPackagesFile()).at(i).getId()) << " ("
				<< packagesInfo(agency.getPackagesFile()).at(i).getPlaces().at(0) << ")";

			packageNumbers.push_back(abs(packagesInfo(agency.getPackagesFile()).at(i).getId()));

			if (packagesInfo(agency.getPackagesFile()).at(i).getId() < 0) {
				cout << "\t[Unavailable Package]";
			}
			cout << endl;
		}

		cout << "\nPlease insert the corresponding number: ";
		cin >> packageSelection;

		cout << "\x1B[2J\x1B[H";

		if (packageSelection == 0) {
			return 0;
		}

		if ((cin.fail()) || (count(packageNumbers.begin(), packageNumbers.end(), packageSelection) == 0)) {

			if (cin.eof()) {
				cout << "\nStopping the program . . ." << endl;
				return 0;
			}

			packageSelectorFailFlag = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		cout << "\x1B[2J\x1B[H";

	} while (packageSelectorFailFlag);

	cout << packagesInfo(agency.getPackagesFile()).at(packageSelection - 1) << endl;

	return -1;
}