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
* File with helper functions implementation
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

int myStringCompare(const char* firstString, const char* secondString) {
	int i = 0;
	while (firstString[i] != TERMINATE_SYMBOL && secondString[i] != TERMINATE_SYMBOL) {
		if (firstString[i] < secondString[i]) {
			return -1;
		}
		if (firstString[i] > secondString[i]) {
			return 1;
		}
		i++;
	}
	if (firstString[i] == TERMINATE_SYMBOL && secondString[i] == TERMINATE_SYMBOL) {
		return 0;
	}
	if (firstString[i] == TERMINATE_SYMBOL) {
		return -1;
	}
	return 1;
}

void mySwap(int& firstValue, int& secondValue) {
	if (&firstValue == &secondValue) {
		return;
	}

	int tempValue = firstValue;
	firstValue = secondValue;
	secondValue = tempValue;
}

double myAbs(double value) {
	if (value < 0) {
		return -value;
	}
	return value;
}

void newLine() {
	std::cout << std::endl;
}

int myStringLength(const char* text) {
	int length = 0;
	while (text[length] != TERMINATE_SYMBOL) {
		length++;
	}
	return length;
}

void myStringConcat(char* sourceString, char* destinationString) {
	while (*destinationString != TERMINATE_SYMBOL) {
		destinationString++;
	}
	while (*sourceString != TERMINATE_SYMBOL) {
		*destinationString = *sourceString;
		sourceString++;
		destinationString++;
	}
	*destinationString = TERMINATE_SYMBOL;
}

char* getArgumentFromCommand(const char* fullCommand) {
	char* argumentString = new char[MAX_COMMAND_LENGTH];
	argumentString[0] = TERMINATE_SYMBOL;
	int currentIndex = 0;
	while (fullCommand[currentIndex] != TERMINATE_SYMBOL && fullCommand[currentIndex] != ' ') {
		currentIndex++;
	}
	while (fullCommand[currentIndex] == ' ') {
		currentIndex++;
	}
	myStringConcat((char*)(fullCommand + currentIndex), argumentString);
	return argumentString;
}

char* getCommandWord(const char* fullCommand) {
	char* commandWord = new char[30];
	int currentIndex = 0;
	while (fullCommand[currentIndex] != TERMINATE_SYMBOL && fullCommand[currentIndex] != ' ') {
		commandWord[currentIndex] = fullCommand[currentIndex];
		currentIndex++;
	}
	commandWord[currentIndex] = TERMINATE_SYMBOL;
	return commandWord;
}

void printBalanceColored(double balance) {
	if (balance > 0) {
		std::cout << "\033[1;32m+";
	}
	else if (balance < 0) {
		std::cout << "\033[1;31m";
	}
	else {
		std::cout << "\033[1;33m";
	}

	printDoubleFixed(balance);

	std::cout << "\033[0m";
}

bool ensureProfile(FinanceProfile& financeProfile, const char* message) {
	if (financeProfile.months == nullptr) {
		std::cout << message;
		newLine();
		return false;
	}
	return true;
}

double myRound(double value, int precision) {
	double factor = 1.0;
	for (int i = 0; i < precision; i++) {
		factor *= 10.0;
	}

	if (value >= 0) {
		return (long long)(value * factor + 0.5) / factor;
	}
	else {
		return (long long)(value * factor - 0.5) / factor;
	}
}

void printSpaces(int count) {
	for (int i = 0; i < count; i++) {
		std::cout << ' ';
	}
}

void toLowerCase(char* text) {
	int charIndex = 0;
	while (text[charIndex] != TERMINATE_SYMBOL) {
		if (text[charIndex] >= 'A' && text[charIndex] <= 'Z') {
			text[charIndex] = text[charIndex] - 'A' + 'a';
		}
		charIndex++;
	}
}

int countDigits(long long value)
{
	if (value == 0) {
		return 1;
	}

	int count = 0;
	long long temp = value;

	if (temp < 0) {
		temp = -temp;
	}

	while (temp != 0) {
		count++;
		temp /= DECIMAL_BASE;
	}

	return count;
}

void splitDouble(double originalValue, long long& wholePart, int& fractionalPart) {
	wholePart = (long long)originalValue;
	fractionalPart = (int)((originalValue - wholePart) * FRACTION_SCALE + 0.5);

	if (fractionalPart < 0) {
		fractionalPart = -fractionalPart;
	}
}

void printFraction(int fractionalPart) {
	if (fractionalPart < FRACTION_TWO_DIGITS) {
		std::cout << "0";
	}
	std::cout << fractionalPart;
}

void printTextAligned(const char* text, int width) {
	int length = myStringLength(text);
	std::cout << text;

	printSpaces(width - length);
}

void printDoubleFixed(double value) {
	long long wholePart;
	int fractionalPart;

	splitDouble(value, wholePart, fractionalPart);

	std::cout << wholePart << ".";
	printFraction(fractionalPart);
}

void printDoubleAligned(double value, int width) {
	long long wholePart;
	int fractionalPart;

	splitDouble(value, wholePart, fractionalPart);

	int length = countDigits(wholePart) + POINT_AND_TWO_SYMBOLS;

	printSpaces(width - length);
	std::cout << wholePart << ".";
	printFraction(fractionalPart);
}

void printBalanceAligned(double balance, int width) {
	long long intPart;
	int fracPart;

	splitDouble(balance, intPart, fracPart);

	int length = countDigits(intPart) + POINT_AND_TWO_SYMBOLS;

	if (balance >= 0) {
		length++;
	}

	int spaces = width - length;
	if (balance > 0) {
		spaces++;
	}

	printSpaces(spaces);
	printBalanceColored(balance);
}

void printHorizontalLine() {
	for (int i = 0; i < TOTAL_WIDTH; i++) {
		std::cout << "-";
	}
	newLine();
}