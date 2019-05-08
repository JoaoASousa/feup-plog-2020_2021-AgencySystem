#include <iostream>
#include <vector>
#include <cmath>

#include "utilities.h"

#include "menus.h"

using namespace std;

// IR ATUALIZANDO À MEDIDA QUE SE VAI ADICIONANDO FUNCIONALIDADES AO MENU
vector<int> mainMenuOptions = { 0, 1, 2 };
vector<int> packageMenuOptions = { 0, 1, 2, 3, 4 };


int mainMenu(Agency agency) {

	bool mainMenuFailFlags;
	int mainOperationSelector;
	
	do {
		mainMenuFailFlags = false;

		cout << "\nMain Menu\n" << endl;

		cout << "  1. Agency" << endl;
		cout << "  2. Packages" << endl;
		cout << "  0. Quit" << endl;

		cout << endl;

		cout << "Please insert the corresponding number: ";
		cin >> mainOperationSelector;

		if ((cin.fail()) || (count(mainMenuOptions.begin(), mainMenuOptions.end(), mainOperationSelector) == 0)) {

			if (cin.eof()) {
				// cout << "\nStopping the program . . ." << endl;
				return -1;
			}

			mainMenuFailFlags = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		cout << "\x1B[2J\x1B[H";
		
	} while (mainMenuFailFlags);
	
	
	int goBack = -1;

	bool flag = false;

	switch (mainOperationSelector) {

		case 1:
			cout << agency << endl;
			break;

		case 2:
			// goBack = packageMenu(agency);
			do {
				switch (packageMenu(agency)) {
					flag = false;
					case 0:
						if (mainMenu(agency) == 0) {
							return 0;
						}

					case 1:
						packageDisplayAll(agency);
						break;

					case 2:
						switch (packageDisplayOne(agency)) {
							case 0:
								flag = true;
						}
					case 3:
						switch (displayBetweenDates(agency)) {
							case 0:
								flag = true;
						}
					case 4:
						if (displayForPlace(agency) == 0) {
							flag = true;
						}
						break;
				}
				
			} while (flag);
			break;

		default:
			break;
	}

	/*if (goBack == 0) {
		if (mainMenu(agency) == 0) {
			return -1;
		};

	}*/

	return mainOperationSelector;
}


int packageMenu(Agency agency) {

	bool packageMenuFailFlags;
	int packageOperationSelector;

	do {
		packageMenuFailFlags = false;

		cout << "\nPackage Menu\n" << endl;

		cout << "  1. Display All Packages" << endl;
		cout << "  2. Display a Package of Choice" << endl;
		cout << "  3. Display Between Dates" << endl;
		cout << "  4. Display for Place" << endl;
		cout << "  0. Go back to Main Menu" << endl;

		cout << endl;

		cout << "Please insert the corresponding number: ";
		cin >> packageOperationSelector;

		if ((cin.fail()) || (count(packageMenuOptions.begin(), packageMenuOptions.end(), packageOperationSelector) == 0)) {

			if (cin.eof()) {
				cout << "\nStopping the program . . ." << endl;
				return -1;
			}

			packageMenuFailFlags = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		cout << "\x1B[2J\x1B[H";

	} while (packageMenuFailFlags);

	return packageOperationSelector;

}

void packageDisplayAll(Agency agency) {

	for (int i = 0; i < packagesInfo(agency.getPackagesFile()).size(); i++) {

		cout << packagesInfo(agency.getPackagesFile()).at(i) << endl;
		cout << endl;
		
	}
}

// return 0 if going back; else return -1
int packageDisplayOne(Agency agency) {

	bool packageSelectorFailFlag = false;
	vector <int> packageNumbers;
	int packageSelection;

	do {
		packageSelectorFailFlag = false;
		for (int i = 0; i < packagesInfo(agency.getPackagesFile()).size(); i++) {

			cout << "Package #" << abs(packagesInfo(agency.getPackagesFile()).at(i).getId()) << " ("
				<< packagesInfo(agency.getPackagesFile()).at(i).getPlaces().at(0) << ")";

			packageNumbers.push_back(abs(packagesInfo(agency.getPackagesFile()).at(i).getId()));

			if (packagesInfo(agency.getPackagesFile()).at(i).getId() < 0) {
				cout << "\t[Unavailable Package]";
			}
			cout << endl;
		}

		cout << "\nPlease insert the corresponding number: ";
		cin >> packageSelection;

		cout << "\x1B[2J\x1B[H";

		if (packageSelection == 0) {
			return 0;
		}

		if ((cin.fail()) || (count(packageNumbers.begin(), packageNumbers.end(), packageSelection) == 0)) {

			if (cin.eof()) {
				cout << "\nStopping the program . . ." << endl;
				return 0;
			}

			packageSelectorFailFlag = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		cout << "\x1B[2J\x1B[H";

	} while (packageSelectorFailFlag);

	cout << packagesInfo(agency.getPackagesFile()).at(packageSelection - 1) << endl;

	return -1;
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
		cout << "A" << endl;
		validDate = false;
	}

	// year verification
	else if (ToEvaluateDate.getYear() < referenceDate.getYear()) {
		cout << "B" << endl;
		validDate = false;
	}

	// same year, month verification
	else if ((ToEvaluateDate.getYear() == referenceDate.getYear()) && (ToEvaluateDate.getMonth() < referenceDate.getMonth())) {
		cout << "C" << endl;
		validDate = false;
	}

	else if ((ToEvaluateDate.getYear() == referenceDate.getYear()) && (ToEvaluateDate.getMonth() == referenceDate.getMonth()) && (ToEvaluateDate.getDay() < referenceDate.getDay())) {
		cout << "D" << endl;
		validDate = false;
	}

	else if (daysOfMonth(ToEvaluateDate.getMonth(), ToEvaluateDate.getYear()) < ToEvaluateDate.getDay()) {
		cout << "E" << endl;
		validDate = false;
	}

	return validDate;
}


// ISSUE: FIRST DATE AND SECOND DATE GET THE DEFAULT VALUE (CURRENT DATE)
// AND DON'T UPDATE
// POSSIBLE FIX: SET FOR EACH ONE THE DAY, MONTH AND YEAR
// (FIRSTDATE.SETDAY(), ETC...)
// TRY TO INITIALIZE WITH THE STRING ?
int displayBetweenDates(Agency agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	Date currentDate;
	
	bool firstDateFailInput, secondDateFailInput;
	Date firstDate, secondDate;
	string firstDateString, secondDateString;

	do {
		firstDateFailInput = false;

		cout << "First Date (YYYY / MM / DD) : ";
		getline(cin >> ws, firstDateString);
		
		if (firstDateString == to_string(0)) {
			return 0;
		}

		if (cin.fail()) {
			if (cin.eof()) {
				return -1;
			}
			cin.clear();
			cin.ignore(1000, '\n');
		}

		//Date firstDate(firstDateString);
		// firstDate.setDay(10);

		if (!checkDate(firstDate, currentDate)) {
			firstDateFailInput = true;
		}

	} while (firstDateFailInput);


	do {
		secondDateFailInput = false;

		cout << "Second Date (YYYY / MM / DD) : ";
		getline(cin >> ws, secondDateString);

if (secondDateString == to_string(0)) {
	return 0;
}

if (cin.fail()) {
	if (cin.eof()) {
		return 0;
	}
	cin.clear();
	cin.ignore(1000, '\n');
}

Date secondDate(secondDateString);

if (!checkDate(secondDate, firstDate)) {
	secondDateFailInput = true;
}

	} while (secondDateFailInput);

	cout << "HI" << endl; // it goes through
	cout << "Dates: " << endl;
	cout << firstDate << endl;
	cout << secondDate << endl;
	cout << "---" << endl;
	bool validLowerBound = false, validUpperBound = false;
	vector<Package> validPackages;

	for (int i = 0; i < packagesInfo(agency.getPackagesFile()).size(); i++) {

		validLowerBound = checkDate(packagesInfo(agency.getPackagesFile()).at(i).getBeginDate(), firstDate);

		if (validLowerBound) {
			validUpperBound = checkDate(secondDate, packagesInfoVector.at(i).getEndDate());
		}

		if (validLowerBound && validUpperBound) {
			cout << i << endl;
			validPackages.push_back(packagesInfoVector.at(i));
		}

	}


	for (int i = 0; i < validPackages.size(); i++) {
		cout << "me" << endl;
		cout << validPackages.at(i) << endl;
		cout << endl;

	}

	return -1;
}


int displayForPlace(Agency agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	vector<Package> packagesToDisplay;


	string placeInputString;
	bool placeNotFound = false;

	do {

		cin.clear();
		cin.ignore(1000, '\n');

		placeNotFound = false;
		cout << "Place to look for: ";
		getline(cin, placeInputString);

		if (cin.fail()) {

			if (cin.eof()) {
				return 0;
			}
		
			placeNotFound = true;
		}

		else if (placeInputString == "0") {
			cout << "\x1B[2J\x1B[H";
			return 0;
		}

	} while (placeNotFound);

	cout << endl;
	// tirar espaços no Place to look for ?
	// e tirar espaços das strings do vetor que tem os lugares de cada package?
	for (int i = 0; i < packagesInfoVector.size(); i++) {

		for (int j = 0; j < packagesInfoVector.at(i).getPlaces().size(); j++) {

			if (placeInputString == packagesInfoVector.at(i).getPlaces().at(j)) {
				packagesToDisplay.push_back(packagesInfoVector.at(i));
			}
			// cout << packagesInfoVector.at(i).getPlaces().at(j);
			// cout << endl;
		}
		// cout << endl;
	}

	if (packagesToDisplay.size() == 0) {
		cout << "No package meets the requirement" << endl;
	}

	else {
		for (int k = 0; k < packagesToDisplay.size(); k++) {
			cout << packagesToDisplay.at(k) << endl;
			cout << endl;
		}
	}

	return -1;
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