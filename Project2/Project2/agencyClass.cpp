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

		setValidAgencyFile();

		while (getline(agencyFile, textLine)) {
			agencyInfo.push_back(textLine);
		}

		agencyFile.close();
		if (agencyInfo.size() != 6) {
			setInvalidAgencyFile();
			return;
		}


		setName(agencyInfo.at(0));			// set agency name
		setNif(stoi(agencyInfo.at(1)));
		setUrl(agencyInfo.at(2));
		// ADDRESS
		setClientsFile(agencyInfo.at(4));
		setPackagesFile(agencyInfo.at(5));

	}

}


// ------------------------------------------------------------------------
// Public Functions

// set functions
void Agency::setName(string newName) {
	name = newName;
}

void Agency::setNif(unsigned newNif) {
	nif = newNif;
}

void Agency::setUrl(string newUrl) {
	url = newUrl;
}

void Agency::setClientsFile(string newClients) {
	clientsFile = newClients;
}

void Agency::setPackagesFile(string newPackages) {
	packagesFile = newPackages;
}

void Agency::setInvalidAgencyFile() {
	agencyNameStatus = false;
}

void Agency::setValidAgencyFile() {
	agencyNameStatus = true;
}


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

bool Agency::getAgencyNameStatus() {
	return agencyNameStatus;
}
