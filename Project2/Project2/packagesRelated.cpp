#include "utilities.h"
#include "clientClass.h"
#include "packagesRelated.h"

#include <utility>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;

// invert a map to a multimap
template<typename K, typename V>
multimap<V, K, greater<V>> invertMap(map<K, V> const &mapToInvert) {

	multimap<V, K, greater<V> > invertedMultiMap;

	for (auto const &pair : mapToInvert) {
		invertedMultiMap.insert(make_pair(pair.second, pair.first));
	}

	return invertedMultiMap;

}


// write to packs.txt from a vector
void writePackagesFromVector(string &packagesFileName, int &lastCreated, vector<Package> &packagesInfoVector) {

	ofstream packagesFileInput(packagesFileName);

	if (packagesFileInput.is_open()) {

		packagesFileInput << lastCreated << endl;

		for (int i = 0; i < packagesInfoVector.size(); i++) {

			if (i == 0 && packagesInfoVector.size() > 1) {

				packagesFileInput << packagesInfoVector.at(i).getId() << endl;

				for (int j = 0; j < packagesInfoVector.at(i).getPlaces().size(); j++) {

					if (j == 0) {
						if (packagesInfoVector.at(i).getPlaces().size() > 1) {
							packagesFileInput << packagesInfoVector.at(i).getPlaces().at(j) << " - ";

						}
						else {
							packagesFileInput << packagesInfoVector.at(i).getPlaces().at(j);
						}

					}

					else {
						if (j == 1) {
							packagesFileInput << packagesInfoVector.at(i).getPlaces().at(j);
						}
						else {
							packagesFileInput << ", " << packagesInfoVector.at(i).getPlaces().at(j);
						}
					}
				}
				packagesFileInput << endl;
				packagesFileInput << packagesInfoVector.at(i).getBeginDate() << endl;
				packagesFileInput << packagesInfoVector.at(i).getEndDate() << endl;
				packagesFileInput << packagesInfoVector.at(i).getPricePer() << endl;
				packagesFileInput << packagesInfoVector.at(i).getMaxPeople() << endl;
				packagesFileInput << packagesInfoVector.at(i).getSold() << endl;
			}

			else {
				packagesFileInput << "::::::::::" << endl;

				packagesFileInput << packagesInfoVector.at(i).getId() << endl;

				for (int j = 0; j < packagesInfoVector.at(i).getPlaces().size(); j++) {

					if (j == 0) {
						if (packagesInfoVector.at(i).getPlaces().size() > 1) {
							packagesFileInput << packagesInfoVector.at(i).getPlaces().at(j) << " - ";

						}
						else {
							packagesFileInput << packagesInfoVector.at(i).getPlaces().at(j);
						}

					}

					else {
						if (j == 1) {
							packagesFileInput << packagesInfoVector.at(i).getPlaces().at(j);
						}
						else {
							packagesFileInput << ", " << packagesInfoVector.at(i).getPlaces().at(j);
						}
					}
				}

				packagesFileInput << endl;
				packagesFileInput << packagesInfoVector.at(i).getBeginDate() << endl;
				packagesFileInput << packagesInfoVector.at(i).getEndDate() << endl;
				packagesFileInput << packagesInfoVector.at(i).getPricePer() << endl;
				packagesFileInput << packagesInfoVector.at(i).getMaxPeople() << endl;
				packagesFileInput << packagesInfoVector.at(i).getSold() << endl;
			}

		}

		packagesFileInput.close();
	}
}


// outputs to the terminal the information of all packages
void packageDisplayAll(Agency &agency) {

	for (int i = 0; i < packagesInfo(agency.getPackagesFile()).size(); i++) {

		cout << packagesInfo(agency.getPackagesFile()).at(i) << endl;
		cout << endl;

	}
}


// return 0 if going back; else return -1
// outputs to the terminal the information of a specific package
int packageDisplayOne(Agency &agency) {

	bool packageSelectorFailFlag = false;
	vector <int> packageNumbers = { 0 };
	int packageSelection;

	// Input control for the package choice
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

		else if (packageSelection == 0) {
			return 0;
		}

		cout << "\x1B[2J\x1B[H";

	} while (packageSelectorFailFlag);

	// output to the terminal the selected package
	cout << packagesInfo(agency.getPackagesFile()).at(packageSelection - 1) << endl;

	return -1;
}


// outputs to the terminal the packages that are between 2 specific dates
int displayBetweenDates(Agency &agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	Date currentDate;

	bool firstDateFailInput, secondDateFailInput;
	Date firstDate, secondDate;
	string firstDateString, secondDateString;

	// Input control for the begin date
	do {
		firstDateFailInput = false;

		cout << "First Date (YYYY / MM / DD) : ";
		getline(cin >> ws, firstDateString);

		if (firstDateString == to_string(0)) {
			return 0;
		}

		if (cin.fail()) {
			if (cin.eof()) {
				return 0;
			}
			cin.clear();
			cin.ignore(1000, '\n');
		}

		Date firstDateS(firstDateString);
		firstDate = firstDateS;

		// check if the begin date is after the current date
		if (!checkDate(firstDate, currentDate)) {
			firstDateFailInput = true;
		}

	} while (firstDateFailInput);

	// Input control for the end date
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

		Date secondDateS(secondDateString);
		secondDate = secondDateS;

		// check if the end date is after the begin date
		if (!checkDate(secondDate, firstDate)) {
			secondDateFailInput = true;
		}

	} while (secondDateFailInput);


	bool validLowerBound = false, validUpperBound = false;
	vector<Package> validPackages;

	for (int i = 0; i < packagesInfo(agency.getPackagesFile()).size(); i++) {

		validLowerBound = checkDate(packagesInfo(agency.getPackagesFile()).at(i).getBeginDate(), firstDate);

		if (validLowerBound) {
			validUpperBound = checkDate(secondDate, packagesInfoVector.at(i).getEndDate());
		}

		if (validLowerBound && validUpperBound) {
			validPackages.push_back(packagesInfoVector.at(i));
		}
	}

	// output to the terminal the packages that meet the requirements
	for (int i = 0; i < validPackages.size(); i++) {
		cout << validPackages.at(i) << endl;
		cout << endl;

	}

	return -1;
}


// outputs to the terminal the packages for a specific place
int displayForPlace(Agency &agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	vector<Package> packagesToDisplay;
	
	string placeInputString;
	bool placeNotFound = false;

	// Input control for the place to search for
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

		else if (trimString(placeInputString) == "0") {
			cout << "\x1B[2J\x1B[H";
			return 0;
		}

	} while (placeNotFound);

	cout << endl;

	for (int i = 0; i < packagesInfoVector.size(); i++) {

		for (int j = 0; j < packagesInfoVector.at(i).getPlaces().size(); j++) {

			if (trimString(placeInputString) == packagesInfoVector.at(i).getPlaces().at(j)) {
				packagesToDisplay.push_back(packagesInfoVector.at(i));
			}
		}
	}

	if (packagesToDisplay.size() == 0) {
		cout << "No package meets the requirement" << endl;
	}

	// output to the terminal the packages that meet the requirements
	else {
		for (int k = 0; k < packagesToDisplay.size(); k++) {
			cout << packagesToDisplay.at(k) << endl;
			cout << endl;
		}
	}

	return -1;

}


// outputs to the terminal the packages that are between 2 specific dates and for a specific place
int displayDateAndPlace(Agency &agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	Date currentDate;

	// Dates

	bool firstDateFailInput, secondDateFailInput;
	Date firstDate, secondDate;
	string firstDateString, secondDateString;
	
	// Input control for the begin date
	do {
		firstDateFailInput = false;

		cout << "First Date (YYYY / MM / DD) : ";
		getline(cin >> ws, firstDateString);

		if (firstDateString == to_string(0)) {
			cout << "\x1B[2J\x1B[H";
			return 0;
		}

		if (cin.fail()) {
			if (cin.eof()) {
				return 0;
			}
			cin.clear();
			cin.ignore(1000, '\n');
		}

		Date firstDateS(firstDateString);
		firstDate = firstDateS;

		// check if the begin date is after the current date
		if (!checkDate(firstDate, currentDate)) {
			firstDateFailInput = true;
		}

	} while (firstDateFailInput);

	// Input control for the end date
	do {
		secondDateFailInput = false;

		cout << "Second Date (YYYY / MM / DD) : ";
		getline(cin >> ws, secondDateString);

		if (secondDateString == to_string(0)) {
			cout << "\x1B[2J\x1B[H";
			return 0;
		}

		if (cin.fail()) {
			if (cin.eof()) {
				return 0;
			}
			cin.clear();
			cin.ignore(1000, '\n');
		}

		Date secondDateS(secondDateString);
		secondDate = secondDateS;

		// check if the end date is after the begin date
		if (!checkDate(secondDate, firstDate)) {
			secondDateFailInput = true;
		}

	} while (secondDateFailInput);

	bool validLowerBound = false, validUpperBound = false;
	vector<Package> validPackages;

	for (int i = 0; i < packagesInfo(agency.getPackagesFile()).size(); i++) {

		validLowerBound = checkDate(packagesInfo(agency.getPackagesFile()).at(i).getBeginDate(), firstDate);

		if (validLowerBound) {
			validUpperBound = checkDate(secondDate, packagesInfoVector.at(i).getEndDate());
		}

		if (validLowerBound && validUpperBound) {
			validPackages.push_back(packagesInfoVector.at(i));
		}

	}


	// Places

	vector<Package> packagesToDisplay;

	string placeInputString;
	bool placeNotFound = false;

	// Input control for the place to search for
	do {

		placeNotFound = false;
		cout << "Place to look for: ";
		getline(cin, placeInputString);

		if (cin.fail()) {

			if (cin.eof()) {
				return 0;
			}

			placeNotFound = true;
		}

		else if (trimString(placeInputString) == "0") {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\x1B[2J\x1B[H";
			return 0;
		}

	} while (placeNotFound);

	cout << endl;

	for (int i = 0; i < validPackages.size(); i++) {

		for (int j = 0; j < validPackages.at(i).getPlaces().size(); j++) {

			if (trimString(placeInputString) == validPackages.at(i).getPlaces().at(j)) {
				packagesToDisplay.push_back(validPackages.at(i));
			}
		}
	}

	if (packagesToDisplay.size() == 0) {
		cout << "No package meets the requirements" << endl;
	}

	// output to the terminal the packages that meet the requirements
	else {
		for (int k = 0; k < packagesToDisplay.size(); k++) {
			cout << packagesToDisplay.at(k) << endl;
			cout << endl;
		}
	}

	return -1;
}


// add a package
int addPackage(Agency &agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	string packagesFileName = agency.getPackagesFile();

	string textLine;
	int lastCreated;
	ifstream packagesFile(packagesFileName);

	bool firstLine = true;

	while (getline(packagesFile, textLine)) {

		if (firstLine) {
			lastCreated = abs(stoi(textLine));
			firstLine = false;
			break;
		}
	}

	packagesFile.close();

	Package newPackage;

	newPackage.setId(abs(lastCreated) + 1);

	lastCreated += 1;

	string placesString;
	cout << "Places ([main place] - [other], [other], ...) : ";
	getline(cin >> ws, placesString);

	if (placesString == to_string(0)) {
		return 0;
	}

	if (cin.fail()) {
		if (cin.eof()) {
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
	}

	newPackage.setPlaces(stringToStringVector(placesString));


	Date currentDate;

	bool startDateFailInput, endDateFailInput;
	Date startDate, endDate;
	string startDateString, endDateString;

	// Input control for the begin date
	do {
		startDateFailInput = false;

		cout << "First Date (YYYY / MM / DD) : ";
		getline(cin >> ws, startDateString);

		if (startDateString == to_string(0)) {
			return 0;
		}

		if (cin.fail()) {
			if (cin.eof()) {
				return 0;
			}
			cin.clear();
			cin.ignore(1000, '\n');
		}
		
		Date startDateS(startDateString);
		startDate = startDateS;

		if (!checkDate(startDate, currentDate)) {
			startDateFailInput = true;
		}

	} while (startDateFailInput);

	newPackage.setBeginDate(startDate);

	// Input control for the end date
	do {
		endDateFailInput = false;

		cout << "Second Date (YYYY / MM / DD) : ";
		getline(cin >> ws, endDateString);

		if (endDateString == to_string(0)) {
			return 0;
		}

		if (cin.fail()) {
			if (cin.eof()) {
				return 0;
			}
			cin.clear();
			cin.ignore(1000, '\n');
		}

		Date endDateS(endDateString);
		endDate = endDateS;

		if (!checkDate(endDate, startDate)) {
			endDateFailInput = true;
		}

	} while (endDateFailInput);

	newPackage.setEndDate(endDate);



	bool pricePerInputFail;
	double pricePer;

	// Input control for price per person (negative number not allowed)
	do {
		pricePerInputFail = false;
		cout << "Price per person: ";
		cin >> pricePer;

		if (pricePer == 0) {
			return 0;
		}

		if (pricePer < 0) {
			pricePerInputFail = true;
		}

		if (cin.fail()) {
			if (cin.eof()) {
				cin.clear();
				cin.ignore(1000, '\n');
				return 0;
			}

			else {
				cout << "\n(Invalid input)" << endl;
				pricePerInputFail = true;
				cin.clear();
				cin.ignore(1000, '\n');
			}

		}

	} while (pricePerInputFail);

	newPackage.setPricePer(pricePer);

	
	bool totalInputFail;
	int maxPeople;

	// changing the maximum number of people
	do {
		totalInputFail = false;
		cout << "Max number of people: ";
		cin >> maxPeople;

		if (maxPeople == 0) {
			return 0;
		}

		if (maxPeople < 0) {
			totalInputFail = true;
		}

		if (cin.fail()) {
			cout << "\n(Invalid input)" << endl;
			totalInputFail = true;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (totalInputFail);

	newPackage.setMaxPeople(maxPeople);


	bool soldInputFail;
	int sold;

	// Input control for the number of sold (negative number not allowed)
	do {
		soldInputFail = false;
		cout << "Sold: ";
		cin >> sold;

		/*if (sold == 0) {
			return 0;
		}*/

		if (sold < 0) {
			soldInputFail = true;
		}

		if (cin.fail()) {
			cout << "\nInvalid input)" << endl;
			soldInputFail = true;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (soldInputFail);

	newPackage.setSold(sold);

	packagesInfoVector.push_back(newPackage);
	
	// writes to the file the updated information
	writePackagesFromVector(packagesFileName, lastCreated, packagesInfoVector);

	return -1;
}


// change a specific package information
int changePackage(Agency &agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	vector <int> possibleChoices;
	bool invalidPackageInputFlag;
	int packageSelector;

	// Input control for package to change
	do {
		invalidPackageInputFlag = false;

		cout << "Package to Change: " << endl;

		for (int i = 0; i < packagesInfoVector.size(); i++) {
			if (abs(packagesInfoVector.at(i).getId()) != packagesInfoVector.at(i).getId()) {
				cout << "  #" << abs(packagesInfoVector.at(i).getId())
					<< " " << packagesInfoVector.at(i).getPlaces().at(0)
					<< "\t\t[Unavailable Package]" << endl;
			}
			else {
				cout << "  #" << abs(packagesInfoVector.at(i).getId())
					<< " " << packagesInfoVector.at(i).getPlaces().at(0)
					<< endl;
			}
			possibleChoices.push_back(abs(packagesInfoVector.at(i).getId()));
		}


		cout << "Please insert the corresponding number: ";
		cin >> packageSelector;

		if (packageSelector == 0) {
			return 0;
		}

		if ((cin.fail()) || (count(possibleChoices.begin(), possibleChoices.end(), packageSelector) == 0)) {

			if (cin.eof()) {
				return 0;
			}

			invalidPackageInputFlag = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}


		cout << "\x1B[2J\x1B[H";

	} while (invalidPackageInputFlag);
	

	int packageToChangePosition;

	for (int i = 0; i < packagesInfoVector.size(); i++) {
		if (abs(packagesInfoVector.at(i).getId()) == packageSelector) {
			packageToChangePosition = i;
			break;
		}
	}


	bool invalidChangeSelection;
	vector<int> changeOptions = { 1, 2, 3, 4, 5, 6 };
	int changeSelection;

	// Input control for the change selection
	do {
		invalidChangeSelection = false;

		cout << packagesInfoVector.at(packageToChangePosition) << endl;
		cout << endl;

		cout << "Change Options" << endl;
		cout << " 1. Places" << endl;
		cout << " 2. Begin Date" << endl;
		cout << " 3. End Date" << endl;
		cout << " 4. Price per Person" << endl;
		cout << " 5. Maximum number of people" << endl;
		cout << " 6. Sold" << endl;


		cout << endl;
		cout << "Please insert the corresponding number: ";
		cin >> changeSelection;

		if (changeSelection == 0) {
			cout << "\x1B[2J\x1B[H";
			return 0;
		}

		if ((cin.fail()) || (count(changeOptions.begin(), changeOptions.end(), changeSelection) == 0)) {

			if (cin.eof()) {
				return 0;
			}

			invalidChangeSelection = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		cout << "\x1B[2J\x1B[H";

	} while (invalidChangeSelection);


	string placeChangesString;

	bool startDateFailInput;
	string startDateString;
	Date currentDate;
	Date startDate;

	bool endDateFailInput;
	string endDateString;
	Date endDate;

	bool pricePerInputFail;
	double pricePer;

	bool totalInputFail;
	int maxPeople;

	bool soldInputFail;
	int sold;

	switch (changeSelection) {

		// changing the places
		case 1:
			cout << "Places ([main place] - [other], [other], ...) : ";
			getline(cin >> ws, placeChangesString);

			if (placeChangesString == to_string(0)) {
				return 0;
			}

			if (cin.fail()) {
				if (cin.eof()) {
					return 0;
				}
				cin.clear();
				cin.ignore(1000, '\n');
			}

			packagesInfoVector.at(packageToChangePosition).setPlaces(stringToStringVector(placeChangesString));

		// changing the begin date
		case 2:

			// Input control for the begin date
			do {
				startDateFailInput = false;

				cout << "First Date (YYYY / MM / DD) : ";
				getline(cin >> ws, startDateString);

				if (startDateString == to_string(0)) {
					return 0;
				}

				if (cin.fail()) {
					if (cin.eof()) {
						return 0;
					}
					cin.clear();
					cin.ignore(1000, '\n');
				}

				Date startDateS(startDateString);
				startDate = startDateS;

				if (!checkDate(startDate, currentDate)) {
					startDateFailInput = true;
				}

			} while (startDateFailInput);

			packagesInfoVector.at(packageToChangePosition).setBeginDate(startDate);

		// changing the end date
		case 3:

			// Input control for the end date
			do {
				endDateFailInput = false;

				cout << "Second Date (YYYY / MM / DD) : ";
				getline(cin >> ws, endDateString);

				if (endDateString == to_string(0)) {
					return 0;
				}

				if (cin.fail()) {
					if (cin.eof()) {
						return 0;
					}
					cin.clear();
					cin.ignore(1000, '\n');
				}

				Date endDateS(endDateString);
				endDate = endDateS;

				if (!checkDate(endDate, startDate)) {
					endDateFailInput = true;
				}

			} while (endDateFailInput);

			packagesInfoVector.at(packageToChangePosition).setEndDate(endDate);

		// changing the price per person
		case 4:

			// Input control for price per person (negative number not allowed)
			do {
				pricePerInputFail = false;
				cout << "Price per person: ";
				cin >> pricePer;

				if (pricePer == 0) {
					return 0;
				}

				if (pricePer < 0) {
					pricePerInputFail = true;
				}

				if (cin.fail()) {
					if (cin.eof()) {
						cin.clear();
						cin.ignore(1000, '\n');
						return 0;
					}

					else {
						cout << "\n(Invalid input)" << endl;
						pricePerInputFail = true;
						cin.clear();
						cin.ignore(1000, '\n');
					}

				}

			} while (pricePerInputFail);

			packagesInfoVector.at(packageToChangePosition).setPricePer(pricePer);

		// changing the maximum number of people
		case 5:

			// Input control for max number of people (negative number not allowed)
			do {
				totalInputFail = false;
				cout << "Max number of people: ";
				cin >> maxPeople;

				if (maxPeople == 0) {
					return 0;
				}

				if (maxPeople < 0) {
					totalInputFail = true;
				}

				if (cin.fail()) {
					cout << "\n(Invalid input)" << endl;
					totalInputFail = true;
					cin.clear();
					cin.ignore(1000, '\n');
				}
			} while (totalInputFail);

			packagesInfoVector.at(packageToChangePosition).setMaxPeople(maxPeople);

		// changing the number of sold "seats"
		case 6:

			// Input control for the number of sold (negative number not allowed)
			do {
				soldInputFail = false;
				cout << "Sold: ";
				cin >> sold;

				if (sold < 0) {
					soldInputFail = true;
				}

				if (cin.fail()) {
					cout << "\nInvalid input)" << endl;
					soldInputFail = true;
					cin.clear();
					cin.ignore(1000, '\n');
				}
			} while (soldInputFail);

			packagesInfoVector.at(packageToChangePosition).setSold(sold);
	}


	string packagesFileName = agency.getPackagesFile();

	string textLine;
	int lastCreated;
	ifstream packagesFile(packagesFileName);

	bool firstLine = true;

	while (getline(packagesFile, textLine)) {

		if (firstLine) {
			lastCreated = abs(stoi(textLine));		// last package created was already unavailable?
			firstLine = false;
			break;
		}
	}

	// writes to the file the updated information
	writePackagesFromVector(packagesFileName, lastCreated, packagesInfoVector);

	return -1;
}


// change a specific package to become unavailable or the opposite (from unavailable to available)
int unavailablePackage(Agency &agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	vector <int> possibleChoices;	// vector that will contain the possible packages to choose from
	bool invalidPackageInputFlag;
	int packageSelector;

	// Input control for the selection of the package
	do {
		invalidPackageInputFlag = false;

		cout << "Package to Change from Available to Unavailable or vice-versa: " << endl;

		for (int i = 0; i < packagesInfoVector.size(); i++) {
			if (abs(packagesInfoVector.at(i).getId()) != packagesInfoVector.at(i).getId()) {
				cout << "  #" << abs(packagesInfoVector.at(i).getId())
					<< " " << packagesInfoVector.at(i).getPlaces().at(0)
					<< "\t\t[Unavailable Package]" << endl;
			}
			else {
				cout << "  #" << abs(packagesInfoVector.at(i).getId())
					<< " " << packagesInfoVector.at(i).getPlaces().at(0)
					<< endl;
			}
			possibleChoices.push_back(abs(packagesInfoVector.at(i).getId()));
		}


		cout << "Please insert the corresponding number: ";
		cin >> packageSelector;

		if (packageSelector == 0) {
			return 0;
		}

		if ((cin.fail()) || (count(possibleChoices.begin(), possibleChoices.end(), packageSelector) == 0)) {

			if (cin.eof()) {
				return 0;
			}

			invalidPackageInputFlag = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		cout << "\x1B[2J\x1B[H";

	} while (invalidPackageInputFlag);


	int packageToChangePosition;

	// packageToChangePosition get the index at which the corresponding pack is
	for (int i = 0; i < packagesInfoVector.size(); i++) {
		if (abs(packagesInfoVector.at(i).getId()) == packageSelector) {
			packageToChangePosition = i;
			break;
		}
	}

	// negates the id (if negative, becomes positive - available; if positive, becomes negative - unavailable)
	packagesInfoVector.at(packageToChangePosition).setId(-packagesInfoVector.at(packageToChangePosition).getId());


	string packagesFileName = agency.getPackagesFile();

	string textLine;
	int lastCreated;
	ifstream packagesFile(packagesFileName);

	bool firstLine = true;

	while (getline(packagesFile, textLine)) {

		if (firstLine) {
			lastCreated = abs(stoi(textLine));		// last package created was already unavailable?
			firstLine = false;
			break;
		}
	}

	// writes to the file the updated information
	writePackagesFromVector(packagesFileName, lastCreated, packagesInfoVector);

	return -1;
}


// outputs to the terminal the information of each package that has been bought by at least one client
void packageDisplayAllClients(Agency &agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	vector<Client> clientsInfoVector = clientsInfo(agency);
	vector<Package> packagesToDisplay;
	vector<int> alreadyInVector;

	// iterates over the clients
	for (int i = 0; i < clientsInfoVector.size(); i++) {

		// iterates over the client's packages bought 
		for (int j = 0; j < clientsInfoVector.at(i).getPackageList().size(); j++) {

			// iterates over the vector containing all packages information
			for (int k = 0; k < packagesInfoVector.size(); k++) {

				if (clientsInfoVector.at(i).getPackageList().at(j).getId() == packagesInfoVector.at(k).getId()) {

					// if the packages's id matches with one of the packages (previous "if" statement)
					// and the package hasn't appeared yet, it gets added to the packages to display
					if (find(alreadyInVector.begin(), alreadyInVector.end(), packagesInfoVector.at(k).getId()) == alreadyInVector.end()) {
						alreadyInVector.push_back(packagesInfoVector.at(k).getId());
						packagesToDisplay.push_back(packagesInfoVector.at(k));
					}
				}
			}
		}
	}
	
	// displays the packages 
	for (int i = 0; i < packagesToDisplay.size(); i++) {
		cout << packagesToDisplay.at(i) << endl;
		cout << endl;
	}

}


// outputs to the terminal the packages' Info for the packages bought by a specific client
int packageDisplayOneClient(Agency &agency) {
	
	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	vector<Client> clientsInfoVector = clientsInfo(agency);
	vector<Package> packagesToDisplay;

	bool clientSelectorFailFlag = false;
	vector <int> clientNumbers = {-1};
	int clientSelection;

	// Input control for the selection of the client
	do {
		clientSelectorFailFlag = false;

		for (int i = 0; i < clientsInfo(agency).size(); i++) {

			cout << "Client #" << i + 1 << ": "
				<< clientsInfo(agency).at(i).getName() << endl;
			clientNumbers.push_back(i);
		}

		cout << "\nPlease insert the corresponding number: ";
		cin >> clientSelection;

		cout << "\x1B[2J\x1B[H";


		if ((cin.fail()) || (count(clientNumbers.begin(), clientNumbers.end(), clientSelection - 1) == 0)) {

			if (cin.eof()) {
				cout << "\nStopping the program . . ." << endl;
				return 0;
			}

			clientSelectorFailFlag = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		// Input '0' to go to the previous menu
		else if (clientSelection == 0) {
			return 0;
		}
		

		cout << "\x1B[2J\x1B[H";


	} while (clientSelectorFailFlag);

	// number entered is not the real index position of the client information in the vector
	int realClientIndexInVector = clientSelection - 1;

	for (int i = 0; i < clientsInfoVector.at(realClientIndexInVector).getPackageList().size(); i++) {

		for (int j = 0; j < packagesInfoVector.size(); j++) {
			if (clientsInfoVector.at(realClientIndexInVector).getPackageList().at(i).getId() == packagesInfoVector.at(j).getId()) {
				packagesToDisplay.push_back(packagesInfoVector.at(j));
			}
		}
	}

	// displays the packages of the chosen client
	for (int i = 0; i < packagesToDisplay.size(); i++) {
		cout << packagesToDisplay.at(i) << endl;
		cout << endl;
	}

	return -1;
}


// outputs to the terminal the number of sold "seats" and the total value for each of the packages
void numberValueSoldPackages(Agency &agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());

	map <int, pair<int,int> > idSoldMap;	// key is the id of the package
	pair<int, int> soldValue;				// 1st element of the pair is the number of sold "seats", 2nd element is the total value (pricePer * soldSeats)

	// assigns to each place the number of sold "seats" and the total value
	for (int i = 0; i < packagesInfoVector.size(); i++) {
		soldValue.first = packagesInfoVector.at(i).getSold();
		soldValue.second = packagesInfoVector.at(i).getSold() * packagesInfoVector.at(i).getPricePer();
		idSoldMap[abs(packagesInfoVector.at(i).getId())] = soldValue;
	}

	// outputs to the terminal the number of sold "seats" and total revenue for each of the packages
	for (map<int, pair<int, int> >::const_iterator mi = idSoldMap.begin(); mi != idSoldMap.end(); mi++) {
		cout << endl;
		cout << "Package Number " << mi->first << " - " << packagesInfoVector.at(mi->first - 1).getPlaces().at(0) << endl;
		cout << "Sold: " << mi->second.first << "\tValue: " << mi->second.second << endl;
	}

}


// outputs to the terminal the N most visited Places
int mostVisitedPlaces(Agency &agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());

	map <string, int> placesFrequency;

	// map placesFrequency 
	for (int i = 0; i < packagesInfoVector.size(); i++) {

		for (int j = 0; j < packagesInfoVector.at(i).getPlaces().size(); j++) {

			if (placesFrequency.find(packagesInfoVector.at(i).getPlaces().at(j)) == placesFrequency.end()) {
				placesFrequency[packagesInfoVector.at(i).getPlaces().at(j)] = packagesInfoVector.at(i).getSold();
			}

			else {
				placesFrequency[packagesInfoVector.at(i).getPlaces().at(j)] += packagesInfoVector.at(i).getSold();
			}
		}
	}

	// inverts the map to a multimap
	multimap<int, string, greater<int> > descending = invertMap(placesFrequency);

	bool invalidNumberFlag;
	int nMostVisited;

	// Input control for the number of places to display
	do {
		invalidNumberFlag = false;

		cout << "N most visited places: ";
		cin >> nMostVisited;

		if ((cin.fail()) || (nMostVisited > descending.size()) || (nMostVisited < 0)) {

			if (cin.eof()) {
				cout << "\nStopping the program . . ." << endl;
				return 0;
			}

			invalidNumberFlag = true;
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid input" << endl;
		}

		else if (nMostVisited == 0) {
			return 0;
		}
		cout << "\x1B[2J\x1B[H";

	} while (invalidNumberFlag);


	cout << nMostVisited << " Most Visited Places" << endl;

	// outputs the most "N" visited places and the number of visits for each one (frequency)
	for (auto const &pair : descending) {
		cout << "Place: " << setw(20) << pair.second << "\tFrequency: " << pair.first << endl;
		nMostVisited = nMostVisited - 1;
		if (nMostVisited <= 0) {
			break;
		}
	}

	return -1;
}