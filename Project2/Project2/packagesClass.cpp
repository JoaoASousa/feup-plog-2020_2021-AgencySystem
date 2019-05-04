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
void Package::setId(unsigned id) {
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