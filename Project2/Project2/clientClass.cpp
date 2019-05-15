#include "clientClass.h"
#include "address.h"

using namespace std;


// ------------------------------------------------------------------------
// Constructors

Client::Client() {

}

Client::Client(string name, unsigned nif, unsigned short familySize, Address address) {
	this->name = name;
	this->nif = nif;
	this->familySize = familySize;
	this->clientAddress = address;
}

Client::Client(string name, unsigned nif, unsigned short familySize, Address address, vector<Package> &packages, unsigned totalPurchased) {
	this->name = name;
	this->nif = nif;
	this->familySize = familySize;
	this->clientAddress = address;
	this->packages = packages;
	this->totalPurchased = totalPurchased;
}


// ------------------------------------------------------------------------
// Public Functions

// set functions
void Client::setName(string name) {
	this->name = name;
}

void Client::setNif(unsigned nif) {
	this->nif = nif;
}

void Client::setFamilySize(unsigned short familySize) {
	this->familySize = familySize;
}

void Client::setAddress(Address clientAddress) {
	this->clientAddress = clientAddress;
}

void Client::setPackageList(vector<Package> &packages) {
	this->packages = packages;
}

void Client::setTotalPurchased(unsigned totalPurchased) {
	this->totalPurchased = totalPurchased;
}


// get functions
string Client::getName() const {
	return name;
}

unsigned Client::getNif() const {
	return nif;
}

unsigned short Client::getFamilySize() const {
	return familySize;
}

Address Client::getAddress() const {
	return clientAddress;
}

vector<Package> Client::getPackageList() const {
	return packages;
}

unsigned Client::getTotalPurchased() const {
	return totalPurchased;
}


ostream &operator<<(ostream& out, const Client &client) {

	out << "Name: " << client.name << endl;
	out << "NIF: " << client.nif << endl;
	out << "Family Size: " << client.familySize << endl;
	out << "Address: " << client.clientAddress << endl;
	
	out << "Packages Bought (IDs): ";
	for (int i = 0; i < client.packages.size(); i++) {
		if (i == 0) {
			
			out << abs(client.packages.at(i).getId());
		}
		else {
			out << ", " << abs(client.packages.at(i).getId());
		}
		
	}

	out << endl;
	out << "Amount Spent: " << client.totalPurchased;

	return out;
}