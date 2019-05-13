#include "clientRelated.h"
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

void clientDisplayAll(Agency &agency) {

	for (int i = 0; i < clientsInfo(agency).size(); i++) {

		cout << endl;
		cout << clientsInfo(agency).at(i) << endl;
	}

}

int displayOneClient(Agency &agency) {

	bool clientSelectorFailFlag = false;
	vector <int> clientsNumbers = { 0 };
	int clientSelection;

	// Input control for the client choice
	do {

		clientSelectorFailFlag = false;
		for (int i = 0; i < clientsInfo(agency).size(); i++) {

			cout << "Client #" << i + 1 << " ("
				<< clientsInfo(agency).at(i).getName() << ")";

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
	cout << clientsInfo(agency).at(clientSelection - 1) << endl;

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