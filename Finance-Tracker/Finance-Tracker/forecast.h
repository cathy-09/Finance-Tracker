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
* Header file with forecast command declarations
*
*/

#pragma once
#include "structures.h"

void forecast(FinanceProfile& financeProfile, int monthAhead);
void calculateSavings(FinanceProfile& financeProfile, double& savings, double& averageChange);
void forecastPositive(double savings, double averageChange, int monthsAhead);
void forecastNegative(FinanceProfile& financeProfile, double savings, double averageChange);