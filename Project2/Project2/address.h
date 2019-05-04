#pragma once

#include <iostream>
#include <string>

using namespace std;

class Address {

	private:
		string street;
		unsigned short doorNumber;
		string floor; 
		string zipCode; 
		string location; 

	public:
		Address();
		Address(string street, unsigned short doorNumber, string floor, string postalCode, string location);

		// set functions
		void setStreet(string street);
		void setDoorNumber(unsigned short doorNumber);
		void setFloor(string floor);
		void setZipCode(string postalCode);
		void setLocation(string  location);

		// get functions
		string getStreet() const;
		unsigned short getDoorNumber() const;
		string getFloor() const;
		string getZipCode() const;
		string getLocation() const;


		friend ostream& operator<<(ostream& out, const Address & address);


};