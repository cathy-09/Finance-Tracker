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
* Header file with search command declarations
*
*/

#pragma once
#include "structures.h"

void searchMonth(FinanceProfile& financeProfile, const char* name);
int findMonthIndex(FinanceProfile& financeProfile, const char* monthName);
void printMonthDetails(FinanceProfile& financeProfile, int monthIndex);