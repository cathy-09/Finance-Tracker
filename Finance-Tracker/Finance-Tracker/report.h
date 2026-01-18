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
* Header file with report command declarations
*
*/

#pragma once
#include "structures.h"

void report(FinanceProfile& financeProfile);
void printReportHeader();
double printMonthReport(FinanceProfile& financeProfile, int monthIndex);
void printReportSummary(FinanceProfile& financeProfile, double totalIncome, double totalExpense);
