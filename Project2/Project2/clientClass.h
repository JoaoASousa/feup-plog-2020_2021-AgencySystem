#pragma once

#include <iostream>
#include <string>

using namespace std;


#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "address.h"
#include "packagesClass.h"




class Client {
	private:
		string name;
		unsigned nif;
		unsigned short familySize;
		Address clientAddress;
		vector<Package> packages;
		unsigned totalPurchased;

	public:
		Client();
		Client(string name, unsigned nif, unsigned short familySize, Address clientAddress);
		Client(string name, unsigned nif, unsigned short familySize, Address clientAddress, vector<Package> &packages, unsigned totalPurchased);

		// set functions
		void setName(string name);
		void setNif(unsigned nif);
		void setFamilySize(unsigned short familySize);
		void setAddress(Address clientAddress);
		void setPackageList(vector<Package> &packages);
		void setTotalPurchased(unsigned totalPurchased);

		// get methods
		string getName() const;
		unsigned getNif() const;
		unsigned short getFamilySize() const;
		Address getAddress() const;
		vector<Package> getPackageList() const;
		unsigned getTotalPurchased() const;


		friend ostream &operator<<(ostream& out, const Client &client);
};