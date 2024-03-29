#include <sstream>
#include <vector>

#include "utilities.h"
#include "address.h"

using namespace std;


// ------------------------------------------------------------------------
// Constructors

Address::Address() {
	
	setStreet("");
	setDoorNumber(0);
	setFloor("");
	setZipCode("");
	setLocation("");

}

Address::Address(string addressString){

	stringstream ss(addressString);

	string temp;

	vector <string> stringsVector;

	while (getline(ss, temp, '/')) {
		stringsVector.push_back(temp);
	}

	setStreet(trimString(stringsVector.at(0)));
	setDoorNumber(stoi(trimString(stringsVector.at(1))));
	setFloor(trimString(stringsVector.at(2)));
	setZipCode(trimString(stringsVector.at(3)));
	setLocation(trimString(stringsVector.at(4)));
	
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


ostream& operator<<(ostream& out, const Address &address) {

	out << address.getStreet() << ", " << address.getDoorNumber()
		<< ", " << address.getFloor() << ", "
		<< address.getZipCode() << ", " << address.getLocation();
	
	return out;
}
