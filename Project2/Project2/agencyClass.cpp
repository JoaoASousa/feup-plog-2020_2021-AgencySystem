#include <fstream>
#include <vector>

#include "agencyClass.h"


// ------------------------------------------------------------------------
// Constructors

// sets agency Information
Agency::Agency(string agencyFileName) {

	string textLine;
	ifstream agencyFile(agencyFileName);
	vector<string> agencyInfo = {};
	
	if (agencyFile.is_open()) {
		
		// setValidAgencyFile();

		while (getline(agencyFile, textLine)) {
			agencyInfo.push_back(textLine);
		}

		agencyFile.close();
		
		
		setName(agencyInfo.at(0));
		setNif(stoi(agencyInfo.at(1)));
		setUrl(agencyInfo.at(2));
		// ADDRESS
		Address addresssss("Rua Sem Nome / 100 / -/ 4400 - 345 / Porto");
		setClientsFile(agencyInfo.at(4));
		setPackagesFile(agencyInfo.at(5));
		
	}


}


// ------------------------------------------------------------------------
// Public Functions

// set functions
void Agency::setName(string name) {
	this->name = name;
}

void Agency::setNif(unsigned nif) {
	this->nif = nif;
}

void Agency::setUrl(string url) {
	this->url = url;
}

void Agency::setClientsFile(string clientsFile) {
	this->clientsFile = clientsFile;
}

void Agency::setPackagesFile(string packagesFile) {
	this->packagesFile = packagesFile;
}

//void Agency::setInvalidAgencyFile() {
//	agencyNameStatus = false;
//}
//
//void Agency::setValidAgencyFile() {
//	agencyNameStatus = true;
//}


// get functions
string Agency::getName() {
	return name;
}

int Agency::getNif() {
	return nif;
}

string Agency::getUrl() {
	return url;
}

string Agency::getClientsFile() {
	return clientsFile;
}

string Agency::getPackagesFile() {
	return packagesFile;
}

//bool Agency::getAgencyNameStatus() {
//	return agencyNameStatus;
//}

void Agency::displayAgencyInfo(Agency newAgency) {

	cout << "Agency Name: " << newAgency.getName() << endl;
	cout << "Agency NIF: " << newAgency.getNif() << endl;
	cout << "Agency Url: " << newAgency.getUrl() << endl;
	cout << "Address: " << endl;
	cout << "Agency's Clients File Name: " << newAgency.getClientsFile() << endl;
	cout << "Agency's Packages File Name: " << newAgency.getPackagesFile() << endl;

}