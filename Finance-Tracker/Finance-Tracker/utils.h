#pragma once
#include "structures.h"

int myStringCompare(const char* a, const char* b);
void myStringConcat(char* sourceString, char* destinationString);
int myStringLength(const char* text);
double myAbs(double value);
void mySwap(int& firstValue, int& secondValue);

char* getArgumentFromCommand(const char* fullCommand);
char* getCommandWord(const char* fullCommand);

void newLine();
void printBalanceColored(double balance);
bool ensureProfile(struct FinanceProfile& financeProfile, const char* message);

double myRound(double value, int precision);
void printSpaces(int count);
void toLowerCase(char* text);

/* formatting helpers */
void printTextAligned(const char* text, int width);
void printDoubleAligned(double value, int width);
void printBalanceAligned(double balance, int width);
void printDoubleFixed(double value);
int countDigits(long long value);
void printFraction(int fracPart);
void splitDouble(double value, long long& intPart, int& fracPart);
void printHorizontalLine();