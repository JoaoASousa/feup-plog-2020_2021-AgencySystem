#include "clientRelated.h"
#include "packagesRelated.h"
#include <iostream>

using namespace std;


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
		clientsFileInput.close();
	}
}

int clientDisplayAll(Agency &agency) {

	vector<Client> clientsInfoVector = clientsInfo(agency);

	for (int i = 0; i < clientsInfoVector.size(); i++) {

		cout << endl;
		cout << clientsInfoVector.at(i) << endl;
	}
	return -1;
}

int displayOneClient(Agency &agency) {

	vector<Client> clientsInfoVector = clientsInfo(agency);

	bool clientSelectorFailFlag = false;
	vector <int> clientsNumbers = { 0 };
	int clientSelection;

	// Input control for the client choice
	do {

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
	cout << clientsInfoVector.at(clientSelection - 1) << endl;

	return -1;

}

int addClient(Agency &agency) {

	vector<Client> clientsInfoVector = clientsInfo(agency);
	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	string clientsFileName = agency.getClientsFile();

	Client newClient;

	string nameString;
	cout << "Name: ";
	getline(cin >> ws, nameString);
	// ter atencao às entradas de nome com mais do que 1 espaço entre nomes

	if (nameString == to_string(0)) {
		return 0;
	}

	if (cin.fail()) {
		if (cin.eof()) {
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
	}

	newClient.setName(nameString);

	bool nifInputFail;
	int nif;

	do {
		nifInputFail = false;

		cout << "NIF: ";
		cin >> nif;

		if (nif < 100000000 || nif > 999999999) {
			nifInputFail = true;
		}

		if (nif == 0) {
			return 0;
		}

		if (cin.fail()) {
			if (cin.eof()) {
				cin.clear();
				cin.ignore(1000, '\n');
				return 0;
			}
			else {
				cout << "Invalid input" << endl;
				nifInputFail = true;
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}
	} while (nifInputFail);

	newClient.setNif(nif);


	bool familySizeInputFail;
	int familySize;

	do {
		familySizeInputFail = false;
		
		cout << "Family Size: ";
		cin >> familySize;

		if (familySize == 0) {
			return 0;
		}

		if (familySize < 0) {
			familySizeInputFail = true;
		}

		if (cin.fail()) {
			cout << "\n(Invalid input)" << endl;
			familySizeInputFail = true;
			cin.clear();
			cin.ignore(1000, '\n');
		}

	} while (familySizeInputFail);

	newClient.setFamilySize(familySize);


	bool addressInputFail;
	string clientAddressString;

	do {
		addressInputFail = false;

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

	} while (addressInputFail);

	Address clientAddress(clientAddressString);

	newClient.setAddress(clientAddress);

	
	bool packageListInputFail;
	string packageListString;
	vector<int> clientPackagesIds;
	vector<Package> clientPackages;
	int packageCounter;

	do {
		packageListInputFail = false;
		packageCounter = 0;
		clientPackages = {};

		cout << "Packages bought ([id] ; [id] ... ) : ";
		cin >> packageListString;

		if (packageListString == to_string(0)) {
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
		
		clientPackagesIds = stringToIntVector(packageListString);
		
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



	} while (packageListInputFail);

	newClient.setPackageList(clientPackages);

	int totalPurchases = 0;

	for (int i = 0; i < clientPackages.size(); i++) {
		totalPurchases += clientPackages.at(i).getPricePer() * familySize;
	}
		
	if (totalPurchases < 0) {
		cout << "Invalid Package Price" << endl;
		return 0;
	}
	
	newClient.setTotalPurchased(totalPurchases);


	clientsInfoVector.push_back(newClient);

	writeClientsFromVector(clientsFileName, clientsInfoVector);

	cout << "\x1B[2J\x1B[H";

	return -1;
}

int removeClient(Agency &agency) {

	bool clientSelectorFailFlag = false;
	vector <int> clientsNumbers = { 0 };
	int clientSelection;

	vector<Client> clientsInfoVector = clientsInfo(agency);
	string clientsFileName = agency.getClientsFile();

	// Input control for the client choice
	do {

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

	writeClientsFromVector(clientsFileName, clientsInfoVector);

	return -1;

}

int buyPackage(Agency &agency) {

	vector<Client> clientsInfoVector = clientsInfo(agency);
	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	string clientsFileName = agency.getClientsFile();
	string packagesFileName = agency.getPackagesFile();

	bool clientSelectorFailFlag = false;
	vector <int> clientsNumbers = { 0 };
	int clientSelection;

	// Input control for the client choice
	do {

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



	bool packageSelectorFailFlag = false;
	bool unavailablePackage = false;
	vector <int> packageNumbers = { 0 };
	int packageSelection;
	int newTotalSold;

	// Input control for the package choice
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

		// unavailable package
		else if (packagesInfo(agency.getPackagesFile()).at(packageSelection - 1).getId() < 0) {
			packageSelectorFailFlag = true;
		}

		// if the limit of people is surpassed
		newTotalSold = packagesInfo(agency.getPackagesFile()).at(packageSelection - 1).getSold() +
			clientsInfoVector.at(clientSelection - 1).getFamilySize();

		if (newTotalSold > packagesInfo(agency.getPackagesFile()).at(packageSelection - 1).getMaxPeople()) {
			packageSelectorFailFlag = true;
		}

		cout << "\x1B[2J\x1B[H";

	} while (packageSelectorFailFlag);

	cout << "Package Purchase Successful" << endl;
	
	vector<Package> newPackageList;
	newPackageList = clientsInfoVector.at(clientSelection - 1).getPackageList();
	newPackageList.push_back(packagesInfo(agency.getPackagesFile()).at(packageSelection - 1));
	
	int newTotalPurchased;
	newTotalPurchased = clientsInfoVector.at(clientSelection - 1).getTotalPurchased();
	newTotalPurchased += packagesInfo(agency.getPackagesFile()).at(packageSelection - 1).getPricePer()
		* clientsInfoVector.at(clientSelection - 1).getFamilySize();


	
	clientsInfoVector.at(clientSelection - 1).setTotalPurchased(newTotalPurchased);
	clientsInfoVector.at(clientSelection - 1).setPackageList(newPackageList);
	// cout << "new total sold " << newTotalSold << endl;
	packagesInfoVector.at(packageSelection - 1).setSold(newTotalSold);
	// packagesInfo(agency.getPackagesFile()).at(packageSelection - 1).setSold(newTotalSold);


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

	writeClientsFromVector(clientsFileName, clientsInfoVector);
	writePackagesFromVector(packagesFileName, lastCreated, packagesInfoVector);

	return -1;
}

int changeClient(Agency &agency) {

	vector<Client> clientsInfoVector = clientsInfo(agency);
	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	string clientsFileName = agency.getClientsFile();
	string packagesFileName = agency.getPackagesFile();


	bool clientSelectorFailFlag = false;
	vector <int> clientsNumbers = { 0 };
	int clientSelection;

	// Input control for the client choice
	do {

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
		
		case 1:
			cout << "Name: ";
			getline(cin >> ws, nameString);
			// ter atencao às entradas de nome com mais do que 1 espaço entre nomes

			if (nameString == to_string(0)) {
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


		case 2:
			do {
				nifInputFail = false;

				cout << "NIF: ";
				cin >> nif;

				if (nif < 100000000 || nif > 999999999) {
					nifInputFail = true;
				}

				if (nif == 0) {
					return 0;
				}

				if (cin.fail()) {
					if (cin.eof()) {
						cin.clear();
						cin.ignore(1000, '\n');
						return 0;
					}
					else {
						cout << "Invalid input" << endl;
						nifInputFail = true;
						cin.clear();
						cin.ignore(1000, '\n');
					}
				}
			} while (nifInputFail);

			clientsInfoVector.at(clientSelection - 1).setNif(nif);
			break;


		case 3:
			do {
				familySizeInputFail = false;

				cout << "Family Size: ";
				cin >> familySize;

				if (familySize == 0) {
					return 0;
				}

				if (familySize < 0) {
					familySizeInputFail = true;
				}

				if (cin.fail()) {
					cout << "\n(Invalid input)" << endl;
					familySizeInputFail = true;
					cin.clear();
					cin.ignore(1000, '\n');
				}

			} while (familySizeInputFail);

			clientsInfoVector.at(clientSelection - 1).setFamilySize(familySize);
			break;


		case 4:
			do {
				addressInputFail = false;
				changedAddress = true;

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

			} while (addressInputFail);

			// function to do what's bellow in the "if" statement so it can loop while the input
			// produces an exception ?
			break;


		case 5:
			do {
				packageListInputFail = false;
				packageCounter = 0;
				clientPackages = {};

				cout << "Packages bought ([id] ; [id] ... ) : ";
				cin >> packageListString;

				if (packageListString == to_string(0)) {
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

				clientPackagesIds = stringToIntVector(packageListString);

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



			} while (packageListInputFail);

			clientsInfoVector.at(clientSelection - 1).setPackageList(clientPackages);

			totalPurchases = 0;

			for (int i = 0; i < clientPackages.size(); i++) {
				totalPurchases += clientPackages.at(i).getPricePer() * clientsInfoVector.at(clientSelection - 1).getFamilySize();
			}

			if (totalPurchases < 0) {
				cout << "Invalid Package Price" << endl;
				return 0;
			}
			break;

	}

	if (changedAddress) {
		changedAddress = false;
		Address clientAddress(clientAddressString);
		clientsInfoVector.at(clientSelection - 1).setAddress(clientAddress);
	}
	
	writeClientsFromVector(clientsFileName, clientsInfoVector);


	return -1;
}