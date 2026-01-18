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

void sortMonths(FinanceProfile& financeProfile, const char* type) {
	if (!isValidSortType(type)) {
		std::cout << "Invalid sort type.";
		newLine();
		return;
	}

	int* order = new int[financeProfile.totalMonths + 1];
	for (int i = 1; i <= financeProfile.totalMonths; i++) {
		order[i] = i;
	}

	sortOrderByType(financeProfile, order, type);
	printTopMonths(financeProfile, order, type);

	delete[] order;
}

bool isValidSortType(const char* type) {
	return myStringCompare(type, "income") == 0 ||
		myStringCompare(type, "expense") == 0 ||
		myStringCompare(type, "balance") == 0;
}

void sortOrderByType(FinanceProfile& financeProfile, int* order, const char* type) {
	for (int i = 1; i <= financeProfile.totalMonths; i++) {
		for (int j = 1; j < financeProfile.totalMonths; j++) {
			double firstValue = getMonthValue(financeProfile, order[j], type);
			double secondValue = getMonthValue(financeProfile, order[j + 1], type);

			if (firstValue < secondValue) {
				mySwap(order[j], order[j + 1]);
			}
		}
	}
}

void printTopMonths(FinanceProfile& financeProfile, int* order, const char* type) {
	std::cout << "Sorted by monthly " << type << " (descending):";
	newLine();

	for (int k = 1; k <= MAX_K_LENGTH && k <= financeProfile.totalMonths; k++) {
		int monthIndex = order[k];
		std::cout << k << ". " << financeProfile.monthNames[monthIndex] << ": ";

		double value = getMonthValue(financeProfile, monthIndex, type);

		if (myStringCompare(type, "expense") == 0) {
			std::cout << "\033[1;31m";
			printDoubleFixed(value);
			std::cout << "\033[0m";
		}
		else {
			printBalanceColored(value);
		}
		newLine();
	}
}

double getMonthValue(FinanceProfile& financeProfile, int monthIndex, const char* type)
{
	if (myStringCompare(type, "income") == 0) {
		return financeProfile.months[monthIndex].income;
	}
	else if (myStringCompare(type, "expense") == 0) {
		return financeProfile.months[monthIndex].expense;
	}
	else if (myStringCompare(type, "balance") == 0) {
		return financeProfile.months[monthIndex].income - financeProfile.months[monthIndex].expense;
	}
	return 0;
}