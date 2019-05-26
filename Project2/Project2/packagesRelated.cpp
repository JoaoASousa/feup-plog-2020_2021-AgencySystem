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

	// multimap ordered by the first element
	multimap<V, K, greater<V> > invertedMultiMap;

	for (auto const &pair : mapToInvert) {
		
		// Reverts and inserts each pair of the map in the multimap
		invertedMultiMap.insert(make_pair(pair.second, pair.first));
	}

	return invertedMultiMap;
}


// writes to the packages' file the information contained in the vector of packages
void writePackagesFromVector(string &packagesFileName, int &lastCreated, vector<Package> &packagesInfoVector) {

	ofstream packagesFileInput(packagesFileName);

	if (packagesFileInput.is_open()) {

		// write the id of the last package created 
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
void packageDisplayAll(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {

	for (int i = 0; i < packagesInfoVector.size(); i++) {

		cout << packagesInfoVector.at(i) << endl;
		cout << endl;
	}
}


// outputs to the terminal the information of a specific package
int packageDisplayOne(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {

	bool packageSelectorFailFlag = false;
	vector <int> packageNumbers = { 0 };
	int packageSelection;

	// Input control for the package choice
	do {
		packageSelectorFailFlag = false;
		for (int i = 0; i < packagesInfoVector.size(); i++) {

			cout << "Package #" << abs(packagesInfoVector.at(i).getId()) << " ("
				<< packagesInfoVector.at(i).getPlaces().at(0) << ")";

			packageNumbers.push_back(abs(packagesInfoVector.at(i).getId()));

			if (packagesInfoVector.at(i).getId() < 0) {
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
	cout << packagesInfoVector.at(packageSelection - 1) << endl;

	return -1;
}


// outputs to the terminal the packages that are between 2 specific dates
int displayBetweenDates(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {

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

	for (int i = 0; i < packagesInfoVector.size(); i++) {

		validLowerBound = checkDate(packagesInfoVector.at(i).getBeginDate(), firstDate);

		if (validLowerBound) {
			validUpperBound = checkDate(secondDate, packagesInfoVector.at(i).getEndDate());
		}

		if (validLowerBound && validUpperBound) {
			validPackages.push_back(packagesInfoVector.at(i));
		}
	}
	cout << endl;
	cout << endl;

	// output to the terminal the packages that meet the requirements
	for (int i = 0; i < validPackages.size(); i++) {
		cout << validPackages.at(i) << endl;
		cout << endl;

	}

	return -1;
}


// outputs to the terminal the packages for a specific place
int displayForPlace(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {

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
int displayDateAndPlace(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {

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

	for (int i = 0; i < packagesInfoVector.size(); i++) {

		validLowerBound = checkDate(packagesInfoVector.at(i).getBeginDate(), firstDate);

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
int addPackage(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector, int &lastCreated) {

	string packagesFileName = agency.getPackagesFile();
		
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

		if (sold < 0) {
			soldInputFail = true;
		}

		else if (sold > maxPeople) {
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

	return -1;
}


// change a specific package information
int changePackage(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {

	// vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	vector <int> possibleChoices;
	bool invalidPackageInputFlag;
	int packageSelector;

	// Input control for package to change
	do {
		invalidPackageInputFlag = false;
		cout << endl;
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
			cout << "\x1B[2J\x1B[H";
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

		cout << endl;
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

			cout << "\nCurrent Places: ";

			for (int i = 0; i < packagesInfoVector.at(packageToChangePosition).getPlaces().size(); i++) {

				if (i == 0) {
					if (packagesInfoVector.at(packageToChangePosition).getPlaces().size() > 1) {
						cout << packagesInfoVector.at(packageToChangePosition).getPlaces().at(i) << " - ";

					}
					else {
						cout << packagesInfoVector.at(packageToChangePosition).getPlaces().at(i);
					}

				}

				else {
					if (i == 1) {
						cout << packagesInfoVector.at(packageToChangePosition).getPlaces().at(i);
					}
					else {
						cout << ", " << packagesInfoVector.at(packageToChangePosition).getPlaces().at(i);
					}
				}
			}
			cout << endl;
			cout << endl;
			cout << "Updated Places ([main place] - [other], [other], ...) : ";
			getline(cin >> ws, placeChangesString);

			if (placeChangesString == to_string(0)) {
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
			cout << "\x1B[2J\x1B[H";
			packagesInfoVector.at(packageToChangePosition).setPlaces(stringToStringVector(placeChangesString));
			break;

		// changing the begin date
		case 2:

			// Input control for the begin date
			do {
				startDateFailInput = false;
				cout << endl;
				cout << "Current Begin Date: " << packagesInfoVector.at(packageToChangePosition).getBeginDate() << endl;
				cout << endl;
				cout << endl;
				cout << "Updated Begin Date (YYYY / MM / DD) : ";
				getline(cin >> ws, startDateString);

				if (startDateString == to_string(0)) {
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

				Date startDateS(startDateString);
				startDate = startDateS;

				if (!checkDate(startDate, currentDate)) {
					startDateFailInput = true;
				}
				cout << "\x1B[2J\x1B[H";
			} while (startDateFailInput);

			packagesInfoVector.at(packageToChangePosition).setBeginDate(startDate);
			break;

		// changing the end date
		case 3:

			// Input control for the end date
			do {
				endDateFailInput = false;
				cout << endl;
				cout << "Current End Date: " << packagesInfoVector.at(packageToChangePosition).getEndDate() << endl;
				cout << endl;
				cout << endl;
				cout << "Updated End Date (YYYY / MM / DD) : ";
				getline(cin >> ws, endDateString);

				if (endDateString == to_string(0)) {
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

				Date endDateS(endDateString);
				endDate = endDateS;

				if (!checkDate(endDate, startDate)) {
					endDateFailInput = true;
				}
				cout << "\x1B[2J\x1B[H";
			} while (endDateFailInput);

			packagesInfoVector.at(packageToChangePosition).setEndDate(endDate);
			break;

		// changing the price per person
		case 4:

			// Input control for price per person (negative number not allowed)
			do {
				pricePerInputFail = false;
				cout << endl;
				cout << "Current Price per person: " << packagesInfoVector.at(packageToChangePosition).getPricePer() << endl;
				cout << endl;
				cout << endl;
				cout << "Updated Price per person: ";
				cin >> pricePer;

				if (pricePer == 0) {
					cout << "\x1B[2J\x1B[H";
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
				cout << "\x1B[2J\x1B[H";
			} while (pricePerInputFail);

			packagesInfoVector.at(packageToChangePosition).setPricePer(pricePer);
			break;

		// changing the maximum number of people
		case 5:

			// Input control for max number of people (negative number not allowed)
			do {
				totalInputFail = false;
				cout << endl;
				cout << "Current Max number of people: " << packagesInfoVector.at(packageToChangePosition).getMaxPeople() << endl;
				cout << endl;
				cout << endl;
				cout << "Updated Max number of people: ";
				cin >> maxPeople;

				if (maxPeople == 0) {
					cout << "\x1B[2J\x1B[H";
					return 0;
				}

				if (maxPeople < 0) {
					totalInputFail = true;
				}

				if (cin.fail()) {

					if (cin.eof()) {
						cin.clear();
						cin.ignore(1000, '\n');
						return 0;
					}

					cout << "\n(Invalid input)" << endl;
					totalInputFail = true;
					cin.clear();
					cin.ignore(1000, '\n');
				}
				cout << "\x1B[2J\x1B[H";
			} while (totalInputFail);

			packagesInfoVector.at(packageToChangePosition).setMaxPeople(maxPeople);
			break;

		// changing the number of sold "seats"
		case 6:

			// Input control for the number of sold (negative number not allowed)
			do {
				soldInputFail = false;
				cout << endl;
				cout << "Current number of Sold \"Seats\": " << packagesInfoVector.at(packageToChangePosition).getSold() << endl;
				cout << endl;
				cout << endl;
				cout << "Updated number of Sold \"Seats\": ";
				cin >> sold;

				if (sold < 0) {
					soldInputFail = true;
				}

				else if (sold > packagesInfoVector.at(packageToChangePosition).getMaxPeople()) {
					soldInputFail = true;
				}

				if (cin.fail()) {

					if (cin.eof()) {
						cin.clear();
						cin.ignore(1000, '\n');
						return 0;
					}

					cout << "\nInvalid input)" << endl;
					soldInputFail = true;
					cin.clear();
					cin.ignore(1000, '\n');
				}
				cout << "\x1B[2J\x1B[H";

			} while (soldInputFail);

			packagesInfoVector.at(packageToChangePosition).setSold(sold);
			break;
	}
	
	
	return -1;
}


// change a specific package to become unavailable or the opposite (from unavailable to available)
int unavailablePackage(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {

	vector <int> possibleChoices;	// vector that will contain the possible packages to choose from
	bool invalidPackageInputFlag;
	int packageSelector;

	// Input control for the selection of the package
	do {
		invalidPackageInputFlag = false;

		cout << "\nChoose a Package to Change from Available to Unavailable or vice-versa: " << endl;

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

		cout << endl;
		cout << "Please insert the corresponding number: ";
		cin >> packageSelector;

		if (packageSelector == 0) {
			cout << "\x1B[2J\x1B[H";
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
	

	return -1;
}


// outputs to the terminal the information of each package that has been bought by at least one client
void packageDisplayAllClients(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {

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
	
	cout << endl;

	// displays the packages 
	for (int i = 0; i < packagesToDisplay.size(); i++) {
		cout << endl;
		cout << packagesToDisplay.at(i) << endl;
		cout << endl;
	}

}


// outputs to the terminal the packages' Info for the packages bought by a specific client
int packageDisplayOneClient(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {
	
	vector<Package> packagesToDisplay;

	bool clientSelectorFailFlag = false;
	vector <int> clientNumbers = {-1};
	int clientSelection;

	// Input control for the selection of the client
	do {
		clientSelectorFailFlag = false;

		for (int i = 0; i < clientsInfoVector.size(); i++) {

			cout << "Client #" << i + 1 << ": "
				<< clientsInfoVector.at(i).getName() << endl;
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
			cout << "\x1B[2J\x1B[H";
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

	cout << endl;
	cout << "Packages Sold to " << clientsInfoVector.at(realClientIndexInVector).getName() << endl;
	cout << endl;

	// displays the packages of the chosen client
	for (int i = 0; i < packagesToDisplay.size(); i++) {
		cout << packagesToDisplay.at(i) << endl;
		cout << endl;
	}

	return -1;
}


// outputs to the terminal the number of sold "seats" and the total value for each of the packages
void numberValueSoldPackages(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {

	map <int, pair<int,int> > idSoldMap;	// key is the id of the package
	pair<int, int> soldValue;				// 1st element of the pair is the number of sold "seats", 2nd element is the total value (pricePer * soldSeats)

	// assigns to each place the number of sold "seats" and the total value
	for (int i = 0; i < packagesInfoVector.size(); i++) {
		soldValue.first = packagesInfoVector.at(i).getSold();
		soldValue.second = packagesInfoVector.at(i).getSold() * packagesInfoVector.at(i).getPricePer();
		idSoldMap[abs(packagesInfoVector.at(i).getId())] = soldValue;
	}

	// outputs to the terminal the number of sold "seats" and total revenue for each of the packages
	cout << endl;
	cout << "Packages\t\t\tSold\tRevenue\n" << endl;

	for (map<int, pair<int, int> >::const_iterator mi = idSoldMap.begin(); mi != idSoldMap.end(); mi++) {
		cout << "#" << mi->first << left << setw(4)  << " - " << setw(20) << left << packagesInfoVector.at(mi->first - 1).getPlaces().at(0);
		cout << "\t" << mi->second.first << "\t" << mi->second.second << endl;
	}

}


// outputs to the terminal the N most visited Places
int mostVisitedPlaces(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {

	map <string, int> placesFrequency;

	// map placesFrequency
	for (int i = 0; i < packagesInfoVector.size(); i++) {

		for (int j = 0; j < packagesInfoVector.at(i).getPlaces().size(); j++) {

			if (packagesInfoVector.at(i).getPlaces().size() > 1 && j == 0) {
				continue;
			}

			else{

				if (placesFrequency.find(packagesInfoVector.at(i).getPlaces().at(j)) == placesFrequency.end()) {
					placesFrequency[packagesInfoVector.at(i).getPlaces().at(j)] = packagesInfoVector.at(i).getSold();
				}

				else {
					placesFrequency[packagesInfoVector.at(i).getPlaces().at(j)] += packagesInfoVector.at(i).getSold();
				}
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

		cout << "N most visited places ( N <= "  << descending.size() << " ): ";
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
			cout << "\x1B[2J\x1B[H";
			return 0;
		}

		cout << "\x1B[2J\x1B[H";

	} while (invalidNumberFlag);


	cout << "\n The " << nMostVisited << " Most Visited Places" << endl;
	cout << endl;
	cout << " Place\t\tNumber of visits\n" << endl;

	// outputs the most "N" visited places and the number of visits for each one (frequency)
	for (auto const &pair : descending) {
		cout << " " << left << setw(15) << pair.second << left << setw(15) << pair.first << endl;
		nMostVisited = nMostVisited - 1;
		if (nMostVisited <= 0) {
			break;
		}
	}

	return -1;
}


// outputs to the terminal a Package Sugestion for each Client
int packageSugestion(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector) {

	map <string, int> placesFrequency;
	
	// "construction" of the map placesFrequency with unique places and their frequency
	for (int i = 0; i < packagesInfoVector.size(); i++) {

		for (int j = 0; j < packagesInfoVector.at(i).getPlaces().size(); j++) {

			if (packagesInfoVector.at(i).getPlaces().size() > 1 && j == 0) {
				continue;
			}

			else {

				if (placesFrequency.find(packagesInfoVector.at(i).getPlaces().at(j)) == placesFrequency.end()) {
					placesFrequency[packagesInfoVector.at(i).getPlaces().at(j)] = packagesInfoVector.at(i).getSold();
				}

				else {
					placesFrequency[packagesInfoVector.at(i).getPlaces().at(j)] += packagesInfoVector.at(i).getSold();
				}
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

	
	vector< vector<string> > clientsPlacesVisited;
	vector<string> oneClientPlacesVisited;
	string aPlace;

	// clientsPlacesVisited will have all the unique places visited by each client (each iteration)
	// (each client in a different element of the vector)
	for (int i = 0; i < clientsInfoVector.size(); i++) {
		oneClientPlacesVisited = {};
	
		for (int j = 0; j < clientsInfoVector.at(i).getPackageList().size(); j++) {

			for (int k = 0; k < clientsInfoVector.at(i).getPackageList().at(j).getPlaces().size(); k++) {

				aPlace = clientsInfoVector.at(i).getPackageList().at(j).getPlaces().at(k);
				if (clientsInfoVector.at(i).getPackageList().at(j).getPlaces().size() > 1 && k != 0){
					if (find(oneClientPlacesVisited.begin(), oneClientPlacesVisited.end(), aPlace) == oneClientPlacesVisited.end()) {
						oneClientPlacesVisited.push_back(aPlace);
					}
				}
				else if (clientsInfoVector.at(i).getPackageList().at(j).getPlaces().size() == 1) {
					if (find(oneClientPlacesVisited.begin(), oneClientPlacesVisited.end(), aPlace) == oneClientPlacesVisited.end()) {
						oneClientPlacesVisited.push_back(aPlace);
					}
				}
			}
		}
		
		clientsPlacesVisited.push_back(oneClientPlacesVisited);
	}

	vector<string> mostVisitedSorted;

	// mostVisitedSorted will have the N most visited places
	// (sorted from most visited to least visited
	for (auto const &pair : descending) {
		mostVisitedSorted.push_back(pair.second);
		nMostVisited = nMostVisited - 1;
		if (nMostVisited <= 0) {
			break;
		}
	}
	

	vector <vector <string> > newPlaces;
	vector <string> newPlacesOneClient;
	bool found;

	// newPlacesOneClient will have all the places that the client has not visited
	// (ordered from most to least visited)
	for (int i = 0; i < clientsPlacesVisited.size(); i++) {
		newPlacesOneClient = {};
		for (int j = 0; j < mostVisitedSorted.size(); j++) {

			found = true;

			for (int k = 0; k < clientsPlacesVisited.at(i).size(); k++) {

				if (clientsPlacesVisited.at(i).at(k) == mostVisitedSorted.at(j)) {
					found = false;
					break;
				}
			}

			if (found) {
				newPlacesOneClient.push_back(mostVisitedSorted.at(j));
			}
			
			
		}
		newPlaces.push_back(newPlacesOneClient);
	}
	

	bool noSugestionFound;

	cout << "Package Sugestions" << endl;

	// for each client
	for (int i = 0; i < newPlaces.size(); i++) {
		
		noSugestionFound = true;
		cout << clientsInfoVector.at(i).getName() << ":     \t";

		if (newPlaces.at(i).size() == 0) {
			cout << "No Available Package Sugestion" << endl;
		}

		else {
			// for each package
			for (int j = 0; j < packagesInfoVector.size(); j++) {

				// for each place of the package
				for (int p = 0; p < packagesInfoVector.at(j).getPlaces().size(); p++) {

					// for each place not visited by the client

					if ((newPlaces.at(i).at(0) == packagesInfoVector.at(j).getPlaces().at(p)) && (packagesInfoVector.at(j).getId() > 0)) {


						cout << "Package #" << abs(packagesInfoVector.at(j).getId()) << " ("
							<< packagesInfoVector.at(j).getPlaces().at(0) << ")";

						noSugestionFound = false;
						cout << endl;
						break;
					}

				}
			}
		}

		if (noSugestionFound) {
			cout << "No Available Package Sugestion" << endl;
		}
	}

	

	return -1;
}