#include <cmath>
#include <string>
#include <sstream>
#include <fstream>


#include "dateClass.h"
#include "packagesClass.h"

using namespace std;


// ------------------------------------------------------------------------
// Constructor

Package::Package() {

}

Package::Package(int id, vector<string> sites, Date begin, Date end, double pricePer, unsigned maxPersons, unsigned sold) {
	
}


// ------------------------------------------------------------------------
// Public Functions

// set functions
void Package::setId(int id) {
	this->id = id;
}

void Package::setPlaces(vector<string> newplaces) {
	places = newplaces;
}

void Package::setBeginDate(Date begin) {
	this->begin = begin;
}

void Package::setEndDate(Date end) {
	this->end = end;
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

Date Package::getBeginDate() const {
	return begin;
}

Date Package::getEndDate() const {
	return end;
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


	for (int i = 0; i < package.places.size(); i++) {
		if (i == 0) {
			if (package.places.size() > 1) {
				out << package.places.at(i) << " -";
			}
			else {
				out << package.places.at(i);
			}
		}

		else {
			out << " " << package.places.at(i);
		}
	}

	out << '\n';
	out << "Begin Date: " << package.begin << '\n';
	out << "End Date: " << package.end << '\n';

	out << "Price per Person: " << package.pricePer << '\n';
	out << "Maximum number of People: " << package.maxPeople << '\n';
	out << "Currently sold: " << package.sold;

	/*
	else {
			if (i == (package.places.size() - 1)) {
				out << " " << package.places.at(i);
			}
			else {
				out << package.places.at(i) << ", ";
			}
		}
	*/
	return out;
}