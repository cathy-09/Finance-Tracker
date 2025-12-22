#include <iostream>

int const MAX_COMMAND_LENGTH = 30;
int const MAX_K_LENGTH = 3;
int const MAX_TYPE_LENGTH = 20;
char const TERMINATE_SYMBOL = '\0';
int const MAX_MONTH_NAME = 13;
int const MAX_MONTHS_IN_YEAR = 12;
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
void forecast(int monthAhead);
void newLine();
void myStringConcat(char* sourceString, char* destinationString);
char* getArgumentFromCommand(const char* fullCommand);
char* getCommandWord(const char* fullCommand);
double myAbs(double value);
void chart();

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
double myAbs(double value)
{
    if (value < 0)
    {
        return -value;
    }
    return value;
}

void newLine()
{
    std::cout << std::endl;
}
void myStringConcat(char* sourceString, char* destinationString)
{
    while (*destinationString != '\0')
    {
        destinationString++;
    }
    while (*sourceString != '\0')
    {
        *destinationString = *sourceString;
        sourceString++;
        destinationString++;
    }
    *destinationString = '\0';
}
char* getArgumentFromCommand(const char* fullCommand)
{
    char* argumentString = new char[MAX_COMMAND_LENGTH];
    argumentString[0] = TERMINATE_SYMBOL;
    int i = 0;
    while (fullCommand[i] != TERMINATE_SYMBOL && fullCommand[i] != ' ')
    {
        i++;
    }
    while (fullCommand[i] == ' ')
    {
        i++;
    }
    myStringConcat((char*)(fullCommand + i), argumentString);
    return argumentString;
}
char* getCommandWord(const char* fullCommand)
{
    char* commandWord = new char[MAX_COMMAND_LENGTH];
    int i = 0;
    while (fullCommand[i] != TERMINATE_SYMBOL && fullCommand[i] != ' ')
    {
        commandWord[i] = fullCommand[i];
        i++;
    }
    commandWord[i] = TERMINATE_SYMBOL;
    return commandWord;
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
        std::cout << "Invalid months!";
        newLine();
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

    std::cout << "Profile created successfully.";
	newLine();
}

void addData() 
{
    int enterMonth = 0; 
    std::cout << "Month: ";
    std::cin >> enterMonth;
    if (enterMonth < 1 || enterMonth > totalMonths) 
    {
        std::cout << "Invalid month!";
        newLine();
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
    newLine();
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
    std::cout << "Month | Income | Expense | Balance";
    newLine();
    std::cout << "----------------------------------";
	newLine();
    for (int i = 1; i <= totalMonths; i++) 
    {
        double balance = months[i].income - months[i].expense;

        std::cout << monthNames[i] << " | "
            << months[i].income << " | "
            << months[i].expense << " | ";
        printBalanceColored(balance);
        newLine();

        totalIncome = totalIncome+ (months[i].income);
        totalExpense = totalExpense + (months[i].expense);
    }
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
    int index = -1;
    for (int i = 1; i <= totalMonths; i++) 
    {
        if (myStringCompare(name, monthNames[i]) == 0) 
        {
            index = i;
            break;
        }
    }
    if (index == -1 || index > totalMonths) 
    {
        std::cout << "Month not found.";
		newLine();
        return;
    }
    double income = months[index].income;
    double expense = months[index].expense;
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
                std::cout << "Invalid sort type.";
				newLine();
                delete[] order;
                return;
            }
            if (firstValue < secondValue) 
            {
                mySwap(order[j], order[j + 1]);
			}
        }
    }
    std::cout << "Sorted by monthly " << type << " (descending):";
	newLine();
    for (int k = 1; (k <= MAX_K_LENGTH && k <= totalMonths); k++)
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
		newLine();
    }
}
void forecast(int monthAhead)
{
    double totalIncome = 0;
    double totalExpense = 0;
    for (int i = 1; i <= totalMonths; i++) 
    {
        totalIncome += months[i].income;
        totalExpense += months[i].expense;
    }
    double savings = totalIncome - totalExpense;
    double averageChange = savings / totalMonths;
    std::cout << "Current savings: ";
    printBalanceColored(savings);
	newLine();
    std::cout << "Average monthly change: ";
    printBalanceColored(averageChange);
    newLine();
    if (averageChange >= 0) 
    {
        double futureSavings = savings + averageChange * monthAhead;
        std::cout << "Predicted savings after " << monthAhead << " months: ";
        printBalanceColored(futureSavings);
        newLine();
    }
    else
    {
        double remainingSavings = savings;
        int month = 0;

        while (remainingSavings > 0 && month <= totalMonths * MAX_MONTHS_IN_YEAR)
        {
            remainingSavings = remainingSavings + myAbs(averageChange);
            month++;
        }

        std::cout << "Expected to run out of money after " << month << " months.";
        newLine();
    }
}
void chart()
{
    std::cout << "=== YEARLY FINANCIAL CHART ===";
    newLine();

    double maxValue = 0;
    for (int i = 1; i <= totalMonths; i++)
    {
        double monthTotal = months[i].income + months[i].expense;
        if (monthTotal > maxValue)
        {
            maxValue = monthTotal;
        }
    }

    int step = maxValue / 5;
    if (step < 1)
    {
        step = 1;
    }

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

    std::cout << "-------------------------";
    newLine();
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