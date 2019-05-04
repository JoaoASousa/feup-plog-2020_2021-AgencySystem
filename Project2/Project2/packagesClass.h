#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Package {

	private:
		unsigned id; 
		vector<string> places;
		//Date begin;  
		//Date end; 
		double pricePer;
		unsigned maxPeople;

	public:
		//Package(vector<string> sites, Date begin, Date end, double pricePer, unsigned maxPersons);

		// set functions
		void setId(unsigned id);
		void setPlaces(vector<string> places);
		//void setBeginDate(Date begin);
		//void setEndDate(Date end);
		void setPricePer(double pricePer);
		void setMaxPeople(unsigned maxPeople);

		// get functions
		unsigned getId() const;
		vector<string> getPlaces() const;
		//Date getBeginDate() const;
		//Date getEndDate() const;
		double getPricePer() const;
		unsigned getMaxPeople() const;

};