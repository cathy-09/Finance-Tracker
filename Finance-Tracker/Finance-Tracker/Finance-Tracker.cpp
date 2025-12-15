#include <iostream>

int const MAX_COMMAND_LENGTH = 30;
int const MAX_MONTH = 12;
char const TERMINATE_SYMBOL = '\0';
int const MAX_MONTH_NAME = 13;

int totalMonths = 0;

int myStringCompare(const char* a, const char* b);
void setupProfile();
void addData();
void printBalanceColored(double balance);
void report();

struct MonthData 
{
    double income;
    double expense;
};
MonthData months[MAX_MONTH];

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
        if (myStringCompare(command, "setup") == 0)
        {
            setupProfile();
        }
        else if (strcmp(command, "add") == 0)
        {
            addData();
        }
        else if (strcmp(command, "report") == 0)
        {
            report();
        }
        else if (strcmp(command, "search") == 0) 
        {
            char monthText[MAX_MONTH_NAME];
            std::cin >> monthText;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //TODO: searchMonth(monthText);
        }
        else 
        {
            std::cout << "Invalid command." << std::endl;
        }
    }
}

int myStringCompare(const char* firstString, const char* secondString) 
{
    int i = 0;
    while (firstString[i] != TERMINATE_SYMBOL && secondString[i] != TERMINATE_SYMBOL)
    {
        if (firstString[i] < secondString[i])
        {
            return -1;
        }
        if (firstString[i] > secondString[i]) 
        {
            return 1;
        }
        i++;
    }
    if (firstString[i] == TERMINATE_SYMBOL && secondString[i] == TERMINATE_SYMBOL) 
    {
        return 0;
    }
    if (firstString[i] == TERMINATE_SYMBOL)
    {
        return -1;
    }
    return 1;
}

void setupProfile()
{
    std::cout << "Enter number of months: ";
    std::cin >> totalMonths;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a number: ";
    }
    if (totalMonths <= 0 || totalMonths > 13)
    {
        std::cout << "Invalid months!" << std::endl;
        totalMonths = 0;
        return;
    }
    for (int i = 1; i <= totalMonths; i++) 
    {
        months[i].income = 0;
        months[i].expense = 0;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Profile created successfully." << std::endl;
}

void addData() 
{
    int enterMonth = 0; 
    std::cout << "Month: ";
    std::cin >> enterMonth;
    if (enterMonth < 1 || enterMonth > totalMonths) 
    {
        std::cout << "Invalid month!" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    std::cout << "Enter income: ";
    std::cin >> months[enterMonth].income;

    std::cout << "Enter expense: ";
    std::cin >> months[enterMonth].expense;

    double balance = months[enterMonth].income - months[enterMonth].expense;

    std::cout << "Result: Balance for " << monthNames[enterMonth] << ": ";
    printBalanceColored(balance);
    std::cout << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printBalanceColored(double balance)
{
    if (balance > 0)
    {
        std::cout << "\033[1;32m+" << balance << "\033[0m";
    }
    else if (balance < 0)
    {
        std::cout << "\033[1;31m" << balance << "\033[0m";
    }
    else
    {
        std::cout << "\033[1;33m" << balance << "\033[0m";
    }
}
void report()
{
    double totalIncome = 0;
    double totalExpense = 0;
    std::cout << "Month | Income | Expense | Balance" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    for (int i = 1; i <= totalMonths; i++) 
    {
        double balance = months[i].income - months[i].expense;

        std::cout << monthNames[i] << " | "
            << months[i].income << " | "
            << months[i].expense << " | ";
        printBalanceColored(balance);
        std::cout << std::endl;

        totalIncome = totalIncome+ (months[i].income);
        totalExpense = totalExpense + (months[i].expense);
    }
    std::cout << "----------------------------------" << std::endl;
    double average = (totalIncome - totalExpense) / totalMonths;

    std::cout << "Total income: " << totalIncome << std::endl;
    std::cout << "Total expense: " << totalExpense << std::endl;
    std::cout << "Average balance: ";
    printBalanceColored(average);
    std::cout << std::endl;
}