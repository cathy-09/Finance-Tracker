#pragma once
#include "structures.h"

void searchMonth(FinanceProfile& financeProfile, const char* name);
int findMonthIndex(FinanceProfile& financeProfile, const char* monthName);
void printMonthDetails(FinanceProfile& financeProfile, int monthIndex);