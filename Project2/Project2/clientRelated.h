#pragma once

#include "agencyClass.h"
#include "clientClass.h"
#include "utilities.h"


void writeClientsFromVector(string &clientsFileName, vector<Client> &clientsInfoVector);

void clientDisplayAll(Agency &agency);

int displayOneClient(Agency &agency);

int addClient(Agency &agency);

int removeClient(Agency &agency);