#include <iostream>

const int MAX_COMMAND_LENGTH = 30;
const int MAX_K_LENGTH = 3;
const int MAX_TYPE_LENGTH = 20;
const char TERMINATE_SYMBOL = '\0';
const int MAX_MONTH_NAME = 13;
const int MAX_MONTHS_IN_YEAR = 12;
const double PERCENT = 100.0;

struct MonthData
{
    double income;
    double expense;
};

int totalMonths = 0;
MonthData* months = nullptr;

const char* monthNames[MAX_MONTH_NAME] =
{
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