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

vector <string> stringToStringVector(string fullString);