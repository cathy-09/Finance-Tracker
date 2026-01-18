#pragma once
#include "structures.h"

void chart(FinanceProfile& financeProfile);
int calculateChartStep(double minBalance, double maxBalance);
void drawChartBody(FinanceProfile& financeProfile, double minBalance, double maxBalance);
void printChartMonths(FinanceProfile& financeProfile);
void printChartHeader();