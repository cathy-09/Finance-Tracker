#pragma once
#include "structures.h"

void sortMonths(FinanceProfile& financeProfile, const char* type);
bool isValidSortType(const char* type);
void sortOrderByType(FinanceProfile& financeProfile, int* order, const char* type);
void printTopMonths(FinanceProfile& financeProfile, int* order, const char* type);
double getMonthValue(FinanceProfile& financeProfile, int monthIndex, const char* type);