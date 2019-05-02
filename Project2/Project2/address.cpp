#include <sstream>
#include <vector>

#include "address.h"

using namespace std;

Address::Address(string addressString) {
	
	stringstream ss(addressString);

	string temp;

	vector <string> stringsVector;

	while (getline(ss, temp, '/')) {
		stringsVector.push_back(temp);
	}
	/*
	stringsVector.at(0).erase(stringsVector.at(0).find_last_not_of(" ") + 1);
	stringsVector.at(1);
	stringsVector.at(2);
	stringsVector.at(3);
	place = stringsVector.at(4);*/
}