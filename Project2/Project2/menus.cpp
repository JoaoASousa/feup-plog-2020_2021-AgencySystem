#include <iostream>
#include <vector>

#include "menus.h"

using namespace std;

// IR ATUALIZANDO À MEDIDA QUE SE VAI ADICIONANDO FUNCIONALIDADES AO MENU
vector<int> menuOptions = { 0, 1, 2 };


int mainMenu() {

	bool menuFailFlags;
	int operationSelector;

	do {
		menuFailFlags = false;

		cout << "\nMain Menu\n" << endl;

		cout << "  1. Agency Information" << endl;
		cout << "  2. Packages" << endl;
		cout << "  0. Quit" << endl;

		cout << endl;

		cout << "Please insert the corresponding number: ";
		cin >> operationSelector;

		if ((cin.fail()) || (count(menuOptions.begin(), menuOptions.end(), operationSelector) == 0)) {

			if (cin.eof()) {
				cout << "\nStopping the program . . ." << endl;
				return -1;
			}

			menuFailFlags = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		cout << "\x1B[2J\x1B[H";
		
	} while (menuFailFlags);

	return operationSelector;
}