#pragma once
#include "structures.h"

void report(FinanceProfile& financeProfile);
void printReportHeader();
double printMonthReport(FinanceProfile& financeProfile, int monthIndex);
void printReportSummary(FinanceProfile& financeProfile, double totalIncome, double totalExpense);
