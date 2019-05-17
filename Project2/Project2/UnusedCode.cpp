
// from mostVisitedPlaces function

/*multimap <int, string> invertedMap;

	for (auto const &pair : placesFrequency) {
		invertedMap.insert(make_pair(pair.second, pair.first));
	}

	for (auto const &pair : invertedMap) {
		std::cout << '{' << pair.second << "," << pair.first << '}' << '\n';
	}*/

	//////////////////////////////////////////////////////////////

	/*for (map<string, int>::const_iterator it = placesFrequency.begin(); it != placesFrequency.end(); it++) {
		cout << endl;
		cout << "Place: " << it->first << "\tPurchases: " << it->second << endl;
	}*/


/////////////////////////////////////////////////////////////////////////////////


// from numberValueSoldPackages function

// map <int, int> idSoldMap;

/*for (map<int, int>::const_iterator mi = idSoldMap.begin(); mi != idSoldMap.end(); mi++) {
		cout << "Package Number " << mi->first << "\tSold: " << mi->second << endl;
	}*/


/////////////////////////////////////////////////////////////////////////////////

// from changePackage function

//Date firstDate(firstDateString);
// firstDate.setDay(10);
// Date secondDate(secondDateString);

// Date secondDate(secondDateString);


/////////////////////////////////////////////////////////////////////////////////


// from addPackage function

//Date firstDate(firstDateString);
// firstDate.setDay(10);

//ofstream packagesFileInput(packagesFileName);
//
//	if (packagesFileInput.is_open()) {
//
//		packagesFileInput << lastCreated + 1 << endl;
//
//		for (int i = 0; i < packagesInfoVector.size(); i++) {
//
//			if (i == 0 && packagesInfoVector.size() > 1) {
//
//				packagesFileInput << packagesInfoVector.at(i).getId() << endl;
//
//				for (int j = 0; j < packagesInfoVector.at(i).getPlaces().size(); j++) {
//
//					if (j == 0) {
//						if (packagesInfoVector.at(i).getPlaces().size() > 1) {
//							packagesFileInput << packagesInfoVector.at(i).getPlaces().at(j) << " - ";
//
//						}
//						else {
//							packagesFileInput << packagesInfoVector.at(i).getPlaces().at(j);
//						}
//
//					}
//
//					else {
//						if (j == 1) {
//							packagesFileInput << packagesInfoVector.at(i).getPlaces().at(j);
//						}
//						else {
//							packagesFileInput << ", " << packagesInfoVector.at(i).getPlaces().at(j);
//						}
//					}
//				}
//				packagesFileInput << endl;
//				packagesFileInput << packagesInfoVector.at(i).getBeginDate() << endl;
//				packagesFileInput << packagesInfoVector.at(i).getEndDate() << endl;
//				packagesFileInput << packagesInfoVector.at(i).getPricePer() << endl;
//				packagesFileInput << packagesInfoVector.at(i).getMaxPeople() << endl;
//				packagesFileInput << packagesInfoVector.at(i).getSold() << endl;
//			}
//
//			else {
//				packagesFileInput << "::::::::::" << endl;
//
//				packagesFileInput << packagesInfoVector.at(i).getId() << endl;
//
//				for (int j = 0; j < packagesInfoVector.at(i).getPlaces().size(); j++) {
//
//					if (j == 0) {
//						if (packagesInfoVector.at(i).getPlaces().size() > 1) {
//							packagesFileInput << packagesInfoVector.at(i).getPlaces().at(j) << " - ";
//
//						}
//						else {
//							packagesFileInput << packagesInfoVector.at(i).getPlaces().at(j);
//						}
//
//					}
//
//					else {
//						if (j == 1) {
//							packagesFileInput << packagesInfoVector.at(i).getPlaces().at(j);
//						}
//						else {
//							packagesFileInput << ", " << packagesInfoVector.at(i).getPlaces().at(j);
//						}
//					}
//				}
//
//				packagesFileInput << endl;
//				packagesFileInput << packagesInfoVector.at(i).getBeginDate() << endl;
//				packagesFileInput << packagesInfoVector.at(i).getEndDate() << endl;
//				packagesFileInput << packagesInfoVector.at(i).getPricePer() << endl;
//				packagesFileInput << packagesInfoVector.at(i).getMaxPeople() << endl;
//				packagesFileInput << packagesInfoVector.at(i).getSold() << endl;
//			}
//
//		}
//
//		packagesFileInput.close();
//	}

/////////////////////////////////////////////////////////////////////////////////

// from displayDateAndPlace function

// firstDate.setDay(10);


/////////////////////////////////////////////////////////////////////////////////

// from displayBetweenDates function

// Date firstDate(firstDateString);
// firstDate.setDay(10);

// Date secondDate(secondDateString);



/////////////////////////////////////////////////////////////////////////////////

// from menus.cpp

			/*for (int i = 0; i < clientsInfo( agency).size(); i++) {
				cout << endl;
				cout << clientsInfo(agency).at(i) << endl;
			}*/


			/*int goBack = -1;*/
// goBack = packageMenu(agency);
			/*if (goBack == 0) {
					if (mainMenu(agency) == 0) {
						return -1;
					};

				}*/

/////////////////////////////////////////////////////////////////////////////////

// from address.cpp

/*setStreet(stringsVector.at(0).erase(stringsVector.at(0).find_last_not_of(" ") + 1));
	setDoorNumber(stoi(stringsVector.at(1)));
	setFloor(stringsVector.at(2));
	setZipCode(stringsVector.at(3));
	setLocation(stringsVector.at(4));*/

/////////////////////////////////////////////////////////////////////////////////

// from agencyClass.cpp

//void Agency::setClients(vector<Client> & clients) {
//	this->clients = clients;
//}
//
//void Agency::setPackages(vector<Packages> & packages) {
//	this->packages = packages;
//}


//vector<Client> Agency::getClients() const{
//	return clients;
//}
//
//vector<Package> Agency::getPackages() const {
//	return packages;
//}

/////////////////////////////////////////////////////////////////////////////////

// from changePackage functions

/*int totalPurchases = 0;*/

	/*for (int i = 0; i < clientPackages.size(); i++) {
		totalPurchases += clientPackages.at(i).getPricePer() * familySize;
	}

	if (totalPurchases < 0) {
		cout << "Invalid Package Price" << endl;
		return 0;
	}

	newClient.setTotalPurchased(totalPurchases);*/

	// writes to the file the updated information
	// writePackagesFromVector(packagesFileName, lastCreated, packagesInfoVector);


/////////////////////////////////////////////////////////////////////////////////

// from packageSugestions

/*for (int m = 0; m < oneClientPlacesVisited.size(); m++) {
			cout << oneClientPlacesVisited.at(m) << endl;
		}
		cout << endl;*/


/*if (find(clientsPlacesVisited.at(i).begin(), clientsPlacesVisited.at(i).end(), mostVisitedSorted.at(j)) == clientsPlacesVisited.at(i).end()) {
				newPlacesOneClient.push_back(mostVisitedSorted.at(j));
			}*/

/*for (int i = 0; i < newPlaces.size(); i++) {
		cout << "Client #" << i + 1 << endl;
		for (int m = 0; m < newPlaces.at(i).size(); m++) {
			cout << newPlaces.at(i).at(m) << endl;
		}
		cout << endl;
	}*/

/////////////////////////////////////////////////////////////////////////////////

// from changePackage

// updating the clients total expenses
/*
int updatedTotalSpent;

// for each client
for (int i = 0; i < clientsInfoVector.size(); i++) {
	updatedTotalSpent = 0;
	// for each client's package bought
	for (int j = 0; j < clientsInfoVector.at(i).getPackageList().size(); j++) {

		for (int k = 0; k < packagesInfoVector.size(); k++) {
			if (abs(clientsInfoVector.at(i).getPackageList().at(j).getId()) == abs(packagesInfoVector.at(k).getId())) {
				updatedTotalSpent += packagesInfoVector.at(k).getPricePer() * clientsInfoVector.at(i).getFamilySize();
			}
		}

	}
	cout << updatedTotalSpent << endl;
	clientsInfoVector.at(i).setTotalPurchased(updatedTotalSpent);
}
*/

/////////////////////////////////////////////////////////////////////////////////


// from stringToStringVector

	//istringstream ss(fullString);

	/*while (ss >> temp) {
		if (temp == "-" || temp == ",") {
			continue;
		}
		cout << temp << endl;
		stringsVector.push_back(temp);
	}*/