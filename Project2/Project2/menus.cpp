#include <iostream>
#include <vector>
#include <cmath>


#include "packagesRelated.h"
#include "utilities.h"
#include "clientClass.h"
#include "menus.h"
#include "clientRelated.h"

using namespace std;

// IR ATUALIZANDO À MEDIDA QUE SE VAI ADICIONANDO FUNCIONALIDADES AO MENU
vector<int> mainMenuOptions = { 0, 1, 2, 3 };
vector<int> packageMenuOptions = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
vector<int> clientMenuOptions = { 0, 1 };

int mainMenu(Agency &agency) {


	bool mainMenuFailFlags;
	int mainOperationSelector;
	
	do {
		mainMenuFailFlags = false;

		cout << "\nMain Menu\n" << endl;

		cout << "  1. Agency" << endl;
		cout << "  2. Packages" << endl;
		cout << "  3. Clients" << endl;
		cout << "  0. Quit" << endl;

		cout << endl;

		cout << "Please insert the corresponding number: ";
		cin >> mainOperationSelector;

		if ((cin.fail()) || (count(mainMenuOptions.begin(), mainMenuOptions.end(), mainOperationSelector) == 0)) {

			if (cin.eof()) {
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

	bool packageFlag = false;
	bool clientFlag = false;

	switch (mainOperationSelector) {

		case 1:
			cout << agency << endl;
			break;

		case 2:
			// goBack = packageMenu(agency);
			do {
				switch (packageMenu(agency)) {
					packageFlag = false;
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
								packageFlag = true;
								break;
						}
						break;

					case 3:
						switch (displayBetweenDates(agency)) {
							case 0:
								packageFlag = true;
						}
						break;

					case 4:
						if (displayForPlace(agency) == 0) {
							packageFlag = true;
						}
						break;

					case 5:
						if (displayDateAndPlace(agency) == 0) {
							packageFlag = true;
						}
						break;
					case 6:
						if (addPackage(agency) == 0) {
							packageFlag = true;
						}
						break;

					case 7:
						if (changePackage(agency) == 0) {
							packageFlag = true;
						}
						break;

					case 8:
						if (unavailablePackage(agency) == 0) {
							packageFlag = true;
						}
						break;

					case 9:
						packageDisplayAllClients(agency);
						break;
				}
				
			} while (packageFlag);
			break;

		case 3:

			do {
				cout << "HII" << endl;
				switch (clientMenu(agency)) {
					clientFlag = false;
					
					case 0:
						if (mainMenu(agency) == 0) {
							return 0;
						}

					case 1:
						clientDisplayAll(agency);
						break;
				}

			} while (clientFlag);
			break;

			// mostVisitedPlaces(agency);

			// numberValueSoldPackages(agency);

			/*if (packageDisplayOneClient(agency) == 0) {
				return 0;
			};*/

			/*for (int i = 0; i < clientsInfo( agency).size(); i++) {
				cout << endl;
				cout << clientsInfo(agency).at(i) << endl;
			}*/


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


int packageMenu(Agency &agency) {

	bool packageMenuFailFlags;
	int packageOperationSelector;

	do {
		packageMenuFailFlags = false;

		cout << "\nPackage Menu\n" << endl;

		cout << "  1. Display All Packages" << endl;
		cout << "  2. Display a Package of Choice" << endl;
		cout << "  3. Display Between Dates" << endl;
		cout << "  4. Display for Place" << endl;
		cout << "  5. Display For Dates and Place" << endl;
		cout << "  6. Add a Package" << endl;
		cout << "  7. Change a Package" << endl;
		cout << "  8. Change a Package to Available or Unavailable" << endl;
		cout << "  9. Packages Sold To All Clients" << endl;
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


int clientMenu(Agency &agency) {

	bool clientMenuFailFlag;
	int clientOperationSelector;

	do {
		clientMenuFailFlag = false;

		cout << "\nClient Menu\n" << endl;

		cout << "  1. Display All Clients" << endl;
		cout << "  2. Display a Client of Choice" << endl;

		cout << endl;

		cout << "Please insert the corresponding number: ";
		cin >> clientOperationSelector;
		
		if ((cin.fail()) || (count(clientMenuOptions.begin(), clientMenuOptions.end(), clientOperationSelector) == 0)) {

			if (cin.eof()) {
				cout << "\nStopping the program . . ." << endl;
				return -1;
			}

			clientMenuFailFlag = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		cout << "\x1B[2J\x1B[H";

	} while (clientMenuFailFlag);

	
	return clientOperationSelector;
}
