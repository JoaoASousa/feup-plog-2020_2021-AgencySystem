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
vector<int> mainMenuOptions = { 0, 1, 2, 3, 4};
vector<int> packageMenuOptions = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
vector<int> clientMenuOptions = { 0, 1, 2, 3, 4, 5, 6, 7 };

int mainMenu(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {


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
	
	
	

	bool packageFlag = false;
	bool clientFlag = false;

	switch (mainOperationSelector) {

		case 1:

			cout << agency << '\n' << endl;
			cout << "Sales: " << endl;
			numberValueSoldPackages(agency, clientsInfoVector, packagesInfoVector);
			break;

		case 2:
			
			do {
				packageFlag = false;
				switch (packageMenu(agency, clientsInfoVector, packagesInfoVector)) {
					packageFlag = false;
					case 0:
						if (mainMenu(agency, clientsInfoVector, packagesInfoVector) == 0) {
							return 0;
						}
						break;

					case 1:
						packageDisplayAll(agency, clientsInfoVector, packagesInfoVector);
						break;

					case 2:
						switch (packageDisplayOne(agency, clientsInfoVector, packagesInfoVector)) {
							case 0:
								packageFlag = true;
								break;
						}
						break;

					case 3:
						switch (displayBetweenDates(agency, clientsInfoVector, packagesInfoVector)) {
							case 0:
								packageFlag = true;
						}
						break;

					case 4:
						if (displayForPlace(agency, clientsInfoVector, packagesInfoVector) == 0) {
							packageFlag = true;
						}
						break;

					case 5:
						if (displayDateAndPlace(agency, clientsInfoVector, packagesInfoVector) == 0) {
							packageFlag = true;
						}
						break;
					case 6:
						if (addPackage(agency, clientsInfoVector, packagesInfoVector) == 0) {
							packageFlag = true;
						}
						break;

					case 7:
						if (changePackage(agency, clientsInfoVector, packagesInfoVector) == 0) {
							packageFlag = true;
						}
						break;

					case 8:
						if (unavailablePackage(agency, clientsInfoVector, packagesInfoVector) == 0) {
							packageFlag = true;
						}
						break;

					case 9:
						packageDisplayAllClients(agency, clientsInfoVector, packagesInfoVector);
						break;

					case 10:
						if (packageDisplayOneClient(agency, clientsInfoVector, packagesInfoVector) == 0) {
							return 0;
						}
						break;

					case 11:
						if (mostVisitedPlaces(agency, clientsInfoVector, packagesInfoVector) == 0) {
							return 0;
						}
						break;
				}

			} while (packageFlag);
			break;

		case 3:

			do {
				clientFlag = false;
				switch (clientMenu(agency, clientsInfoVector, packagesInfoVector)) {
					clientFlag = false;

					case 0:
						if (mainMenu(agency, clientsInfoVector, packagesInfoVector) == 0) {
							return 0;
						};
						break;

					case 1:
						if (clientDisplayAll(agency, clientsInfoVector) == 0) {
							return 0;
						}
						break;

					case 2:
						if (displayOneClient(agency, clientsInfoVector) == 0) {
							clientFlag = true;
						}
						break;

					case 3:
						if (addClient(agency, clientsInfoVector, packagesInfoVector) == 0) {
							clientFlag = true;
						}
						break;

					case 4:
						if (removeClient(agency, clientsInfoVector, packagesInfoVector) == 0) {
							clientFlag = true;
						}
						break;

					case 5:
						if (buyPackage(agency, clientsInfoVector, packagesInfoVector) == 0) {
							clientFlag = true;
						}
						break;

					case 6:
						if (changeClient(agency, clientsInfoVector, packagesInfoVector) == 0) {
							clientFlag = true;
						}
						break;

					case 7:
						if (packageSugestion(agency, clientsInfoVector, packagesInfoVector) == 0) {
							clientFlag = true;
						}
						break;

				}

			} while (clientFlag);
			break;




		default:
			break;
	}

	

	return mainOperationSelector;
}


int packageMenu(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {

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
		cout << " 10. Packages Sold to a Client" << endl;
		cout << " 11. Most Visited Places" << endl;
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


int clientMenu(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {

	bool clientMenuFailFlag;
	int clientOperationSelector;

	do {
		clientMenuFailFlag = false;

		cout << "\x1B[2J\x1B[H";

		cout << "\nClient Menu\n" << endl;

		cout << "  1. Display All Clients" << endl;
		cout << "  2. Display a Client of Choice" << endl;
		cout << "  3. Add a Client" << endl;
		cout << "  4. Delete a Client" << endl;
		cout << "  5. Buy a Package" << endl;
		cout << "  6. Change a Client" << endl;
		cout << "  7. Packages Sugestion" << endl;

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
