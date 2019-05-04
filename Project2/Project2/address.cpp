#include <sstream>
#include <vector>

#include "address.h"

using namespace std;


// ------------------------------------------------------------------------
// Constructors

Address::Address(string addressString) {
	
	stringstream ss(addressString);

	string temp;

	vector <string> stringsVector;

	while (getline(ss, temp, '/')) {
		stringsVector.push_back(temp);
	}
	
	setStreet(stringsVector.at(0).erase(stringsVector.at(0).find_last_not_of(" ") + 1));
	setDoorNumber(stoi(stringsVector.at(1)));
	setFloor(stringsVector.at(2));
	setZipCode(stringsVector.at(3));
	setLocation(stringsVector.at(4));

	/*cout << "Street:" << getStreet() << "!" << endl;
	cout << "Door number:" << getDoorNumber() << "!" << endl;
	cout << "Floor:" << getFloor() << "!" << endl;
	cout << "Zip Code:" << getZipCode() << "!" << endl;
	cout << "Location:" << getLocation() << "!" << endl;*/
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

void Address::setLocation(string location) {
	this->location = location;
}


// get functions
string Address::getStreet() {
	return street;
}

unsigned short Address::getDoorNumber() {
	return doorNumber;
}

string Address::getFloor() {
	return floor;				// MIGHT HAVE A PROBLEM HERE
}

string Address::getZipCode() {
	return zipCode;
}

string Address::getLocation() {
	return location;
}

void Address::displayAddress() {
	cout << "Address: " << getStreet() << ", "
		<< getDoorNumber() << ", " << getFloor() << ", "
		<< getZipCode() << ", " << getLocation() << endl;

}