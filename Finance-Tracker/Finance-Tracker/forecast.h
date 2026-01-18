#pragma once
#include "structures.h"

void forecast(FinanceProfile& financeProfile, int monthAhead);
void calculateSavings(FinanceProfile& financeProfile, double& savings, double& averageChange);
void forecastPositive(double savings, double averageChange, int monthsAhead);
void forecastNegative(FinanceProfile& financeProfile, double savings, double averageChange);