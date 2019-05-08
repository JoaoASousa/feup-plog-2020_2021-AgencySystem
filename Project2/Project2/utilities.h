#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


#include "packagesClass.h"
#include "address.h"

using namespace std;

bool validAgencyFile(string agencyName);

vector<Package> packagesInfo(string packagesFileName);

int daysOfMonth(int month, int year);

bool checkDate(Date ToEvaluateDate, Date referenceDate);

vector <string> stringToStringVector(string fullString);

string trimString(const string &toTrim, const string &whitespace = " \t");