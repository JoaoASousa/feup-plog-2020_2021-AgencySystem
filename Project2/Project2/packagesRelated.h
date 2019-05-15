#pragma once

#include "agencyClass.h"
#include "packagesClass.h"
#include "utilities.h"


void writePackagesFromVector(string &packagesFileName, int &lastCreated, vector<Package> &packagesInfoVector);

void packageDisplayAll(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

int packageDisplayOne(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

int displayBetweenDates(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

int displayForPlace(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

int displayDateAndPlace(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

int addPackage(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

int changePackage(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

int unavailablePackage(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

void packageDisplayAllClients(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

int packageDisplayOneClient(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

void numberValueSoldPackages(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

int mostVisitedPlaces(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

int packageSugestion(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);