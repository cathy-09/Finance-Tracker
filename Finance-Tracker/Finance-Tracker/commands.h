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
* Header file with commands declarations
*
*/

#pragma once
#include "structures.h"

void handleCommand(FinanceProfile& financeProfile, char* commandWord, char* argumentString, bool& exitProgram);

void handleForecastCommand(FinanceProfile& financeProfile, const char* argumentString);
void handleSearchCommand(FinanceProfile& financeProfile, const char* argumentString);
void handleSortCommand(FinanceProfile& financeProfile, const char* argumentString);

int parseMonthsAhead(const char* argumentString);
bool isArgumentMissing(const char* argument, const char* message);
void printHelp();
void welcome();