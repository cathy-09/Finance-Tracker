#include <iostream>

int const MAX_COMMAND_LENGTH = 30;
int const MAX_MONTH = 12;
char const TERMINATE_SYMBOL = '\0';

int totalMonths = 0;
MonthData months[MAX_MONTH];

int myStringCompare(const char* a, const char* b);
void setupProfile();
void addData();
void printBalanceColored(double balance);

struct MonthData {
    double income;
    double expense;
};

const char* monthNames[13] = {
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
    while (true) {
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
    std::cout << "Profile created successfully." << std::endl;
}

void addData() 
{
    int enterMonth;
    std::cin >> enterMonth;

    if (enterMonth < 1 || enterMonth > totalMonths) 
    {
        std::cout << "Invalid month!" << std::endl;
        return;
    }

    std::cout << "Enter income: ";
    std::cin >> months[enterMonth].income;

    std::cout << "Enter expense: ";
    std::cin >> months[enterMonth].expense;

    double balance = months[enterMonth].income - months[enterMonth].expense;

    std::cout << "Result: Balance for " << monthNames[enterMonth] << ": " << balance << std::endl;
    printBalanceColored(balance);
}

void printBalanceColored(double balance) 
{
    if (balance < 0)
    {
        std::cout << "\033[1;31m" << "Negative Balance!" << "\033[0m" << std::endl;
    }
    else 
    {
        std::cout << "\033[1;32m" << "Positive Balance!" << "\033[0m" << std::endl;
    }
}