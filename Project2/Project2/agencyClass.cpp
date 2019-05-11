#include <fstream>
#include <vector>

#include "utilities.h"
#include "agencyClass.h"


// ------------------------------------------------------------------------
// Constructors

// sets agency Information
Agency::Agency(string agencyFileName) {

	string textLine;
	ifstream agencyFile(agencyFileName);
	vector<string> agencyInfo = {};

	if (agencyFile.is_open()) {

		while (getline(agencyFile, textLine)) {
			agencyInfo.push_back(textLine);
		}

		agencyFile.close();
		if (agencyInfo.size() != 6) {
			// if some information is missing from the .txt file
			return ;
		}


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

//void Agency::setClients(vector<Client> & clients) {
//	this->clients = clients;
//}
//
//void Agency::setPackages(vector<Packages> & packages) {
//	this->packages = packages;
//}



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

//vector<Client> Agency::getClients() const{
//	return clients;
//}
//
//vector<Package> Agency::getPackages() const {
//	return packages;
//}



ostream& operator<<(ostream& out, const Agency &agency) {
	out << "Agency " << agency.name << '\n'
		<< "NIF: " << agency.nif << '\n'
		<< "URL: " << agency.url << '\n'
		<< "Address: " << agency.agencyAddress << '\n'
		<< "Client's File Name: " << agency.clientsFileName << '\n'
		<< "Packages' File Name: " << agency.packagesFileName << '\n';

	return out;

}