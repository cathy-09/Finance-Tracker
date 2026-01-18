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
* Header file with add command declarations
*
*/

#pragma once
#include "structures.h"

void addData(FinanceProfile& financeProfile);
bool isValidMonthIndex(FinanceProfile& financeProfile, int month);
void inputMonthData(FinanceProfile& financeProfile, int month);
double calculateMonthBalance(FinanceProfile& financeProfile, int month);
void printMonthResult(FinanceProfile& financeProfile, int month, double balance);
int countEnteredMonths(FinanceProfile& financeProfile);
bool isMonthAlreadyEntered(FinanceProfile& financeProfile, int month);