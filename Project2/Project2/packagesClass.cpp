#include <cmath>
#include "packagesClass.h"

using namespace std;


// ------------------------------------------------------------------------
// Constructor

//Package::Package(vector<string> sites, Date begin, Date end, double pricePer, unsigned maxPersons) {
//
//}


// ------------------------------------------------------------------------
// Public Functions

// set functions
void Package::setId(int id) {
	this->id = id;
}

void Package::setPlaces(vector<string> newplaces) {
	places = newplaces;
}

void Package::setPricePer(double pricePer) {
	this->pricePer = pricePer;
}

void Package::setMaxPeople(unsigned maxPeople) {
	this->maxPeople = maxPeople;
}

void Package::setSold(unsigned sold) {
	this->sold = sold;
}


// get functions
unsigned Package::getId() const {
	return id;
}

vector<string> Package::getPlaces() const {
	return places;
}

double Package::getPricePer() const {
	return pricePer;
}

unsigned Package::getMaxPeople() const {
	return maxPeople;
}

unsigned Package::getSold() const {
	return sold;
}


ostream &operator<<(ostream& out, const Package &package) {
	
	out << "Package Number #" << abs(package.id);
	
	if (abs(package.id) != package.id) {
		out << "\t[Unavailable Package]";
	}

	out << "\nPlaces: ";

	bool mainPlace = true;

	for (int i = 0; i < package.places.size(); i++) {
		if (mainPlace) {
			out << package.places.at(i) << " - ";
			mainPlace = false;
		}
		else {
			if (i == (package.places.size() - 1)) {
				out << package.places.at(i);
			}
			else {
				out << package.places.at(i) << ", ";
			}
		}
	}
	
	// TO BE FINISHED
	out << "Begin Date: " << '\n';
	out << "End Date: " << '\n';

	out << "Price per Person: " << package.pricePer << '\n';
	out << "Maximum number of People: " << package.maxPeople << '\n';
	out << "Currently sold: " << package.sold;

	return out;
}