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
* File with search command implementation
*
*/

#include <iostream>

#include "commands.h"
#include "setup.h"
#include "add.h"
#include "report.h"
#include "search.h"
#include "sort.h"
#include "forecast.h"
#include "chart.h"
#include "utils.h"
#include "constants.h"

void searchMonth(FinanceProfile& financeProfile, const char* name) {
	if (!ensureProfile(financeProfile, "Profile not set.")) {
		return;
	}

	if (isArgumentMissing(name, "Month name missing.")) {
		return;
	}

	int index = findMonthIndex(financeProfile, name);

	if (index == -1)
	{
		std::cout << "Month not found.";
		newLine();
		return;
	}

	printMonthDetails(financeProfile, index);
}

int findMonthIndex(FinanceProfile& financeProfile, const char* monthName) {
	for (int i = 1; i <= financeProfile.totalMonths; i++) {
		if (myStringCompare(monthName, financeProfile.monthNames[i]) == 0) {
			return i;
		}
	}
	return -1;
}

void printMonthDetails(FinanceProfile& financeProfile, int monthIndex) {
	double income = financeProfile.months[monthIndex].income;
	double expense = financeProfile.months[monthIndex].expense;
	double balance = income - expense;

	std::cout << "Income: " << income;
	newLine();

	std::cout << "Expense: " << expense;
	newLine();

	std::cout << "Balance: ";
	printBalanceColored(balance);
	newLine();

	if (income > 0) {
		double ratio = (expense * PERCENT) / income;
		ratio = myRound(ratio, 1);
		std::cout << "Expense ratio: " << ratio << "%";
		newLine();
	}
	else {
		std::cout << "Expense ratio: no income.";
		newLine();
	}
}