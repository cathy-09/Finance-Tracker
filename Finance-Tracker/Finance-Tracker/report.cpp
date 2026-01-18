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

void report(FinanceProfile& financeProfile) {
	if (!ensureProfile(financeProfile, "No profile to report.")) {
		return;
	}

	double totalIncome = 0;
	double totalExpense = 0;

	printReportHeader();

	for (int i = 1; i <= financeProfile.totalMonths; i++) {
		if (financeProfile.months[i].income != 0 || financeProfile.months[i].expense != 0) {
			printMonthReport(financeProfile, i);
			totalIncome += financeProfile.months[i].income;
			totalExpense += financeProfile.months[i].expense;
		}
	}

	printReportSummary(financeProfile, totalIncome, totalExpense);
}

void printReportHeader() {
	printTextAligned("Month", COL_MONTH);
	std::cout << " | ";

	printTextAligned("Income", COL_INCOME);
	std::cout << " | ";

	printTextAligned("Expense", COL_EXPENSE);
	std::cout << " | ";

	printTextAligned("Balance", COL_BALANCE);
	newLine();

	printHorizontalLine();
}

double printMonthReport(FinanceProfile& financeProfile, int monthIndex) {
	double balance = financeProfile.months[monthIndex].income - financeProfile.months[monthIndex].expense;

	printTextAligned(financeProfile.monthNames[monthIndex], COL_MONTH);
	std::cout << " | ";

	printDoubleAligned(financeProfile.months[monthIndex].income, COL_INCOME);
	std::cout << " | ";

	printDoubleAligned(financeProfile.months[monthIndex].expense, COL_EXPENSE);
	std::cout << " | ";

	printBalanceAligned(balance, COL_BALANCE);

	newLine();
	return balance;
}

void printReportSummary(FinanceProfile& financeProfile, double totalIncome, double totalExpense) {
	printHorizontalLine();

	int enteredMonths = countEnteredMonths(financeProfile);

	double average = 0;
	if (enteredMonths > 0) {
		average = (totalIncome - totalExpense) / enteredMonths;
		average = myRound(average, 2);
	}

	std::cout << "Total income: ";
	printDoubleFixed(totalIncome);
	newLine();

	std::cout << "Total expense: ";
	printDoubleFixed(totalExpense);
	newLine();

	std::cout << "Average balance: ";
	printBalanceColored(average);
	newLine();
}