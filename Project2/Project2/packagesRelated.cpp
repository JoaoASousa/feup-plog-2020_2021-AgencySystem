#include "utilities.h"
#include "clientClass.h"
#include "packagesRelated.h"


using namespace std;




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

void packageDisplayAll(Agency &agency) {

	for (int i = 0; i < packagesInfo(agency.getPackagesFile()).size(); i++) {

		cout << packagesInfo(agency.getPackagesFile()).at(i) << endl;
		cout << endl;

	}
}

// return 0 if going back; else return -1
int packageDisplayOne(Agency &agency) {

	bool packageSelectorFailFlag = false;
	vector <int> packageNumbers = { 0 };
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

	cout << packagesInfo(agency.getPackagesFile()).at(packageSelection - 1) << endl;

	return -1;
}


int displayBetweenDates(Agency &agency) {

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
				return 0;
			}
			cin.clear();
			cin.ignore(1000, '\n');
		}

		//Date firstDate(firstDateString);
		// firstDate.setDay(10);
		Date firstDateS(firstDateString);
		firstDate = firstDateS;

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

		// Date secondDate(secondDateString);
		Date secondDateS(secondDateString);
		secondDate = secondDateS;

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
			// cout << i << endl;
			validPackages.push_back(packagesInfoVector.at(i));
		}

	}


	for (int i = 0; i < validPackages.size(); i++) {
		cout << validPackages.at(i) << endl;
		cout << endl;

	}

	return -1;
}


int displayForPlace(Agency &agency) {

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


int displayDateAndPlace(Agency &agency) {

	// Dates

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
			// cout << i << endl;
			validPackages.push_back(packagesInfoVector.at(i));
		}

	}


	// Places

	vector<Package> packagesToDisplay;

	string placeInputString;
	bool placeNotFound = false;

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
			// cout << validPackages.at(i).getPlaces().at(j);
			// cout << endl;
		}
		// cout << endl;
	}

	if (packagesToDisplay.size() == 0) {
		cout << "No package meets the requirements" << endl;
	}

	else {
		for (int k = 0; k < packagesToDisplay.size(); k++) {
			cout << packagesToDisplay.at(k) << endl;
			cout << endl;
		}
	}

	return -1;
}


int addPackage(Agency &agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	string packagesFileName = agency.getPackagesFile();

	string textLine;
	int lastCreated;
	ifstream packagesFile(packagesFileName);

	bool firstLine = true;

	while (getline(packagesFile, textLine)) {

		if (firstLine) {
			lastCreated = abs(stoi(textLine)); // last package created was already unavailable?
			firstLine = false;
			break;
		}
	}

	packagesFile.close();

	Package newPackage;


	newPackage.setId(lastCreated + 1);

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

		//Date firstDate(firstDateString);
		// firstDate.setDay(10);
		Date startDateS(startDateString);
		startDate = startDateS;

		if (!checkDate(startDate, currentDate)) {
			startDateFailInput = true;
		}

	} while (startDateFailInput);

	newPackage.setBeginDate(startDate);


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

		// Date secondDate(secondDateString);
		Date endDateS(endDateString);
		endDate = endDateS;

		if (!checkDate(endDate, startDate)) {
			endDateFailInput = true;
		}

	} while (endDateFailInput);

	newPackage.setEndDate(endDate);



	bool pricePerInputFail;
	double pricePer;

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


	ofstream packagesFileInput(packagesFileName);

	if (packagesFileInput.is_open()) {

		packagesFileInput << lastCreated + 1 << endl;

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


	return -1;
}


int changePackage(Agency &agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	vector <int> possibleChoices;
	bool invalidPackageInputFlag;
	int packageSelector;

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
	// Places, First Date, Second Date, PricePer, Max Number, Sold

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


		case 2:

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

				//Date firstDate(firstDateString);
				// firstDate.setDay(10);
				Date startDateS(startDateString);
				startDate = startDateS;

				if (!checkDate(startDate, currentDate)) {
					startDateFailInput = true;
				}

			} while (startDateFailInput);

			packagesInfoVector.at(packageToChangePosition).setBeginDate(startDate);


		case 3:

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

				// Date secondDate(secondDateString);
				Date endDateS(endDateString);
				endDate = endDateS;

				if (!checkDate(endDate, startDate)) {
					endDateFailInput = true;
				}

			} while (endDateFailInput);

			packagesInfoVector.at(packageToChangePosition).setEndDate(endDate);


		case 4:

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


		case 5:

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


		case 6:

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
			lastCreated = abs(stoi(textLine)); // last package created was already unavailable?
			firstLine = false;
			break;
		}
	}


	writePackagesFromVector(packagesFileName, lastCreated, packagesInfoVector);



	return -1;
}


int unavailablePackage(Agency &agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	vector <int> possibleChoices;
	bool invalidPackageInputFlag;
	int packageSelector;

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

	for (int i = 0; i < packagesInfoVector.size(); i++) {
		if (abs(packagesInfoVector.at(i).getId()) == packageSelector) {
			packageToChangePosition = i;
			break;
		}
	}

	packagesInfoVector.at(packageToChangePosition).setId(-packagesInfoVector.at(packageToChangePosition).getId());



	string packagesFileName = agency.getPackagesFile();

	string textLine;
	int lastCreated;
	ifstream packagesFile(packagesFileName);

	bool firstLine = true;

	while (getline(packagesFile, textLine)) {

		if (firstLine) {
			lastCreated = abs(stoi(textLine)); // last package created was already unavailable?
			firstLine = false;
			break;
		}
	}

	writePackagesFromVector(packagesFileName, lastCreated, packagesInfoVector);

	return -1;
}


void packageDisplayAllClients(Agency &agency) {

	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	vector<Client> clientsInfoVector = clientsInfo(agency);
	vector<Package> packagesToDisplay;
	vector<int> alreadyInVector;

	for (int i = 0; i < clientsInfoVector.size(); i++) {

		for (int j = 0; j < clientsInfoVector.at(i).getPackageList().size(); j++) {

			for (int k = 0; k < packagesInfoVector.size(); k++) {

				if (clientsInfoVector.at(i).getPackageList().at(j).getId() == packagesInfoVector.at(k).getId()) {

					if (find(alreadyInVector.begin(), alreadyInVector.end(), packagesInfoVector.at(k).getId()) == alreadyInVector.end()) {
						alreadyInVector.push_back(packagesInfoVector.at(k).getId());
						packagesToDisplay.push_back(packagesInfoVector.at(k));
					}
				}
			}
		}
	}

	for (int i = 0; i < packagesToDisplay.size(); i++) {
		cout << packagesToDisplay.at(i) << endl;
		cout << endl;
	}

}


int packageDisplayOneClient(Agency &agency) {
	
	vector<Package> packagesInfoVector = packagesInfo(agency.getPackagesFile());
	vector<Client> clientsInfoVector = clientsInfo(agency);
	vector<Package> packagesToDisplay;

	bool clientSelectorFailFlag = false;
	vector <int> clientNumbers = {-1};
	int clientSelection;


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

		else if (clientSelection == 0) {
			return 0;
		}
		

		cout << "\x1B[2J\x1B[H";


	} while (clientSelectorFailFlag);


	int realClientIndexInVector = clientSelection - 1;

	for (int i = 0; i < clientsInfoVector.at(realClientIndexInVector).getPackageList().size(); i++) {

		for (int j = 0; j < packagesInfoVector.size(); j++) {
			if (clientsInfoVector.at(realClientIndexInVector).getPackageList().at(i).getId() == packagesInfoVector.at(j).getId()) {
				packagesToDisplay.push_back(packagesInfoVector.at(j));
			}
		}
	}

	for (int i = 0; i < packagesToDisplay.size(); i++) {
		cout << packagesToDisplay.at(i) << endl;
		cout << endl;
	}


	return -1;
}