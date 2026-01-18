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
* Header file with chart command declarations
*
*/

#pragma once
#include "structures.h"

void chart(FinanceProfile& financeProfile);
int calculateChartStep(double minBalance, double maxBalance);
void drawChartBody(FinanceProfile& financeProfile, double minBalance, double maxBalance);
void printChartMonths(FinanceProfile& financeProfile);
void printChartHeader();