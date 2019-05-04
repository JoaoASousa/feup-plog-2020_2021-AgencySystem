#pragma once

#include <iostream>
#include <string>
#include <vector>

#include  "address.h"

using namespace std;

class Agency {
	// Address agencyAddress(string addressString); // HELP
	private:
		string name;
		unsigned int nif;
		Address agencyAddress;
		string url;
		//vector <Client> clients;
		//vector <Package> packages;

		bool clientsInfoHasChanged;
		bool packetsInfoHasChanged; 
		unsigned int maxClientsId; 
		unsigned int maxPacketsId;


	public:
		Agency(string agencyFileName);

		
		// set functions
		void setName(string newName);
		void setNif(unsigned newNif);
		void setUrl(string newUrl);
		//void setClients(vector<Client> & clients);
		//void setPackages(vector<Packages> & packages);

		// get functions
		string getName() const;
		unsigned getNif() const;
		Address getAddress() const;
		string getUrl() const;
		//vector<Client> getClients() const;
		//vector<Package> getPackages() const;


		friend ostream& operator<<(ostream& out, const Agency & agency);

};