#pragma once
#include "structures.h"

void addData(FinanceProfile& financeProfile);
bool isValidMonthIndex(FinanceProfile& financeProfile, int month);
void inputMonthData(FinanceProfile& financeProfile, int month);
double calculateMonthBalance(FinanceProfile& financeProfile, int month);
void printMonthResult(FinanceProfile& financeProfile, int month, double balance);
int countEnteredMonths(FinanceProfile& financeProfile);
bool isMonthAlreadyEntered(FinanceProfile& financeProfile, int month);