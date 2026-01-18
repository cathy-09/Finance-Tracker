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
* Header file with structures definitions
*
*/

#pragma once

struct MonthData {
    double income;
    double expense;
};

struct FinanceProfile {
    int totalMonths;
    MonthData* months;
    const char** monthNames;
};