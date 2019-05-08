#pragma once

#include "agencyClass.h"

int mainMenu(Agency agency);

int packageMenu(Agency agency);

void packageDisplayAll(Agency agency);

int packageDisplayOne(Agency agency);


int daysOfMonth(int month, int year);

bool checkDate(Date ToEvaluateDate, Date referenceDate);

int displayBetweenDates(Agency agency);

int displayForPlace(Agency agency);

string trimString(const string &toTrim, const string &whitespace = " \t");