#pragma once

#include <iostream>
#include <string>

#include  "address.h"

using namespace std;

class Agency {
	Address agencyAddress(string addressString); // HELP
	private:
		string name, url, clientsFile, packagesFile;
		string addressString;
		
		bool agencyNameStatus;
		int nif;


	public:
		Agency(string agencyFileName);

		
		// set functions
		void setName(string newName);
		void setNif(unsigned newNif);
		void setUrl(string newUrl);
		void setClientsFile(string newClients);
		void setPackagesFile(string newPackages);
		void setInvalidAgencyFile();
		void setValidAgencyFile();

		// get functions
		string getName();
		int getNif();
		string getUrl();
		string getClientsFile();
		string getPackagesFile();
		bool getAgencyNameStatus();
		void displayAgencyInfo(Agency newAgency);

};