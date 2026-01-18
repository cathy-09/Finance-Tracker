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
* File with setup command implementation
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

void setupProfile(FinanceProfile& financeProfile) {
	std::cout << "Enter number of months: ";
	std::cin >> financeProfile.totalMonths;

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Enter a number.";
		newLine();

		financeProfile.totalMonths = 0;
		return;
	}

	if (!isValidMonthCount(financeProfile.totalMonths)) {
		std::cout << "Invalid months!";
		newLine();

		financeProfile.totalMonths = 0;
		return;
	}

	delete[] financeProfile.months;
	financeProfile.months = new MonthData[financeProfile.totalMonths + 1];

	initializeMonths(financeProfile.months, financeProfile.totalMonths);

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Profile created successfully.";
	newLine();
}

bool requiresProfile(FinanceProfile& financeProfile, const char* commandWord) {
	bool needsProfile =
		myStringCompare(commandWord, "add") == 0 ||
		myStringCompare(commandWord, "report") == 0 ||
		myStringCompare(commandWord, "search") == 0 ||
		myStringCompare(commandWord, "sort") == 0 ||
		myStringCompare(commandWord, "forecast") == 0 ||
		myStringCompare(commandWord, "chart") == 0;

	if (needsProfile && financeProfile.months == nullptr) {
		std::cout << "Profile not set. Setup first.";
		newLine();
		return true;
	}

	return false;
}

void initializeMonths(MonthData* monthsArray, int monthsCount) {
	for (int i = 1; i <= monthsCount; i++) {
		monthsArray[i].income = 0;
		monthsArray[i].expense = 0;
	}
}

bool isValidMonthCount(int months) {
	return months > 0 && months <= MAX_MONTHS_IN_YEAR;
}