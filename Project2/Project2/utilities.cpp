#include "utilities.h"


using namespace std;


// function that checks if the filename given corresponds to a valid agency 
bool validAgencyFile(string agencyName) {

	string textLine;
	ifstream agencyFile(agencyName);
	vector <string> agencyInfo = {};
	bool openPacksFile = true;
	bool openClientsFile = true;

	if (agencyFile.is_open()) {

		while (getline(agencyFile, textLine)) {
			agencyInfo.push_back(textLine);
		}

		agencyFile.close();

		// if some information is missing from the .txt file
		if (agencyInfo.size() != 6) {
			cout << "Missing information\n" << endl;
			return false;
		}

		else {
			// checking if the packages' file provided exists
			ifstream packagesFile(agencyInfo.at(5));

			vector<Package> packagesInfo;

			if (!packagesFile.is_open()) {
				openPacksFile = false;
				cout << "Invalid packages filename" << endl;
			}
			packagesFile.close();

			// checking if the clients' file provided exists
			ifstream clientsFile(agencyInfo.at(4));

			if (!clientsFile.is_open()) {
				openClientsFile = false;
				cout << "Invalid clients filename" << endl;
			}
			clientsFile.close();

			// if they both exist
			if (openClientsFile && openPacksFile) {
				return true;
			}

			else {
				cout << endl;
				return false;
			}
		}
	}

	else {
		return false;
	}

}


// returns a vector of packages from a string containing the name of the packages' file
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


// returns a vector of clients from a string containing the name of the clients' file
vector<Client> clientsInfo(Agency agency) {
	
	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	vector<int> clientPackagesIds;
	vector<Package> clientPackages;

	string textLine;
	ifstream clientsFile(agency.getClientsFile());

	vector<Client> clientsInfo;

	Client client;

	int lineCounter = 0;

	if (clientsFile.is_open()) {

		while (getline(clientsFile, textLine)) {
			if (textLine.find("::::::::::") != string::npos) {
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
									clientPackages.push_back(packagesInfoVector.at(i));
								}
							}
							
						}
						client.setPackageList(clientPackages);
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


// return the number of days given the month and year
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


// checks if a date isn't before a reference (date)
bool checkDate(Date ToEvaluateDate, Date referenceDate) {

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

	// same year / month, day verification
	else if ((ToEvaluateDate.getYear() == referenceDate.getYear()) && (ToEvaluateDate.getMonth() == referenceDate.getMonth()) && (ToEvaluateDate.getDay() < referenceDate.getDay())) {
		validDate = false;
	}

	// day verification
	else if (daysOfMonth(ToEvaluateDate.getMonth(), ToEvaluateDate.getYear()) < ToEvaluateDate.getDay()) {
		validDate = false;
	}

	return validDate;
}


// function to convert a string to a vector of strings
vector <string> stringToStringVector(string fullString) {

	string temp;
	string const delims = { "-," };
	vector <string> stringsVector;

	size_t beg, pos = 0;
	while ((beg = fullString.find_first_not_of(delims, pos)) != std::string::npos)
	{
		pos = fullString.find_first_of(delims, beg + 1);
		stringsVector.push_back(trimString(fullString.substr(beg, pos - beg)));
	}

	return stringsVector;
}


// function to convert a string to a vector of integers
vector <int> stringToIntVector(string fullString) {

	string temp;
	string const delims = { ";" };
	vector <int> intVector;

	size_t beg, pos = 0;
	while ((beg = fullString.find_first_not_of(delims, pos)) != std::string::npos){
		
		pos = fullString.find_first_of(delims, beg + 1);
		intVector.push_back(stoi(trimString(fullString.substr(beg, pos - beg))));
	}

	return intVector;
}


// function to trim both ends of a string
string trimString(const string &toTrim, const string &whitespace) {

	auto stringBegin = toTrim.find_first_not_of(whitespace);
	if (stringBegin == string::npos) {
		return "";
	}

	auto stringEnd = toTrim.find_last_not_of(whitespace);
	auto stringRange = stringEnd - stringBegin + 1;

	return toTrim.substr(stringBegin, stringRange);
}