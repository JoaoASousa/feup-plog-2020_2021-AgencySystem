
#include "utilities.h"

using namespace std;


bool validAgencyFile(string agencyName) {

	string textLine;
	ifstream agencyFile(agencyName);
	vector <string> agencyInfo = {};

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

vector<Package> packagesInfo(string packagesFileName) {
	
	string textLine;
	ifstream packagesFile(packagesFileName);

	vector<Package> packagesInfo;
	
	Package package;
	
	int lineCounter = 0;
	bool firstLine = true;
	string beginString;
	string endString;

	if (packagesFile.is_open()) {


		while (getline(packagesFile, textLine)) {

			if (firstLine) {
				firstLine = false;
				continue;
			}

			if (textLine == "::::::::::") {
				continue;
			}

			else {

				switch (lineCounter) {

					case 0:
						package.setId(stoi(textLine));
						break;

					case 1:
						package.setPlaces(stringToStringVector(textLine));						
						break;

					case 2:
						beginString = textLine;
						break;

					case 3:
						endString = textLine;
						break;

					case 4:
						package.setPricePer(stoi(textLine));
						break;

					case 5:
						package.setMaxPeople(stoi(textLine));
						break;

					case 6:
						package.setSold(stoi(textLine));
						break;
				}

				Date startDateParam(beginString);
				package.setBeginDate(startDateParam);

				Date endDateParam(endString);
				package.setEndDate(endDateParam);

				lineCounter++;
			}

			if (lineCounter == 7) {
				packagesInfo.push_back(package);

				lineCounter = 0;
			}
		}

		packagesFile.close();
	}

	return packagesInfo;
}

vector <string> stringToStringVector(string fullString) {

	istringstream ss(fullString);

	string temp;

	vector <string> stringsVector;

	while (ss >> temp) {
		if (temp == "-" || temp == ",") {
			continue;
		}
		stringsVector.push_back(temp);
	}

	return stringsVector;
}