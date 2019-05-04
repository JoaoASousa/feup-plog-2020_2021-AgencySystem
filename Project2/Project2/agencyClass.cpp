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

		while (getline(agencyFile, textLine)) {
			agencyInfo.push_back(textLine);
		}

		agencyFile.close();
		if (agencyInfo.size() != 6) {
			// missing some information in the .txt file
			return ;
		}


		setName(agencyInfo.at(0));			// set agency name
		setNif(stoi(agencyInfo.at(1)));
		setUrl(agencyInfo.at(2));
		setAddress(agencyInfo.at(3));
		//setClientsFile(agencyInfo.at(4));
		//setPackagesFile(agencyInfo.at(5));*/

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

//vector<Client> Agency::getClients() const{
//	return clients;
//}
//
//vector<Package> Agency::getPackages() const {
//	return packages;
//}



ostream& operator<<(ostream& out, const Agency & agency) {
	out << "Agency " << agency.getName() << '\n'
		<< "NIF: " << agency.getNif() << '\n'
		<< "URL: " << agency.getUrl() << '\n'
		<< "Address: " << agency.getAddress() << '\n';

	return out;

}