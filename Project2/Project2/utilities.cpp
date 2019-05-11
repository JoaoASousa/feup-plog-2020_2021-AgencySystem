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

vector<Client> clientsInfo(string clientsFileName, Agency agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	vector<int> clientPackagesIds;
	vector<Package> clientPackages;

	string textLine;
	ifstream clientsFile(clientsFileName);

	vector<Client> clientsInfo;

	Client client;

	int lineCounter = 0;

	if (clientsFile.is_open()) {

		while (getline(clientsFile, textLine)) {
			if (textLine.find("::::::::::") != string::npos) {
				// lineCounter = 0;
			}

			else {

				switch (lineCounter) {
					case 0:
						client.setName(textLine);
						break;

					case 1:
						client.setNif(stoi(textLine));
						break;

					case 2:
						client.setFamilySize(stoi(textLine));
						break;

					case 3:
						client.setAddress(textLine);
						break;

					case 4:
						clientPackages = {};

						clientPackagesIds = stringToIntVector(textLine);
						for (int i = 0; i < packagesInfoVector.size(); i++) {
							
							for (int j = 0; j < clientPackagesIds.size(); j++) {
								if (abs(packagesInfoVector.at(i).getId()) == clientPackagesIds.at(j)) {
									// cout << '\n' << clientPackagesIds.at(j) << '\n' << endl;
									clientPackages.push_back(packagesInfoVector.at(i));
								}
							}
							
						}
						client.setPackageList(clientPackages);
						// client.packages = parsePackages(textLine);
						// packagesString = packageIDsString(client.packages);
						break;
					
					case 5:
						client.setTotalPurchased(stoi(textLine));
						break;
				}

				lineCounter++;
			}

			if (lineCounter == 6) {

				clientsInfo.push_back(client);
				lineCounter = 0;
			}

		}

		clientsFile.close();
	}

	return clientsInfo;
}

int daysOfMonth(int month, int year) {

	bool leapYear = false;

	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		leapYear = true;
	}

	if ((month < 8 && month % 2 == 1) || (month >= 8 && month % 2 == 0)) {
		return 31;
	}

	else if (month == 2) {
		return leapYear ? 29 : 28;
	}

	return 30;
}

bool checkDate(Date ToEvaluateDate, Date referenceDate) {
	//cout << referenceDate << endl;
	bool validDate = true;

	// basic verification
	if (ToEvaluateDate.getYear() <= 0 || (ToEvaluateDate.getMonth() <= 0 || ToEvaluateDate.getMonth() > 12) || ToEvaluateDate.getDay() <= 0) {
		validDate = false;
	}

	// year verification
	else if (ToEvaluateDate.getYear() < referenceDate.getYear()) {
		validDate = false;
	}

	// same year, month verification
	else if ((ToEvaluateDate.getYear() == referenceDate.getYear()) && (ToEvaluateDate.getMonth() < referenceDate.getMonth())) {
		validDate = false;
	}

	else if ((ToEvaluateDate.getYear() == referenceDate.getYear()) && (ToEvaluateDate.getMonth() == referenceDate.getMonth()) && (ToEvaluateDate.getDay() < referenceDate.getDay())) {
		validDate = false;
	}

	else if (daysOfMonth(ToEvaluateDate.getMonth(), ToEvaluateDate.getYear()) < ToEvaluateDate.getDay()) {
		validDate = false;
	}

	return validDate;
}

vector <string> stringToStringVector(string fullString) {

	//istringstream ss(fullString);

	string temp;
	string const delims = { "-," };
	vector <string> stringsVector;

	size_t beg, pos = 0;
	while ((beg = fullString.find_first_not_of(delims, pos)) != std::string::npos)
	{
		pos = fullString.find_first_of(delims, beg + 1);
		stringsVector.push_back(trimString(fullString.substr(beg, pos - beg)));
	}
	/*while (ss >> temp) {
		if (temp == "-" || temp == ",") {
			continue;
		}
		cout << temp << endl;
		stringsVector.push_back(temp);
	}*/

	return stringsVector;
}

vector <int> stringToIntVector(string fullString) {

	string temp;
	string const delims = { ";" };
	vector <int> intVector;

	size_t beg, pos = 0;
	while ((beg = fullString.find_first_not_of(delims, pos)) != std::string::npos){
		
		pos = fullString.find_first_of(delims, beg + 1);
		//cout << '\n' << stoi(fullString.substr(beg, pos - beg)) << '\n' << endl;
		intVector.push_back(stoi(trimString(fullString.substr(beg, pos - beg))));
	}

	return intVector;
}

string trimString(const string &toTrim, const string &whitespace) {

	auto stringBegin = toTrim.find_first_not_of(whitespace);
	if (stringBegin == string::npos) {
		return "";
	}

	auto stringEnd = toTrim.find_last_not_of(whitespace);
	auto stringRange = stringEnd - stringBegin + 1;

	return toTrim.substr(stringBegin, stringRange);
}