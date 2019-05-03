


#include "utilities.h"

using namespace std;


bool validAgencyFile(string agencyName) {

	string textLine;
	ifstream agencyFile(agencyName);
	vector<string> agencyInfo = {};

	if (agencyFile.is_open()) {


		while (getline(agencyFile, textLine)) {
			agencyInfo.push_back(textLine);
		}

		agencyFile.close();

		if (agencyInfo.size() != 6) {
			return false;
		}
		else {
			return true;
		}

	}
	
	else {
		return false;
	}
}