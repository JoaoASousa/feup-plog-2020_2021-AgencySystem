#include "clientRelated.h"
#include <iostream>

using namespace std;


void clientDisplayAll(Agency &agency) {

	for (int i = 0; i < clientsInfo(agency).size(); i++) {

		cout << endl;
		cout << clientsInfo(agency).at(i) << endl;
	}

}