#pragma once
#include "structures.h"

void setupProfile(FinanceProfile& financeProfile);
bool isValidMonthCount(int months);
void initializeMonths(MonthData* monthsArray, int monthsCount);
bool requiresProfile(FinanceProfile& financeProfile, const char* commandWord);