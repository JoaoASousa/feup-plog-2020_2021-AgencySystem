#include "utilities.h"
#include "clientRelated.h"
#include "packagesRelated.h"
#include <iostream>
#include <map>

using namespace std;

// writes to the clients' file the information contained in the vector of clients
void writeClientsFromVector(string &clientsFileName, vector<Client> &clientsInfoVector) {

	ofstream clientsFileInput(clientsFileName);

	if (clientsFileInput.is_open()) {

		for (int i = 0; i < clientsInfoVector.size(); i++) {

			if (i != 0) {
				clientsFileInput << "::::::::::" << endl;
			}

			clientsFileInput << clientsInfoVector.at(i).getName() << endl;
			clientsFileInput << clientsInfoVector.at(i).getNif() << endl;
			clientsFileInput << clientsInfoVector.at(i).getFamilySize() << endl;
			clientsFileInput << clientsInfoVector.at(i).getAddress().getStreet()
				<< " / " << clientsInfoVector.at(i).getAddress().getDoorNumber()
				<< " / " << clientsInfoVector.at(i).getAddress().getFloor()
				<< " / " << clientsInfoVector.at(i).getAddress().getZipCode()
				<< " / " << clientsInfoVector.at(i).getAddress().getLocation()
				<< endl;

			if (clientsInfoVector.at(i).getPackageList().size() == 0) {
				clientsFileInput << endl;
				clientsFileInput << clientsInfoVector.at(i).getTotalPurchased() << endl;
			}

			else {
				for (int j = 0; j < clientsInfoVector.at(i).getPackageList().size(); j++) {

					if (clientsInfoVector.at(i).getPackageList().size() == 0) {
						clientsFileInput << endl;
					}

					if (j != 0) {
						clientsFileInput << " ; ";
					}
					clientsFileInput << abs(clientsInfoVector.at(i).getPackageList().at(j).getId());
				}
				clientsFileInput << endl;
				clientsFileInput << clientsInfoVector.at(i).getTotalPurchased() << endl;
			}
		}
		clientsFileInput.close();
	}
}


// outputs to the terminal the information of all clients
int clientDisplayAll(Agency &agency, vector<Client> &clientsInfoVector) {

	cout << endl;
	for (int i = 0; i < clientsInfoVector.size(); i++) {

		cout << endl;
		cout << clientsInfoVector.at(i) << endl;
	}
	return -1;
}


// outputs to the terminal the information of a specific client
int displayOneClient(Agency &agency, vector<Client> &clientsInfoVector) {
	
	bool clientSelectorFailFlag = false;
	vector <int> clientsNumbers = { 0 };
	int clientSelection;

	// Input control for the client choice
	do {
		cout << endl;
		clientSelectorFailFlag = false;
		for (int i = 0; i < clientsInfoVector.size(); i++) {

			cout << "Client #" << i + 1 << " ("
				<< clientsInfoVector.at(i).getName() << ")";

			clientsNumbers.push_back(i + 1);

			cout << endl;
		}

		cout << "\nPlease insert the corresponding number: ";
		cin >> clientSelection;

		cout << "\x1B[2J\x1B[H";

		if ((cin.fail()) || (count(clientsNumbers.begin(), clientsNumbers.end(), clientSelection) == 0)) {

			if (cin.eof()) {
				cout << "\nStopping the program . . ." << endl;
				return 0;
			}

			clientSelectorFailFlag = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		else if (clientSelection == 0) {
			return 0;
		}

		cout << "\x1B[2J\x1B[H";

	} while (clientSelectorFailFlag);

	// output to the terminal the selected client
	cout << endl;
	cout << clientsInfoVector.at(clientSelection - 1) << endl;

	return -1;

}


// add a client
int addClient(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {

	string clientsFileName = agency.getClientsFile();

	Client newClient;

	// name of the new client
	string nameString;
	cout << endl;
	cout << "Name: ";
	getline(cin >> ws, nameString);

	if (trimString(nameString) == to_string(0)) {
		return 0;
	}

	if (cin.fail()) {
		if (cin.eof()) {
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
	}

	newClient.setName(trimString(nameString));


	// nif of the new client
	bool nifInputFail;
	int nif;

	do {
		nifInputFail = false;
		cout << endl;
		cout << "NIF: ";
		cin >> nif;

		if (cin.fail()) {
			if (cin.eof()) {
				return 0;
			}
			else {
				cout << "\n(Invalid input)" << endl;
				nifInputFail = true;
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}

		else if (nif < 100000000 || nif > 999999999) {
			nifInputFail = true;
		}

		else if (nif == 0) {
			return 0;
		}

	} while (nifInputFail);

	newClient.setNif(nif);

	// family size of the new client
	bool familySizeInputFail;
	int familySize;

	do {
		familySizeInputFail = false;
		cout << endl;
		cout << "Family Size: ";
		cin >> familySize;

		if (cin.fail()) {
			if (cin.eof()) {
				return 0;
			}
			else {
				cout << "\n(Invalid input)" << endl;
				familySizeInputFail = true;
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}

		else if (familySize == 0) {
			return 0;
		}

		else if (familySize < 0) {
			cout << "\n(Invalid input)" << endl;
			familySizeInputFail = true;
		}

	} while (familySizeInputFail);

	newClient.setFamilySize(familySize);

	// address of the new client
	bool addressInputFail;
	string clientAddressString;

	do {
		addressInputFail = false;
		cout << endl;
		cout << "Address ([Street] / [Door number] / [Floor, '-' if not applicable] / [Zip Code] / [Place]) : ";
		getline(cin >> ws, clientAddressString);

		if (clientAddressString == to_string(0)) {
			return 0;
		}

		if (cin.fail()) {
			if (cin.eof()) {
				return 0;
			}

			addressInputFail = true;
			cin.clear();
			cin.ignore(1000, '\n');
		}

		else {
			addressInputFail = false;

			try {

				stringstream ss(clientAddressString);

				string temp;

				vector <string> stringsVector;

				while (getline(ss, temp, '/')) {
					stringsVector.push_back(temp);
				}

				if (stringsVector.size() != 5){
					addressInputFail = true;
				}

				else {
					stringsVector.at(1) = (stoi(trimString(stringsVector.at(1))));
				}
				
			}
			catch (...) {
				addressInputFail = true;
			}
		}

	} while (addressInputFail);
	

	Address clientAddress(clientAddressString);

	newClient.setAddress(clientAddress);

	// list of bought packages of the new client
	bool packageListInputFail;
	string packageListString;
	vector<int> clientPackagesIds;
	vector<Package> clientPackages;
	int packageCounter;

	do {
		cout << endl;
		packageListInputFail = false;
		packageCounter = 0;
		clientPackages = {};

		cout << "Packages bought ([id] ; [id] ...  Or \"none\") : ";
		getline(cin >> ws, packageListString);

		if (packageListString == to_string(0)) {
			cout << "\x1B[2J\x1B[H";
			return 0;
		}

		if (cin.fail()) {
			if (cin.eof()) {
				return 0;
			}
			packageListInputFail = true;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		
		if (trimString(packageListString) == "none") {
			clientPackagesIds = {};
		}
		else {
			clientPackagesIds = stringToIntVector(packageListString);
		}
		
		for (int i = 0; i < packagesInfoVector.size(); i++) {

			for (int j = 0; j < clientPackagesIds.size(); j++) {
				if (abs(packagesInfoVector.at(i).getId()) == clientPackagesIds.at(j)) {
					packageCounter++;
					clientPackages.push_back(packagesInfoVector.at(i));
				}
			}

		}

		if (packageCounter != clientPackagesIds.size()) {
			packageListInputFail = true;
		}

		// Updating Sold Packages
		int newTotalSold;

		for (int i = 0; i < packagesInfoVector.size(); i++) {

			for (int j = 0; j < clientPackagesIds.size(); j++) {

				if (abs(packagesInfoVector.at(i).getId()) == clientPackagesIds.at(j)) {

					newTotalSold = packagesInfoVector.at(i).getSold() + newClient.getFamilySize();

					if (newTotalSold > packagesInfoVector.at(i).getMaxPeople()) {
						packageListInputFail = true;
						cout << "\nMaximum number of people reached" << endl;
					}
					else {
						packagesInfoVector.at(i).setSold(newTotalSold);
					}
				}
			}
		}


	} while (packageListInputFail);

	newClient.setPackageList(clientPackages);

	// total purchases of the new client (total spent)
	int totalPurchases = 0;

	for (int i = 0; i < clientPackages.size(); i++) {
		totalPurchases += clientPackages.at(i).getPricePer() * familySize;
	}
		
	if (totalPurchases < 0) {
		cout << "\nInvalid Package Price" << endl;
		return 0;
	}
	
	newClient.setTotalPurchased(totalPurchases);


	clientsInfoVector.push_back(newClient);


	cout << "\x1B[2J\x1B[H";

	return -1;
}


// remove a client
int removeClient(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {

	bool clientSelectorFailFlag = false;
	vector <int> clientsNumbers = { 0 };
	int clientSelection;
	
	string clientsFileName = agency.getClientsFile();

	// Input control for the client choice
	do {
		cout << endl;
		clientSelectorFailFlag = false;
		for (int i = 0; i < clientsInfoVector.size(); i++) {

			cout << "Client #" << i + 1 << " ("
				<< clientsInfoVector.at(i).getName() << ")";

			clientsNumbers.push_back(i + 1);

			cout << endl;
		}

		cout << "\nPlease insert the corresponding number: ";
		cin >> clientSelection;

		cout << "\x1B[2J\x1B[H";

		if ((cin.fail()) || (count(clientsNumbers.begin(), clientsNumbers.end(), clientSelection) == 0)) {

			if (cin.eof()) {
				cout << "\nStopping the program . . ." << endl;
				return 0;
			}

			clientSelectorFailFlag = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		else if (clientSelection == 0) {
			return 0;
		}

		cout << "\x1B[2J\x1B[H";

	} while (clientSelectorFailFlag);


	clientsInfoVector.erase(clientsInfoVector.begin() + clientSelection - 1);
	

	return -1;

}


// buy a specified package for a specified client
int buyPackage(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {
	
	string clientsFileName = agency.getClientsFile();
	string packagesFileName = agency.getPackagesFile();

	bool clientSelectorFailFlag = false;
	vector <int> clientsNumbers = { 0 };
	int clientSelection;

	// Input control for the client choice
	do {
		cout << endl;
		clientSelectorFailFlag = false;
		for (int i = 0; i < clientsInfoVector.size(); i++) {
			
			cout << "Client #" << i + 1 << " ("
				<< clientsInfoVector.at(i).getName() << ")";

			clientsNumbers.push_back(i + 1);

			cout << endl;
		}

		cout << "\nPlease insert the corresponding number: ";
		cin >> clientSelection;

		cout << "\x1B[2J\x1B[H";

		if ((cin.fail()) || (count(clientsNumbers.begin(), clientsNumbers.end(), clientSelection) == 0)) {

			if (cin.eof()) {
				cout << "\nStopping the program . . ." << endl;
				return 0;
			}

			clientSelectorFailFlag = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		else if (clientSelection == 0) {
			return 0;
		}

		cout << "\x1B[2J\x1B[H";

	} while (clientSelectorFailFlag);


	vector <int> packagesAlreadyBought;

	for (int i = 0; i < clientsInfoVector.at(clientSelection - 1).getPackageList().size(); i++) {
		packagesAlreadyBought.push_back(abs(clientsInfoVector.at(clientSelection - 1).getPackageList().at(i).getId()));
	}


	bool packageSelectorFailFlag = false;
	bool unavailablePackage = false;
	vector <int> packageNumbers = { 0 };
	int packageSelection;
	int newTotalSold;
	bool changeToUnavailable;

	// Input control for the package choice
	do {
		packageSelectorFailFlag = false;

		for (int i = 0; i < packagesInfoVector.size(); i++) {

			cout << "Package #" << abs(packagesInfoVector.at(i).getId()) << " ("
				<< packagesInfoVector.at(i).getPlaces().at(0) << ")";

			packageNumbers.push_back(abs(packagesInfoVector.at(i).getId()));

			if (packagesInfoVector.at(i).getId() < 0) {
				cout << "\t[Unavailable Package]";
			}
			cout << endl;
		}

		cout << "\nPlease insert the corresponding number: ";
		cin >> packageSelection;

		cout << "\x1B[2J\x1B[H";

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

		else if (packageSelection == 0) {
			return 0;
		}

		// if the package is unavailable
		else if (packagesInfoVector.at(packageSelection - 1).getId() < 0) {
			packageSelectorFailFlag = true;
		}
		
		// if the client already has bought the package
		else if (find(packagesAlreadyBought.begin(), packagesAlreadyBought.end(), abs(packagesInfoVector.at(packageSelection - 1).getId())) != packagesAlreadyBought.end()) {
			packageSelectorFailFlag = true;
		}

		else {
			// if the limit of people of the package would be surpassed
			newTotalSold = packagesInfoVector.at(packageSelection - 1).getSold() +
				clientsInfoVector.at(clientSelection - 1).getFamilySize();

			if (newTotalSold > packagesInfoVector.at(packageSelection - 1).getMaxPeople()) {
				packageSelectorFailFlag = true;
			}
			else if (newTotalSold == packagesInfoVector.at(packageSelection - 1).getMaxPeople()) {
				packagesInfoVector.at(packageSelection - 1).setId(-packagesInfoVector.at(packageSelection - 1).getId());
			}
		}

		cout << "\x1B[2J\x1B[H";

	} while (packageSelectorFailFlag);

	cout << "\nPackage Purchase Successful" << endl;
	
	// updating the packages bought by the client
	vector<Package> newPackageList;
	newPackageList = clientsInfoVector.at(clientSelection - 1).getPackageList();
	newPackageList.push_back(packagesInfoVector.at(packageSelection - 1));
	
	// updating the total amount spent by the client
	int newTotalPurchased;
	newTotalPurchased = clientsInfoVector.at(clientSelection - 1).getTotalPurchased();
	newTotalPurchased += packagesInfoVector.at(packageSelection - 1).getPricePer()
		* clientsInfoVector.at(clientSelection - 1).getFamilySize();


	clientsInfoVector.at(clientSelection - 1).setTotalPurchased(newTotalPurchased);
	clientsInfoVector.at(clientSelection - 1).setPackageList(newPackageList);

	// updating the number of packages sold in the packages' file
	packagesInfoVector.at(packageSelection - 1).setSold(newTotalSold);

	
	return -1;
}


// change a specific client information
int changeClient(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {
	
	string clientsFileName = agency.getClientsFile();
	string packagesFileName = agency.getPackagesFile();


	bool clientSelectorFailFlag = false;
	vector <int> clientsNumbers = { 0 };
	int clientSelection;

	// Input control for the client choice
	do {
		cout << endl;
		clientSelectorFailFlag = false;
		for (int i = 0; i < clientsInfoVector.size(); i++) {

			cout << "Client #" << i + 1 << " ("
				<< clientsInfoVector.at(i).getName() << ")";

			clientsNumbers.push_back(i + 1);

			cout << endl;
		}

		cout << "\nPlease insert the corresponding number: ";
		cin >> clientSelection;

		cout << "\x1B[2J\x1B[H";

		if ((cin.fail()) || (count(clientsNumbers.begin(), clientsNumbers.end(), clientSelection) == 0)) {

			if (cin.eof()) {
				cout << "\nStopping the program . . ." << endl;
				return 0;
			}

			clientSelectorFailFlag = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		else if (clientSelection == 0) {
			cout << "\x1B[2J\x1B[H";
			return 0;
		}

		cout << "\x1B[2J\x1B[H";

	} while (clientSelectorFailFlag);



	bool invalidChangeSelection = false;
	vector<int> changeOptions = {1, 2, 3, 4, 5 };
	int changeSelection;

	// Input control for the change selection
	do {
		invalidChangeSelection = false;

		cout << clientsInfoVector.at(clientSelection - 1) << endl;
		cout << endl;

		cout << "Change Options" << endl;
		cout << " 1. Name" << endl;
		cout << " 2. NIF" << endl;
		cout << " 3. Family Size" << endl;
		cout << " 4. Address" << endl;
		cout << " 5. Packages Bought (IDs)" << endl;
		

		cout << endl;
		cout << "Please insert the corresponding number: ";
		cin >> changeSelection;

		if (changeSelection == 0) {
			cout << "\x1B[2J\x1B[H";
			return 0;
		}


		if ((cin.fail()) || (count(changeOptions.begin(), changeOptions.end(), changeSelection) == 0)) {

			if (cin.eof()) {
				return 0;
			}

			invalidChangeSelection = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		cout << "\x1B[2J\x1B[H";

	} while (invalidChangeSelection);



	string nameString;

	bool nifInputFail;
	int nif;

	bool familySizeInputFail;
	int familySize;

	bool addressInputFail;
	string clientAddressString;
	bool changedAddress = false;
	
	bool packageListInputFail;
	string packageListString;
	vector<int> clientPackagesIds;
	vector<Package> clientPackages;
	int packageCounter;
	int totalPurchases;


	switch (changeSelection) {
		
		// changing the name
		case 1:
			cout << "Current Name: " << clientsInfoVector.at(clientSelection - 1).getName() << endl;
			cout << "Updated Name: ";
			getline(cin >> ws, nameString);

			if (nameString == to_string(0)) {
				cout << "\x1B[2J\x1B[H";
				return 0;
			}

			if (cin.fail()) {
				if (cin.eof()) {
					return 0;
				}
				cin.clear();
				cin.ignore(1000, '\n');
			}
			
			clientsInfoVector.at(clientSelection - 1).setName(nameString);
			break;

		
		// changing the nif
		case 2:
			do {
				nifInputFail = false;
				cout << "Current Nif: " << clientsInfoVector.at(clientSelection - 1).getNif() << endl;
				cout << "Updated NIF: ";
				cin >> nif;

				if (nif < 100000000 || nif > 999999999) {
					nifInputFail = true;
				}

				if (nif == 0) {
					cout << "\x1B[2J\x1B[H";
					return 0;
				}

				if (cin.fail()) {
					if (cin.eof()) {
						return 0;
					}
					else {
						cout << "Invalid input" << endl;
						nifInputFail = true;
						cin.clear();
						cin.ignore(1000, '\n');
					}
				}

				cout << "\x1B[2J\x1B[H";
			} while (nifInputFail);

			clientsInfoVector.at(clientSelection - 1).setNif(nif);
			break;

		
		// changing the family size
		case 3:
			do {
				familySizeInputFail = false;

				cout << "Current Family Size: " << clientsInfoVector.at(clientSelection - 1).getFamilySize() << endl;
				cout << "Updated Family Size: ";
				cin >> familySize;

				if (familySize == 0) {
					cout << "\x1B[2J\x1B[H";
					return 0;
				}

				if (familySize < 0) {
					familySizeInputFail = true;
				}

				if (cin.fail()) {
					if (cin.eof()) {
						return 0;
					}
					else {
						cout << "Invalid input" << endl;
						familySizeInputFail = true;
						cin.clear();
						cin.ignore(1000, '\n');
					}
				}

				cout << "\x1B[2J\x1B[H";
			} while (familySizeInputFail);

			clientsInfoVector.at(clientSelection - 1).setFamilySize(familySize);
			break;


		// changing the address
		case 4:
			do {
				cout << "Current Address: " << clientsInfoVector.at(clientSelection - 1).getAddress() << endl;
				addressInputFail = false;
				changedAddress = true;

				cout << "Updated Address ([Street] / [Door number] / [Floor, '-' if not applicable] / [Zip Code] / [Place]) : ";
				getline(cin >> ws, clientAddressString);

				if (clientAddressString == to_string(0)) {
					cout << "\x1B[2J\x1B[H";
					return 0;
				}

				if (cin.fail()) {
					if (cin.eof()) {
						return 0;
					}

					addressInputFail = true;
					cin.clear();
					cin.ignore(1000, '\n');
				}

				else {
					addressInputFail = false;

					// address input control
					try {

						stringstream ss(clientAddressString);

						string temp;

						vector <string> stringsVector;

						while (getline(ss, temp, '/')) {
							stringsVector.push_back(temp);
						}

						if (stringsVector.size() != 5) {
							addressInputFail = true;
						}

						else {
							stringsVector.at(1) = (stoi(trimString(stringsVector.at(1))));
						}

					}
					catch (...) {
						addressInputFail = true;
					}
				}

				cout << "\x1B[2J\x1B[H";
			} while (addressInputFail);

			break;

		// changing the packages bought
		case 5:
			do {
				cout << "Current Packages Bought: ";
				for (int p = 0; p < clientsInfoVector.at(clientSelection - 1).getPackageList().size(); p++) {
					if (p == 0) {
						cout << abs(clientsInfoVector.at(clientSelection - 1).getPackageList().at(p).getId());
					}
					else {
						cout << ", " << abs(clientsInfoVector.at(clientSelection - 1).getPackageList().at(p).getId());
					}
				}

				cout << endl;
				packageListInputFail = false;
				packageCounter = 0;
				clientPackages = {};

				cout << "Packages bought ([id] ; [id] ...  Or \"none\") : ";
				getline(cin >> ws, packageListString);

				if (packageListString == to_string(0)) {
					cout << "\x1B[2J\x1B[H";
					return 0;
				}

				if (cin.fail()) {
					if (cin.eof()) {
						return 0;
					}
					packageListInputFail = true;
					cin.clear();
					cin.ignore(1000, '\n');
				}
				if (trimString(packageListString) == "none") {
					clientPackagesIds = {};
				}
				
				else {
					clientPackagesIds = stringToIntVector(packageListString);
				}

				for (int i = 0; i < packagesInfoVector.size(); i++) {

					for (int j = 0; j < clientPackagesIds.size(); j++) {
						if (abs(packagesInfoVector.at(i).getId()) == clientPackagesIds.at(j)) {
							packageCounter++;
							clientPackages.push_back(packagesInfoVector.at(i));
						}
					}

				}

				if (packageCounter != clientPackagesIds.size()) {
					packageListInputFail = true;
				}


				cout << "\x1B[2J\x1B[H";
			} while (packageListInputFail);

			clientsInfoVector.at(clientSelection - 1).setPackageList(clientPackages);
			

			// updating the total amount spent
			totalPurchases = 0;

			for (int i = 0; i < clientPackages.size(); i++) {
				totalPurchases += clientPackages.at(i).getPricePer() * clientsInfoVector.at(clientSelection - 1).getFamilySize();
			}

			if (totalPurchases < 0) {
				cout << "Invalid Package Price" << endl;
				return 0;
			}
			else {
				clientsInfoVector.at(clientSelection - 1).setTotalPurchased(totalPurchases);
			}

			break;

	}

	if (changedAddress) {
		changedAddress = false;
		Address clientAddress(clientAddressString);
		clientsInfoVector.at(clientSelection - 1).setAddress(clientAddress);
	}
	

	return -1;
}
