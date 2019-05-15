#pragma once

#include "agencyClass.h"

int mainMenu(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

int packageMenu(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

int clientMenu(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);