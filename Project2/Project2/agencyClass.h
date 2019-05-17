#pragma once

#include <iostream>
#include <string>
#include <vector>

#include  "address.h"

using namespace std;

class Agency {

	private:
		string name;
		unsigned int nif;
		Address agencyAddress;
		string url;
		string clientsFileName;
		string packagesFileName;



	public:
		Agency(string agencyFileName);
		
		// set functions
		void setName(string name);
		void setNif(unsigned nif);
		void setUrl(string url);
		void setAddress(Address agencyAddress);
		void setClientsFile(string clientsFileName);
		void setPackagesFile(string packagesFileName);



		// get functions
		string getName() const;
		unsigned getNif() const;
		Address getAddress() const;
		string getUrl() const;
		string getClientsFile() const;
		string getPackagesFile() const;



		friend ostream& operator<<(ostream& out, const Agency & agency);

};