#include <cmath>
#include <string>
#include <sstream>
#include <fstream>


#include "dateClass.h"
#include "packagesClass.h"

using namespace std;


// ------------------------------------------------------------------------
// Constructors

Package::Package() {
	
}

Package::Package(int id, vector<string> sites, Date begin, Date end, double pricePer, unsigned maxPeople, unsigned sold) {
	
	setId(id);
	setPlaces(sites);
	setBeginDate(begin);
	setEndDate(end);
	setPricePer(pricePer);
	setMaxPeople(maxPeople);
	setSold(sold);
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
int Package::getId() const {
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
		out << "\t\t[Unavailable Package]";
	}

	out << "\nPlaces:\t\t\t\t";
	
	for (int i = 0; i < package.places.size(); i++) {
		
		if (i == 0) {
			if (package.places.size() > 1) {
				out << package.places.at(i) << " - ";
				
			}
			else {
				out << package.places.at(i);
			}
			
		}

		else {
			if (i == 1) {
				out << package.places.at(i);
			}
			else {
				out << ", " << package.places.at(i);
			}
		}
	}

	out << '\n';
	out << "Begin Date:\t\t\t" << package.begin << '\n';
	out << "End Date:\t\t\t" << package.end << '\n';

	out << "Price per Person:\t\t" << package.pricePer << '\n';
	out << "Maximum number of People:\t" << package.maxPeople << '\n';
	out << "Currently sold:\t\t\t" << package.sold;

	return out;
}