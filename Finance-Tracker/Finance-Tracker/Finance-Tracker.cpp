#include <iostream>

int const MAX_COMMAND_LENGTH = 30;
int const MAX_K_LENGTH = 3;
int const MAX_TYPE_LENGTH = 20;
char const TERMINATE_SYMBOL = '\0';
int const MAX_MONTH_NAME = 13;
int const MAX_MONTHS_IN_YEAR = 12;
double const PERCENT = 100.0;

int totalMonths = 0;

bool isValidMonthCount(int months);
void initializeMonths(struct MonthData* monthsArray, int monthsCount);
void setupProfile();
void addData();
bool isValidMonthIndex(int month);
void inputMonthData(int month);
double calculateMonthBalance(int month);
void printMonthResult(int month, double balance);
void report();
void printReportHeader();
double printMonthReport(int monthIndex);
void printReportSummary(double totalIncome, double totalExpense);
void searchMonth(const char* name);
int findMonthIndex(const char* monthName);
void printMonthDetails(int monthIndex);
void mySwap(int& firstValue, int& secondValue);
void sortMonths(const char* type);
double getMonthValue(int monthIndex, const char* type);
bool isValidSortType(const char* type);
void sortOrderByType(int* order, const char* type);
void printTopMonths(int* order, const char* type);
void forecast(int monthAhead);
void calculateSavings(double& savings, double& averageChange);
void forecastPositive(double savings, double averageChange, int monthsAhead);
void forecastNegative(double savings, double averageChange);
void chart();
double getMaxMonthTotal();
int calculateChartStep(double maxValue);
void drawChartBody(double maxValue, int step);
void printChartMonths();

/* Utility functions */
int myStringCompare(const char* a, const char* b);
void myStringConcat(char* sourceString, char* destinationString);
char* getArgumentFromCommand(const char* fullCommand);
char* getCommandWord(const char* fullCommand);
double myAbs(double value);
void newLine();
void printBalanceColored(double balance);

struct MonthData 
{
    double income;
    double expense;
};
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

int main()
{
    char command[MAX_COMMAND_LENGTH];
    while (true) 
    {
        std::cout << "> ";
        std::cin.getline(command, MAX_COMMAND_LENGTH);
        char* commandWord = getCommandWord(command);
        char* argumentString = getArgumentFromCommand(command);
        
        if (myStringCompare(commandWord, "setup") == 0)
        {
            setupProfile();
        }
        else if (myStringCompare(commandWord, "add") == 0)
        {
            addData();
        }
        else if (myStringCompare(commandWord, "report") == 0)
        {
            report();
        }
        else if (myStringCompare(commandWord, "search") == 0)
        {
            if (argumentString[0] == '\0')
            {
                std::cout << "Month name missing.";
                newLine();
            }
            else
            {
                searchMonth(argumentString);
            }
        }
        else if (myStringCompare(commandWord, "sort") == 0)
        {
            if (argumentString[0] == '\0')
            {
                std::cout << "Sort type missing.";
                newLine();
            }
            else
            {
                sortMonths(argumentString);
            }
        }
        else if (myStringCompare(commandWord, "forecast") == 0)
        {
            if (argumentString[0] == '\0')
            {
                std::cout << "Months missing.";
                newLine();
            }
            else
            {
                int monthAhead = 0;
                int i = 0;

                while (argumentString[i] != TERMINATE_SYMBOL)
                {
                    monthAhead = monthAhead * 10 + (argumentString[i] - '0');
                    i++;
                }

                if (monthAhead <= 0)
                {
                    std::cout << "Invalid months.";
                    newLine();
                }
                else
                {
                    forecast(monthAhead);
                }
            }
        }
        else if (myStringCompare(commandWord, "chart") == 0)
        {
            chart();
        }
        else
        {
            std::cout << "Invalid command.";
            newLine();
        }
		delete[] commandWord;
        delete[] argumentString;
    }
    delete[] months;
}

void setupProfile()
{
    std::cout << "Enter number of months: ";
    std::cin >> totalMonths;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a number.";
        newLine();
        totalMonths = 0;
        return;
    }

    if (!isValidMonthCount(totalMonths))
    {
        std::cout << "Invalid months!";
        newLine();
        totalMonths = 0;
        return;
    }

    delete[] months;
    months = new MonthData[totalMonths + 1];

    initializeMonths(months, totalMonths);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Profile created successfully.";
    newLine();
}

void initializeMonths(MonthData* monthsArray, int monthsCount)
{
    for (int i = 1; i <= monthsCount; i++)
    {
        monthsArray[i].income = 0;
        monthsArray[i].expense = 0;
    }
}

bool isValidMonthCount(int months)
{
    return months > 0 && months <= 12;
}

bool isValidMonthIndex(int month)
{
    return month >= 1 && month <= totalMonths;
}

void addData()
{
    int month = 0;

    std::cout << "Month: ";
    std::cin >> month;

    if (!isValidMonthIndex(month))
    {
        std::cout << "Invalid month!";
        newLine();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    inputMonthData(month);

    double balance = calculateMonthBalance(month);
    printMonthResult(month, balance);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void inputMonthData(int month)
{
    std::cout << "Enter income: ";
    std::cin >> months[month].income;

    std::cout << "Enter expense: ";
    std::cin >> months[month].expense;
}
double calculateMonthBalance(int month)
{
    return months[month].income - months[month].expense;
}
void printMonthResult(int month, double balance)
{
    std::cout << "Result: Balance for " << monthNames[month] << ": ";
    printBalanceColored(balance);
    newLine();
}

void report()
{
    double totalIncome = 0;
    double totalExpense = 0;

    printReportHeader();

    for (int i = 1; i <= totalMonths; i++)
    {
        printMonthReport(i);
        totalIncome += months[i].income;
        totalExpense += months[i].expense;
    }

    printReportSummary(totalIncome, totalExpense);
}

void printReportHeader()
{
    std::cout << "Month | Income | Expense | Balance";
    newLine();
    std::cout << "----------------------------------";
    newLine();
}
double printMonthReport(int monthIndex)
{
    double balance = months[monthIndex].income - months[monthIndex].expense;

    std::cout << monthNames[monthIndex] << " | "
        << months[monthIndex].income << " | "
        << months[monthIndex].expense << " | ";

    printBalanceColored(balance);
    newLine();

    return balance;
}
void printReportSummary(double totalIncome, double totalExpense)
{
    std::cout << "----------------------------------";
    newLine();

    double average = (totalIncome - totalExpense) / totalMonths;

    std::cout << "Total income: " << totalIncome;
    newLine();
    std::cout << "Total expense: " << totalExpense;
    newLine();
    std::cout << "Average balance: ";
    printBalanceColored(average);
    newLine();
}
void searchMonth(const char* name)
{
    int index = findMonthIndex(name);

    if (index == -1)
    {
        std::cout << "Month not found.";
        newLine();
        return;
    }

    printMonthDetails(index);
}
int findMonthIndex(const char* monthName)
{
    for (int i = 1; i <= totalMonths; i++)
    {
        if (myStringCompare(monthName, monthNames[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}
void printMonthDetails(int monthIndex)
{
    double income = months[monthIndex].income;
    double expense = months[monthIndex].expense;
    double balance = income - expense;

    std::cout << "Income: " << income;
    newLine();

    std::cout << "Expense: " << expense;
    newLine();

    std::cout << "Balance: ";
    printBalanceColored(balance);
    newLine();

    if (income > 0)
    {
        double ratio = (expense * PERCENT) / income;
        std::cout << "Expense ratio: " << ratio << "%";
        newLine();
    }
    else
    {
        std::cout << "Expense ratio: no income.";
        newLine();
    }
}
void mySwap(int& firstValue, int& secondValue)
{
    if (&firstValue == &secondValue)
    {
        return;
    }
    int tempValue = firstValue;
    firstValue = secondValue;
    secondValue = tempValue;
}
void sortMonths(const char* type)
{
    if (!isValidSortType(type))
    {
        std::cout << "Invalid sort type.";
        newLine();
        return;
    }

    int* order = new int[totalMonths + 1];
    for (int i = 1; i <= totalMonths; i++)
    {
        order[i] = i;
    }

    sortOrderByType(order, type);
    printTopMonths(order, type);

    delete[] order;
}
double getMonthValue(int monthIndex, const char* type)
{
    if (myStringCompare(type, "income") == 0)
    {
        return months[monthIndex].income;
    }
    else if (myStringCompare(type, "expense") == 0)
    {
        return months[monthIndex].expense;
    }
    else if (myStringCompare(type, "balance") == 0)
    {
        return months[monthIndex].income - months[monthIndex].expense;
    }
    return 0;
}
bool isValidSortType(const char* type)
{
    return myStringCompare(type, "income") == 0 ||
        myStringCompare(type, "expense") == 0 ||
        myStringCompare(type, "balance") == 0;
}
void sortOrderByType(int* order, const char* type)
{
    for (int i = 1; i <= totalMonths; i++)
    {
        for (int j = 1; j < totalMonths; j++)
        {
            double firstValue = getMonthValue(order[j], type);
            double secondValue = getMonthValue(order[j + 1], type);

            if (firstValue < secondValue)
            {
                mySwap(order[j], order[j + 1]);
            }
        }
    }
}
void printTopMonths(int* order, const char* type)
{
    std::cout << "Sorted by monthly " << type << " (descending):";
    newLine();

    for (int k = 1; k <= MAX_K_LENGTH && k <= totalMonths; k++)
    {
        int monthIndex = order[k];
        std::cout << k << ". " << monthNames[monthIndex] << ": ";
        printBalanceColored(getMonthValue(monthIndex, type));
        newLine();
    }
}

void forecast(int monthAhead)
{
    double savings = 0;
    double averageChange = 0;

    calculateSavings(savings, averageChange);

    std::cout << "Current savings: ";
    printBalanceColored(savings);
    newLine();

    std::cout << "Average monthly change: ";
    printBalanceColored(averageChange);
    newLine();

    if (averageChange >= 0)
    {
        forecastPositive(savings, averageChange, monthAhead);
    }
    else
    {
        forecastNegative(savings, averageChange);
    }
}
void calculateSavings(double& savings, double& averageChange)
{
    double totalIncome = 0;
    double totalExpense = 0;

    for (int i = 1; i <= totalMonths; i++)
    {
        totalIncome += months[i].income;
        totalExpense += months[i].expense;
    }

    savings = totalIncome - totalExpense;
    averageChange = savings / totalMonths;
}
void forecastPositive(double savings, double averageChange, int monthsAhead)
{
    double futureSavings = savings + averageChange * monthsAhead;

    std::cout << "Predicted savings after " << monthsAhead << " months: ";
    printBalanceColored(futureSavings);
    newLine();
}

void forecastNegative(double savings, double averageChange)
{
    double remainingSavings = savings;
    int month = 0;

    while (remainingSavings > 0 &&
        month <= totalMonths * MAX_MONTHS_IN_YEAR)
    {
        remainingSavings += averageChange;
        month++;
    }

    std::cout << "Expected to run out of money after " << month << " months.";
    newLine();
}

void chart()
{
    std::cout << "=== YEARLY FINANCIAL CHART ===";
    newLine();

    double maxValue = getMaxMonthTotal();
    int step = calculateChartStep(maxValue);

    drawChartBody(maxValue, step);

    std::cout << "-------------------------";
    newLine();

    printChartMonths();
}
double getMaxMonthTotal()
{
    double maxValue = 0;

    for (int i = 1; i <= totalMonths; i++)
    {
        double monthTotal = months[i].income + months[i].expense;
        if (monthTotal > maxValue)
        {
            maxValue = monthTotal;
        }
    }

    return maxValue;
}
int calculateChartStep(double maxValue)
{
    int step = maxValue / 5;
    if (step < 1)
    {
        step = 1;
    }
    return step;
}
void drawChartBody(double maxValue, int step)
{
    for (int level = maxValue; level >= 0; level -= step)
    {
        std::cout << level << " | ";

        for (int m = 1; m <= MAX_MONTHS_IN_YEAR; m++)
        {
            double monthTotal = 0;

            if (m <= totalMonths)
            {
                monthTotal = months[m].income + months[m].expense;
            }

            if (monthTotal >= level)
            {
                std::cout << "# ";
            }
            else
            {
                std::cout << "  ";
            }
        }
        newLine();
    }
}
void printChartMonths()
{
    std::cout << "    ";

    for (int m = 1; m <= MAX_MONTHS_IN_YEAR; m++)
    {
        std::cout
            << monthNames[m][0]
            << monthNames[m][1]
            << monthNames[m][2]
            << " ";
    }
    newLine();
}
