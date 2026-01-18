/**
*
* Solution to course project #3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Katerina Dimitrova
* @idnumber 8MI0600563
* @compiler GCC
*
* Header file with setup command declarations
*
*/

#pragma once
#include "structures.h"

void setupProfile(FinanceProfile& financeProfile);
bool isValidMonthCount(int months);
void initializeMonths(MonthData* monthsArray, int monthsCount);
bool requiresProfile(FinanceProfile& financeProfile, const char* commandWord);