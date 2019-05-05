#pragma once

#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Date {

	private:
		unsigned short day;
		unsigned short month;
		unsigned year;

	public:
		Date();
		Date(string date);
		Date(unsigned short day, unsigned short month, unsigned year);

		// set functions
		void setDay(unsigned short day);
		void setMonth(unsigned short month);
		void setYear(unsigned year);

		// get functions
		unsigned short getDay() const;
		unsigned short getMonth() const;
		unsigned getYear() const;


		friend ostream& operator<<(ostream& out, const Date & date);

};