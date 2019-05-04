#pragma once

#include <iostream>
#include <string>

using namespace std;

class Address {

	private:
		string street, floor, zipCode, location;
		unsigned short doorNumber;

	public:
		Address(string addressString);

		// set functions
		void setStreet(string street);
		void setDoorNumber(unsigned short doorNumber);
		void setFloor(string floor);
		void setZipCode(string zipCode);
		void setLocation(string location);

		// get functions
		string getStreet();
		unsigned short getDoorNumber();
		string getFloor();
		string getZipCode();
		string getLocation();

};