#include <fstream>
#include <vector>
#include <iomanip>

#include "utilities.h"
#include "agencyClass.h"


// ------------------------------------------------------------------------
// Constructors

// sets the agency's information
Agency::Agency(string agencyFileName) {

	string textLine;
	ifstream agencyFile(agencyFileName);
	vector<string> agencyInfo = {};

	if (agencyFile.is_open()) {

		while (getline(agencyFile, textLine)) {
			agencyInfo.push_back(textLine);
		}

		agencyFile.close();

		setName(agencyInfo.at(0));
		setNif(stoi(agencyInfo.at(1)));
		setUrl(agencyInfo.at(2));
		setAddress(agencyInfo.at(3));
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

void Agency::setAddress(Address agencyAddress) {
	this->agencyAddress = agencyAddress;
}

void Agency::setClientsFile(string clientsFileName) {
	this->clientsFileName = clientsFileName;
}

void Agency::setPackagesFile(string packagesFileName) {
	this->packagesFileName = packagesFileName;
}


// get functions
string Agency::getName() const {
	return name;
}

unsigned Agency::getNif() const {
	return nif;
}

string Agency::getUrl() const {
	return url;
}

Address Agency::getAddress() const {
	return agencyAddress;
}

string Agency::getClientsFile() const {
	return clientsFileName;
}

string Agency::getPackagesFile() const {
	return packagesFileName;
}


ostream& operator<<(ostream& out, const Agency &agency) {
	
	out << left << setw(25) << "Agency Name: " << '\t' << agency.name << '\n'
		<< left << setw(25) << "NIF: " << '\t' << agency.nif << '\n'
		<< left << setw(25) << "URL: " << '\t' << agency.url << '\n'
		<< left << setw(25) << "Address: " << '\t' << agency.agencyAddress << '\n'
		<< left << setw(25) << "Client's File Name: " << '\t' << agency.clientsFileName << '\n'
		<< left << setw(25) << "Packages' File Name: " << '\t' << agency.packagesFileName << '\n';

	return out;

}