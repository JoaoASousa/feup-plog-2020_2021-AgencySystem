#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "dateClass.h"

using namespace std;

class Package {

	private:
		int id; 
		vector<string> places;
		//Date begin;  
		//Date end; 
		double pricePer;
		unsigned maxPeople;
		unsigned sold;

	public:
		Package(vector<string> sites, Date begin, Date end, double pricePer, unsigned maxPersons);

		// set functions
		void setId(int id);
		void setPlaces(vector<string> places);
		//void setBeginDate(Date begin);
		//void setEndDate(Date end);
		void setPricePer(double pricePer);
		void setMaxPeople(unsigned maxPeople);
		void setSold(unsigned sold);

		// get functions
		unsigned getId() const;
		vector<string> getPlaces() const;
		//Date getBeginDate() const;
		//Date getEndDate() const;
		double getPricePer() const;
		unsigned getMaxPeople() const;
		unsigned getSold() const;


		friend ostream &operator<<(ostream& out, const Package &package);
};