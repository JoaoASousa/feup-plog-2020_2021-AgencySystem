#pragma once

#include "agencyClass.h"
#include "packagesClass.h"
#include "utilities.h"


void writePackagesFromVector(string &packagesFileName, int &lastCreated, vector<Package> &packagesInfoVector);

void packageDisplayAll(Agency &agency);

int packageDisplayOne(Agency &agency);

int displayBetweenDates(Agency &agency);

int displayForPlace(Agency &agency);

int displayDateAndPlace(Agency &agency);

int addPackage(Agency &agency);

int changePackage(Agency &agency);

int unavailablePackage(Agency &agency);

void packageDisplayAllClients(Agency &agency);

int packageDisplayOneClient(Agency &agency);

void numberValueSoldPackages(Agency &agency);

int mostVisitedPlaces(Agency &agency);
