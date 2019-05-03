#include <iostream>
#include <vector>

#include "menus.h"

using namespace std;

// IR ATUALIZANDO
vector<int> menuOptions = { 1 };

int mainMenu() {

	bool menuFailFlags;

	int operationSelector;


	do {

		cout << "\nMain Menu\n" << endl;
		cout << "  1. Agency Information" << endl;
		


		cout << endl;

		menuFailFlags = false;
		cout << "Please insert the corresponding number: (control + z to quit) ";
		cin >> operationSelector;


		
		if ((cin.fail()) || (count(menuOptions.begin(), menuOptions.end(), operationSelector) == 0)) {


			if (cin.eof()) {

				cout << "\nStopping the program . . ." << endl;
				return -1;
			}

			menuFailFlags = true;
			cin.clear();
			cin.ignore(1000, '\n');



			cout << "\nInvalid input." << endl;

		}


		cout << "\x1B[2J\x1B[H";							// "clears" the terminal

	} while (menuFailFlags);

	return operationSelector;
}

