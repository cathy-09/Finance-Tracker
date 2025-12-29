#include <iostream>

int const MAX_COMMAND_LENGTH = 30;
int const MAX_K_LENGTH = 3;
int const POINT_AND_TWO_SYMBOLS = 3;
int const MAX_TYPE_LENGTH = 20;
char const TERMINATE_SYMBOL = '\0';
int const MAX_MONTH_NAME = 13;
int const MAX_MONTHS_IN_YEAR = 12;
double const PERCENT = 100.0;
const int COL_MONTH = 10;
const int COL_INCOME = 12;
const int COL_EXPENSE = 12;
const int COL_BALANCE = 12;
const int TOTAL_WIDTH = COL_MONTH + COL_INCOME + COL_EXPENSE + COL_BALANCE + 3 * 3 + 1;

int totalMonths = 0;

/* main */
void processCommand(char* commandWord, char* argumentString, bool& shouldExit);
void handleForecastCommand(const char* argumentString);
void handleSearchCommand(const char* argumentString);
void handleSortCommand(const char* argumentString);
int parseMonthsAhead(const char* argumentString);

/* setupProfile functionally */
void setupProfile();
bool isValidMonthCount(int months);
void initializeMonths(struct MonthData* monthsArray, int monthsCount);

/* addData functionally */
void addData();
bool isValidMonthIndex(int month);
void inputMonthData(int month);
double calculateMonthBalance(int month);
void printMonthResult(int month, double balance);

/* Align */
void printTextAligned(const char* text, int width);
void printDoubleAligned(double value, int width);
void printBalanceAligned(double balance, int width);
void printDoubleFixed(double value);
int countDigits(long long value);
void printFraction(int fracPart);
void splitDouble(double value, long long& intPart, int& fracPart);


/* report functionally */
void report();
void printReportHeader();
double printMonthReport(int monthIndex);
void printReportSummary(double totalIncome, double totalExpense);

/* searchMonth functionally */
void searchMonth(const char* name);
int findMonthIndex(const char* monthName);
void printMonthDetails(int monthIndex);

/* sortMonths functionally */
void sortMonths(const char* type);
bool isValidSortType(const char* type);
void sortOrderByType(int* order, const char* type);
void printTopMonths(int* order, const char* type);
double getMonthValue(int monthIndex, const char* type);

/* forecast functionally */
void forecast(int monthAhead);
void calculateSavings(double& savings, double& averageChange);
void forecastPositive(double savings, double averageChange, int monthsAhead);
void forecastNegative(double savings, double averageChange);

/* chart functionally */
void chart();
int calculateChartStep(double maxValue);
void drawChartBody(double minBalance, double maxBalance, int step);
void printChartMonths();

/* Utility functions */
int myStringCompare(const char* a, const char* b);
void myStringConcat(char* sourceString, char* destinationString);
int myStringLength(const char* text);
double myAbs(double value);
void mySwap(int& firstValue, int& secondValue);
char* getArgumentFromCommand(const char* fullCommand);
char* getCommandWord(const char* fullCommand);
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
	bool exitProgram = false;

	while (!exitProgram)
	{
		std::cout << "> ";
		std::cin.getline(command, MAX_COMMAND_LENGTH);

		char* commandWord = getCommandWord(command);
		char* argumentString = getArgumentFromCommand(command);

		processCommand(commandWord, argumentString, exitProgram);

		delete[] commandWord;
		delete[] argumentString;
	}

	delete[] months;
}

void processCommand(char* commandWord, char* argumentString, bool& exitProgram)
{
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
		handleSearchCommand(argumentString);
	}
	else if (myStringCompare(commandWord, "sort") == 0)
	{
		handleSortCommand(argumentString);
	}
	else if (myStringCompare(commandWord, "forecast") == 0)
	{
		handleForecastCommand(argumentString);
	}
	else if (myStringCompare(commandWord, "chart") == 0)
	{
		chart();
	}
	else if (myStringCompare(commandWord, "exit") == 0)
	{
		report();
		exitProgram = true;
	}
	else
	{
		std::cout << "Invalid command.";
		newLine();
	}
}

int parseMonthsAhead(const char* argumentString)
{
	int monthAhead = 0;
	int i = 0;

	while (argumentString[i] != TERMINATE_SYMBOL)
	{
		monthAhead = monthAhead * 10 + (argumentString[i] - '0');
		i++;
	}

	return monthAhead;
}

void handleForecastCommand(const char* argumentString)
{
	if (argumentString[0] == TERMINATE_SYMBOL)
	{
		std::cout << "Months missing.";
		newLine();
	}
	else
	{
		int monthAhead = parseMonthsAhead(argumentString);

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
void handleSearchCommand(const char* argumentString)
{
	if (argumentString[0] == TERMINATE_SYMBOL)
	{
		std::cout << "Month name missing.";
		newLine();
	}
	else
	{
		searchMonth(argumentString);
	}
}

void handleSortCommand(const char* argumentString)
{
	if (argumentString[0] == TERMINATE_SYMBOL)
	{
		std::cout << "Sort type missing.";
		newLine();
	}
	else
	{
		sortMonths(argumentString);
	}
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

bool isValidMonthIndex(int month)
{
	return month >= 1 && month <= totalMonths;
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

int countDigits(long long value)
{
	if (value == 0)
	{
		return 1;
	}

	int count = 0;
	long long temp = value;

	if (temp < 0)
	{
		temp = -temp;
	}

	while (temp != 0)
	{
		count++;
		temp /= 10;
	}

	return count;
}

void splitDouble(double value, long long& intPart, int& fracPart)
{
	intPart = (long long)value;
	fracPart = (int)((value - intPart) * 100);

	if (fracPart < 0)
	{
		fracPart = -fracPart;
	}
}

void printFraction(int fracPart)
{
	if (fracPart < 10)
	{
		std::cout << "0";
	}
	std::cout << fracPart;
}

void printTextAligned(const char* text, int width)
{
	int length = myStringLength(text);
	std::cout << text;

	for (int i = 0; i < width - length; i++)
	{
		std::cout << ' ';
	}
}

void printDoubleFixed(double value)
{
	long long intPart;
	int fracPart;

	splitDouble(value, intPart, fracPart);

	std::cout << intPart << ".";
	printFraction(fracPart);
}

void printDoubleAligned(double value, int width)
{
	long long intPart;
	int fracPart;

	splitDouble(value, intPart, fracPart);

	int length = countDigits(intPart) + POINT_AND_TWO_SYMBOLS;

	for (int i = 0; i < width - length; i++)
	{
		std::cout << ' ';
	}

	std::cout << intPart << ".";
	printFraction(fracPart);
}

void printBalanceAligned(double balance, int width)
{
	long long intPart;
	int fracPart;

	splitDouble(balance, intPart, fracPart);

	int length = countDigits(intPart) + POINT_AND_TWO_SYMBOLS;

	if (balance >= 0)
	{
		length++; 
	}

	int spaces = width - length;
	if (balance > 0)
	{
		spaces++;
	}

	for (int i = 0; i < spaces; i++)
	{
		std::cout << ' ';
	}

	printBalanceColored(balance);
}

void printHorizontalLine()
{
	for (int i = 0; i < TOTAL_WIDTH; i++)
	{
		std::cout << "-";
	}
	newLine();
}

void printReportHeader()
{
	printTextAligned("Month", COL_MONTH);
	std::cout << " | ";
	printTextAligned("Income", COL_INCOME);
	std::cout << " | ";
	printTextAligned("Expense", COL_EXPENSE);
	std::cout << " | ";
	printTextAligned("Balance", COL_BALANCE);
	newLine();

	printHorizontalLine();
}

double printMonthReport(int monthIndex)
{
	double balance = months[monthIndex].income - months[monthIndex].expense;

	printTextAligned(monthNames[monthIndex], COL_MONTH);
	std::cout << " | ";
	printDoubleAligned(months[monthIndex].income, COL_INCOME);
	std::cout << " | ";
	printDoubleAligned(months[monthIndex].expense, COL_EXPENSE);
	std::cout << " | ";
	printBalanceAligned(balance, COL_BALANCE);

	newLine();
	return balance;
}

void printReportSummary(double totalIncome, double totalExpense)
{
	printHorizontalLine();

	double average = (totalIncome - totalExpense) / totalMonths;

	std::cout << "Total income: ";
	printDoubleFixed(totalIncome);
	newLine();

	std::cout << "Total expense: ";
	printDoubleFixed(totalExpense);
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

		double value = getMonthValue(monthIndex, type);

		if (myStringCompare(type, "expense") == 0)
		{
			std::cout << "\033[1;31m";
			printDoubleFixed(value);
			std::cout << "\033[0m";
		}
		else
		{
			printBalanceColored(value);
		}

		newLine();
	}
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

	double minBalance = months[1].income - months[1].expense;
	double maxBalance = minBalance;

	for (int i = 2; i <= totalMonths; i++)
	{
		double balance = months[i].income - months[i].expense;
		if (balance < minBalance)
		{
			minBalance = balance;
		}
		if (balance > maxBalance)
		{
			maxBalance = balance;
		}
	}

	double range = maxBalance - minBalance;
	int step = calculateChartStep(range);

	drawChartBody(minBalance, maxBalance, step);
	printChartMonths();
}

int calculateChartStep(double maxValue)
{
	if (maxValue <= 0)
	{
		return 100;
	}

	int step = (int)(maxValue / 5.0);

	if (step == 0)
	{
		step = 1;
	}

	return step;
}

void drawChartBody(double minBalance, double maxBalance, int step)
{
	for (int level = 5; level >= 1; level--)
	{
		double value = minBalance + (level * step);
		int printValue = (int)value;
		int numDigits = 0;
		int temp = printValue;

		if (temp == 0)
		{
			numDigits = 1;
		}
		else if (temp < 0)
		{
			numDigits = 1;
			temp = -temp;
			while (temp > 0)
			{
				numDigits++;
				temp /= 10;
			}
		}
		else
		{
			while (temp > 0)
			{
				numDigits++;
				temp /= 10;
			}
		}
		for (int i = numDigits; i < 5; i++)
		{
			std::cout << " ";
		}
		std::cout << printValue << " | ";
		for (int m = 1; m <= totalMonths; m++)
		{
			double balance = months[m].income - months[m].expense;
			if (balance >= value)
			{
				std::cout << "#";
			}
			else
			{
				std::cout << " ";
			}
			std::cout << "   ";
		}
		newLine();
	}

	std::cout << "      ";
	for (int i = 0; i < totalMonths * 4; i++)
	{
		std::cout << "-";
	}
	newLine();
}

void printChartMonths()
{
	std::cout << "      ";

	for (int m = 1; m <= totalMonths; m++)
	{
		std::cout << monthNames[m][0] << monthNames[m][1] << monthNames[m][2] << " ";
	}
	newLine();
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

int myStringLength(const char* text)
{
	int length = 0;
	while (text[length] != TERMINATE_SYMBOL)
	{
		length++;
	}
	return length;
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
	char* argumentString = new char[30];
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
	char* commandWord = new char[30];
	int i = 0;
	while (fullCommand[i] != TERMINATE_SYMBOL && fullCommand[i] != ' ')
	{
		commandWord[i] = fullCommand[i];
		i++;
	}
	commandWord[i] = TERMINATE_SYMBOL;
	return commandWord;
}

void printBalanceColored(double balance)
{
	if (balance > 0)
	{
		std::cout << "\033[1;32m+";
	}
	else if (balance < 0)
	{
		std::cout << "\033[1;31m";
	}
	else
	{
		std::cout << "\033[1;33m";
	}

	printDoubleFixed(balance);

	std::cout << "\033[0m";
}
