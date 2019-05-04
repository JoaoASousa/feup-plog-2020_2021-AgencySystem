#include <sstream>
#include <vector>

#include "address.h"

using namespace std;

/*
Address::Address(string addressString) {
	
	stringstream ss(addressString);

	string temp;

	vector <string> stringsVector;

	while (getline(ss, temp, '/')) {
		stringsVector.push_back(temp);
	}
	
	stringsVector.at(0).erase(stringsVector.at(0).find_last_not_of(" ") + 1);
	stringsVector.at(1);
	stringsVector.at(2);
	stringsVector.at(3);
	place = stringsVector.at(4);
}
*/



// ------------------------------------------------------------------------
// Constructors

Address::Address() {
}

Address::Address(string street, unsigned short doorNumber, string floor, string postalCode, string location) {

	// REQUIRES IMPLEMENTATION
}



// ------------------------------------------------------------------------
// Public Functions

// set functions
void Address::setStreet(string street) {
	this->street = street;
}

void Address::setDoorNumber(unsigned short doorNumber) {
	this->doorNumber = doorNumber;
}

void Address::setFloor(string floor) {
	this->floor = floor;
}

void Address::setZipCode(string zipCode) {
	this->zipCode = zipCode;
}

void Address::setLocation(string  location) {
	this->location = location;
}



// get functions
string Address::getStreet() const {
	return street;
}

unsigned short Address::getDoorNumber() const {
	return doorNumber;
}

string Address::getFloor() const {
	return floor;
}

string Address::getZipCode() const {
	return zipCode;
}

string Address::getLocation() const {
	return location;
}





/*********************************
 * Mostrar Address
 ********************************/

 // discplyes an address in a nice format
ostream& operator<<(ostream& out, const Address &address) {

	// REQUIRES IMPLEMENTATION

}
