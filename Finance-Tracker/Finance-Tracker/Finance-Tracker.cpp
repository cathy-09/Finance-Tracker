#include <iostream>

int const MAX_COMMAND_LENGTH = 30;
char const TERMINATE_SYMBOL = '\0';
int const MAX_MONTH_NAME = 13;
double const PERCENT = 100.0;

int totalMonths = 0;

int myStringCompare(const char* a, const char* b);
void setupProfile();
void addData();
void printBalanceColored(double balance);
void report();
void searchMonth(const char* name);
void mySwap(int& firstValue, int& secondValue);
void sortMonths(const char* type);

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
            searchMonth(monthText);
        }
        else if (strcmp(command, "sort") == 0) {
            char type[20];
            std::cin >> type;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            sortMonths(type);
        }
        else 
        {
            std::cout << "Invalid command." << std::endl;
        }
    }
    delete[] months;
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
    delete[] months;
    months = new MonthData[totalMonths + 1];
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
void searchMonth(const char* name)
{
	int index = -1;
    for (int i = 1; i <= totalMonths; i++)
    {
        if (myStringCompare(name, monthNames[i]) == 0) 
        {
            index = i;
			break;
        }
        if (index == -1 || index > totalMonths)
        {
            std::cout << "Month not found." << std::endl;
            return;
        }
        double income = months[index].income;
        double expense = months[index].expense;
        double balance = income - expense;
        std::cout << "Income: " << income << std::endl;
        std::cout << "Expense: " << expense << std::endl;
        std::cout << "Balance: ";
        printBalanceColored(balance);
        std::cout << std::endl;
        if (income > 0)
        {
            double ratio = (expense * PERCENT) / income;
            std::cout << "Expense ratio: " << ratio << "%";
            std::cout << std::endl;
        }
        else 
        {
            std::cout << "Expense ratio: no income.";
            std::cout << std::endl;
        }
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
    int* order = new int[totalMonths + 1];
    for (int i = 1; i <= totalMonths; i++)
    {
        order[i] = i;
    }
    for (int i = 1; i <= totalMonths; i++)
    {
        for (int j = 1; j <= totalMonths - 1; j++)
        {
			double firstValue = 0;
            double secondValue = 0;
            if (myStringCompare(type, "income") == 0) 
            {
                firstValue = months[order[j]].income;
                secondValue = months[order[j + 1]].income;
            }
            else if (myStringCompare(type, "expense") == 0) 
            {
                firstValue = months[order[j]].expense;
                secondValue = months[order[j + 1]].expense;
            }
            else if (myStringCompare(type, "balance") == 0) 
            {
                firstValue = months[order[j]].income - months[order[j]].expense;
                secondValue = months[order[j + 1]].income - months[order[j + 1]].expense;
            }
            else 
            {
                std::cout << "Invalid sort type." << std::endl;
                delete[] order;
                return;
            }
            if (firstValue < secondValue) 
            {
                mySwap(order[j], order[j + 1]);
			}
        }
    }
    std::cout << "Sorted by monthly " << type << " (descending):" << std::endl;
    for (int k = 1; k <= 3 && k <= totalMonths; k++)
    {
        int monthIndex = order[k];
        std::cout << k << ". " << monthNames[monthIndex] << ": ";
        double value = 0;
        if (myStringCompare(type, "income") == 0)
        {
            value = months[monthIndex].income;
        }
        else if (myStringCompare(type, "expense") == 0)
        {
            value = months[monthIndex].expense;
        }
        else
        {
			value = months[monthIndex].income - months[monthIndex].expense;
        }
        printBalanceColored(value);
        std::cout << std::endl;
    }
}