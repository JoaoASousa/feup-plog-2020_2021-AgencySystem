#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <sstream>
#include "dateClass.h"

using namespace std;


// ------------------------------------------------------------------------
// Constructors
Date::Date() {

	// current Date
	time_t t = time(NULL);
	tm* timePointer = localtime(&t);
	
	this->day = (timePointer->tm_mday);
	this->month = (timePointer->tm_mon) + 1;
	this->year = (timePointer->tm_year) + 1900;

}

Date::Date(string date) {

	istringstream ss(date);

	unsigned short year, month, day;
	char delimiter;

	ss >> year >> delimiter >> month >> delimiter >> day;
	
	this->day = day;
	this->month = month;
	this->year = year;
}


Date::Date(unsigned short day, unsigned short month, unsigned year) {
	this->day = day;
	this->month = month;
	this->year = year;
}



// ------------------------------------------------------------------------
// Public Functions


// set functions
void Date::setDay(unsigned short day) {
	this->day = day;
}
void Date::setMonth(unsigned short month) {
	this->month = month;
}

void Date::setYear(unsigned year) {
	this->year = year;
}


// get functions
unsigned short Date::getDay() const {
	return day;
}

unsigned short Date::getMonth() const {
	return month;
}

unsigned Date::getYear() const {
	return year;
}


ostream& operator<<(ostream& out, const Date & date) {

	out << date.year << '/' << date.month << '/' << date.day;
	return out;
}
