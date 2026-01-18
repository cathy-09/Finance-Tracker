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
* File with chart command implementation
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

void chart(FinanceProfile& financeProfile) {
	if (!ensureProfile(financeProfile, "Profile not set.")) {
		return;
	}

	if (financeProfile.totalMonths == 0) {
		std::cout << "No data.";
		newLine();
		return;
	}

	printChartHeader();

	double minBalance = financeProfile.months[1].income - financeProfile.months[1].expense;
	double maxBalance = minBalance;

	for (int i = 2; i <= financeProfile.totalMonths; i++) {
		double balance = financeProfile.months[i].income - financeProfile.months[i].expense;

		if (balance < minBalance) {
			minBalance = balance;
		}
		if (balance > maxBalance) {
			maxBalance = balance;
		}
	}

	int step = calculateChartStep(minBalance, maxBalance);

	drawChartBody(financeProfile, minBalance, maxBalance);
	printChartMonths(financeProfile);
}

void printChartHeader() {
	std::cout << "=== YEARLY FINANCIAL CHART ===";
	newLine();
}

int calculateChartStep(double minBalance, double maxBalance) {
	double range = maxBalance - minBalance;

	if (range <= 0) {
		return MIN_STEP;
	}

	double rawStep = range / CHART_LEVELS;

	int scale = 1;
	while (rawStep / scale > SCALE_FACTOR) {
		scale *= SCALE_FACTOR;
	}

	int step = (int)((rawStep + scale - 1) / scale) * scale;

	return step;
}

void drawChartBody(FinanceProfile& financeProfile, double minBalance, double maxBalance) {
	int step = calculateChartStep(minBalance, maxBalance);

	for (double level = maxBalance; level >= minBalance; level -= step) {
		int printValue = (int)level;
		std::cout.width(5);
		std::cout << printValue << " | ";

		for (int m = 1; m <= financeProfile.totalMonths; m++) {
			double balance = financeProfile.months[m].income - financeProfile.months[m].expense;
			if (balance >= level) {
				std::cout << "# ";
			}
			else {
				std::cout << "  ";
			}
		}
		newLine();
	}

	std::cout << "      ";
	for (int m = 1; m <= financeProfile.totalMonths; m++) {
		std::cout << "--";
	}
	newLine();
}

void printChartMonths(FinanceProfile& financeProfile) {
	std::cout << "      ";

	for (int m = 1; m <= financeProfile.totalMonths; m++) {
		std::cout << financeProfile.monthNames[m][0]
			<< financeProfile.monthNames[m][1]
			<< financeProfile.monthNames[m][2]
			<< " ";
	}
	newLine();
}