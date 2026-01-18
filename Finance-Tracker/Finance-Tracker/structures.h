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