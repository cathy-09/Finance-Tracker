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
* File with forecast command implementation
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

void forecast(FinanceProfile& financeProfile, int monthAhead) {
	if (!ensureProfile(financeProfile, "Profile not set.")) {
		return;
	}

	double savings = 0;
	double averageChange = 0;

	calculateSavings(financeProfile, savings, averageChange);

	std::cout << "Current savings: ";
	printBalanceColored(savings);
	newLine();

	std::cout << "Average monthly change: ";
	printBalanceColored(averageChange);
	newLine();

	if (averageChange >= 0) {
		forecastPositive(savings, averageChange, monthAhead);
	}
	else {
		forecastNegative(financeProfile, savings, averageChange);
	}
}
void calculateSavings(FinanceProfile& financeProfile, double& savings, double& averageChange)
{
	double totalIncome = 0;
	double totalExpense = 0;

	for (int i = 1; i <= financeProfile.totalMonths; i++) {
		totalIncome += financeProfile.months[i].income;
		totalExpense += financeProfile.months[i].expense;
	}

	savings = totalIncome - totalExpense;
	int enteredMonths = countEnteredMonths(financeProfile);

	if (enteredMonths > 0) {
		averageChange = savings / enteredMonths;
	}
	else {
		averageChange = 0;
	}
}

void forecastPositive(double savings, double averageChange, int monthsAhead) {
	double futureSavings = savings + averageChange * monthsAhead;

	std::cout << "Predicted savings after " << monthsAhead << " months: ";
	printBalanceColored(futureSavings);
	newLine();
}

void forecastNegative(FinanceProfile& financeProfile, double savings, double averageChange) {
	double remainingSavings = savings;
	int month = 0;

	while (remainingSavings > EPSILON) {
		remainingSavings += averageChange;
		month++;
	}

	std::cout << "Expected to run out of money after " << month << " months.";
	newLine();
}
