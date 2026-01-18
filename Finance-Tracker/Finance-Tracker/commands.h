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