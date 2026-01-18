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
* Header file with sort command declarations
*
*/

#pragma once
#include "structures.h"

void sortMonths(FinanceProfile& financeProfile, const char* type);
bool isValidSortType(const char* type);
void sortOrderByType(FinanceProfile& financeProfile, int* order, const char* type);
void printTopMonths(FinanceProfile& financeProfile, int* order, const char* type);
double getMonthValue(FinanceProfile& financeProfile, int monthIndex, const char* type);