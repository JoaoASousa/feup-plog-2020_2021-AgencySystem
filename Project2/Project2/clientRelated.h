#pragma once

#include "agencyClass.h"
#include "clientClass.h"
#include "utilities.h"


void writeClientsFromVector(string &clientsFileName, vector<Client> &clientsInfoVector);

int clientDisplayAll(Agency &agency, vector<Client> &clientsInfoVector);

int displayOneClient(Agency &agency, vector<Client> &clientsInfoVector);

int addClient(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

int removeClient(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

int buyPackage(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);

int changeClient(Agency &agency, vector<Client> &clientsInfoVector, vector<Package> &packagesInfoVector);