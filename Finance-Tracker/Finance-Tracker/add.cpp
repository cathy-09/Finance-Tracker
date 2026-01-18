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
* File with add command implementation
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

void addData(FinanceProfile& financeProfile) {
	if (!ensureProfile(financeProfile, "Profile not set.")) {
		return;
	}

	int month = 0;

	std::cout << "Enter month (1-" << financeProfile.totalMonths << "): ";
	std::cin >> month;

	if (!isValidMonthIndex(financeProfile, month)) {
		std::cout << "Invalid month!";
		newLine();

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}

	if (isMonthAlreadyEntered(financeProfile, month)) {
		std::cout << "Data for this month is already entered.";
		newLine();

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}

	inputMonthData(financeProfile, month);

	double balance = calculateMonthBalance(financeProfile, month);
	printMonthResult(financeProfile, month, balance);

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool isValidMonthIndex(FinanceProfile& financeProfile, int month) {
	return month >= 1 && month <= financeProfile.totalMonths;
}

void inputMonthData(FinanceProfile& financeProfile, int month) {
	do {
		std::cout << "Enter income: ";
		std::cin >> financeProfile.months[month].income;

		std::cout << "Enter expense: ";
		std::cin >> financeProfile.months[month].expense;

		if (financeProfile.months[month].income < 0
			|| financeProfile.months[month].expense < 0) {
			std::cout << "Income and expense must be positive or zero.";
			newLine();
		}
	} while (financeProfile.months[month].income < 0 || financeProfile.months[month].expense < 0);
}

double calculateMonthBalance(FinanceProfile& financeProfile, int month) {
	return financeProfile.months[month].income - financeProfile.months[month].expense;
}

void printMonthResult(FinanceProfile& financeProfile, int month, double balance) {
	std::cout << "Result: Balance for " << financeProfile.monthNames[month] << ": ";
	printBalanceColored(balance);
	newLine();
}

int countEnteredMonths(FinanceProfile& financeProfile) {
	int count = 0;

	for (int i = 1; i <= financeProfile.totalMonths; i++) {
		if (financeProfile.months[i].income != 0 ||
			financeProfile.months[i].expense != 0) {
			count++;
		}
	}
	return count;
}

bool isMonthAlreadyEntered(FinanceProfile& financeProfile, int month) {
	return financeProfile.months[month].income != 0 ||
		financeProfile.months[month].expense != 0;
}