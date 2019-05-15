
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