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
* File with main program
*
*/

#include <iostream>

#include "constants.h"
#include "structures.h"
#include "commands.h"
#include "setup.h"
#include "add.h"
#include "report.h"
#include "search.h"
#include "sort.h"
#include "forecast.h"
#include "chart.h"
#include "utils.h"

int main() {
	welcome();
	const char* defaultMonthNames[MAX_MONTH_NAME] = {
		"",
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};

	FinanceProfile financeProfile;
	financeProfile.months = nullptr;
	financeProfile.totalMonths = 0;
	financeProfile.monthNames = defaultMonthNames;

	char command[MAX_COMMAND_LENGTH];
	bool exitProgram = false;
	
	while (!exitProgram) {
		std::cout << "> ";
		std::cin.getline(command, MAX_COMMAND_LENGTH);

		char* commandWord = getCommandWord(command);
		toLowerCase(commandWord);
		char* argumentString = getArgumentFromCommand(command);

		handleCommand(financeProfile, commandWord, argumentString, exitProgram);

		delete[] commandWord;
		delete[] argumentString;
	}

	delete[] financeProfile.months;
}