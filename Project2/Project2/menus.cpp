#include <iostream>
#include <vector>

#include "menus.h"

using namespace std;

// IR ATUALIZANDO À MEDIDA QUE SE VAI ADICIONANDO FUNCIONALIDADES AO MENU
vector<int> menuOptions = { 0, 1, 2 };


int mainMenu() {

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
				cout << "\nStopping the program . . ." << endl;
				return -1;
			}

			mainMenuFailFlags = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		cout << "\x1B[2J\x1B[H";
		
	} while (mainMenuFailFlags);

	return mainOperationSelector;
}


int packageMenu() {

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

	return packageOperationSelector;
}