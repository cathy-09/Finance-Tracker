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

void welcome() {
	std::cout << "=================================";
	newLine();
	std::cout << "   Welcome to Finance Profile!";
	newLine();
	std::cout << "=================================";
	newLine();
	std::cout << "Type 'help' to see commands list.";
	newLine();
}

void printHelp() {
	std::cout << "Available Commands";
	newLine();
	std::cout << "-------------------------------------------------------------";
	newLine();
	std::cout << "> setup <month> - Create a new finance profile.";
	newLine();
	std::cout << "> add - Add income and expenses for a month.";
	newLine();
	std::cout << "> report - Show report for all months.";
	newLine();
	std::cout << "> search <month> - Show information for selected month.";
	newLine();
	std::cout << "> sort <type> - Sort by income, expense or balance.";
	newLine();
	std::cout << "> forecast <monthsAhead> - Financial forecast for m months.";
	newLine();
	std::cout << "> chart - Show graphical chart";
	newLine();
	std::cout << "> exit - Exit the program.";
	newLine();
	std::cout << "> help - Show list of commands.";
	newLine();
	std::cout << "-------------------------------------------------------------";
	newLine();
}

void handleCommand(FinanceProfile& financeProfile, char* commandWord, char* argumentString, bool& exitProgram) {
	if (myStringCompare(commandWord, "setup") == 0) {
		setupProfile(financeProfile);
		return;
	}
	if (myStringCompare(commandWord, "exit") == 0) {
		if (financeProfile.months != nullptr) {
			report(financeProfile);
		}
		exitProgram = true;
		return;
	}

	if (requiresProfile(financeProfile, commandWord)) {
		return;
	}

	if (myStringCompare(commandWord, "add") == 0) {
		addData(financeProfile);
	}
	else if (myStringCompare(commandWord, "report") == 0) {
		report(financeProfile);
	}
	else if (myStringCompare(commandWord, "search") == 0) {
		handleSearchCommand(financeProfile, argumentString);
	}
	else if (myStringCompare(commandWord, "sort") == 0) {
		handleSortCommand(financeProfile, argumentString);
	}
	else if (myStringCompare(commandWord, "forecast") == 0) {
		handleForecastCommand(financeProfile, argumentString);
	}
	else if (myStringCompare(commandWord, "chart") == 0) {
		chart(financeProfile);
	}
	else if (myStringCompare(commandWord, "help") == 0) {
		printHelp();
	}
	else {
		std::cout << "Invalid command.";
		newLine();
	}
}

int parseMonthsAhead(const char* argumentString) {
	int monthAhead = 0;
	int i = 0;

	while (argumentString[i] != TERMINATE_SYMBOL) {
		monthAhead = monthAhead * DECIMAL_BASE + (argumentString[i] - '0');
		i++;
	}

	return monthAhead;
}

void handleForecastCommand(FinanceProfile& financeProfile, const char* argumentString) {
	if (isArgumentMissing(argumentString, "Months missing.")) {
		return;
	}
	else {
		int monthAhead = parseMonthsAhead(argumentString);

		if (monthAhead <= 0) {
			std::cout << "Invalid months.";
			newLine();
		}
		else {
			forecast(financeProfile, monthAhead);
		}
	}
}
void handleSearchCommand(FinanceProfile& financeProfile, const char* argumentString) {
	if (isArgumentMissing(argumentString, "Months missing.")) {
		return;
	}
	else {
		searchMonth(financeProfile, argumentString);
	}
}

void handleSortCommand(FinanceProfile& financeProfile, const char* argumentString)
{
	if (isArgumentMissing(argumentString, "Sort type missing.")) {
		return;
	}
	else {
		sortMonths(financeProfile, argumentString);
	}
}

bool isArgumentMissing(const char* argument, const char* message) {
	if (argument[0] == TERMINATE_SYMBOL) {
		std::cout << message;
		newLine();
		return true;
	}
	return false;
}