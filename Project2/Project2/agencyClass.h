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
		// Address agencyAddress;
		
		bool agencyNameStatus;
		int nif;


	public:
		Agency(string agencyFileName);

		
		// set functions
		void setName(string name);
		void setNif(unsigned nif);
		void setUrl(string url);
		void setClientsFile(string clientsFile);
		void setPackagesFile(string packagesFile);
		// void setInvalidAgencyFile();
		// void setValidAgencyFile();

		// get functions
		string getName();
		int getNif();
		string getUrl();
		string getClientsFile();
		string getPackagesFile();
		// bool getAgencyNameStatus();
		void displayAgencyInfo(Agency newAgency);

};