#include <iostream>

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
* File with main program
*
*/

/* Constants */
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
const int CHART_LEVELS = 5;
const int MIN_STEP = 1;
const int SCALE_FACTOR = 10;
const int FRACTION_TWO_DIGITS = 10;
const int DECIMAL_BASE = 10;
const int FRACTION_SCALE = 100;
const double EPSILON = 0.01;

/* MonthData Structure */
struct MonthData {
	double income;
	double expense;
};

/* FinanceProfile Structure */
struct FinanceProfile {
	int totalMonths;
	MonthData* months;
	const char** monthNames;
};

/* main */
void handleCommand(FinanceProfile& financeProfile, char* commandWord, char* argumentString, bool& exitProgram);
void handleForecastCommand(FinanceProfile& financeProfile, const char* argumentString);
void handleSearchCommand(FinanceProfile& financeProfile, const char* argumentString);
void handleSortCommand(FinanceProfile& financeProfile, const char* argumentString);
int parseMonthsAhead(const char* argumentString);
bool isArgumentMissing(const char* argument, const char* message);
void printHelp();

/* setupProfile functionally */
void setupProfile(FinanceProfile& financeProfile);
bool isValidMonthCount(int months);
void initializeMonths(MonthData* monthsArray, int monthsCount);
bool requiresProfile(FinanceProfile& financeProfile, const char* commandWord);

/* addData functionally */
void addData(FinanceProfile& financeProfile);
bool isValidMonthIndex(FinanceProfile& financeProfile, int month);
void inputMonthData(FinanceProfile& financeProfile, int month);
double calculateMonthBalance(FinanceProfile& financeProfile, int month);
void printMonthResult(FinanceProfile& financeProfile, int month, double balance);
int countEnteredMonths(FinanceProfile& financeProfile);
bool isMonthAlreadyEntered(FinanceProfile& financeProfile, int month);

/* Align */
void printTextAligned(const char* text, int width);
void printDoubleAligned(double value, int width);
void printBalanceAligned(double balance, int width);
void printDoubleFixed(double value);
int countDigits(long long value);
void printFraction(int fracPart);
void splitDouble(double value, long long& intPart, int& fracPart);

/* report functionally */
void report(FinanceProfile& financeProfile);
void printReportHeader();
double printMonthReport(FinanceProfile& financeProfile, int monthIndex);
void printReportSummary(FinanceProfile& financeProfile, double totalIncome, double totalExpense);

/* searchMonth functionally */
void searchMonth(FinanceProfile& financeProfile, const char* name);
int findMonthIndex(FinanceProfile& financeProfile, const char* monthName);
void printMonthDetails(FinanceProfile& financeProfile, int monthIndex);

/* sortMonths functionally */
void sortMonths(FinanceProfile& financeProfile, const char* type);
bool isValidSortType(const char* type);
void sortOrderByType(FinanceProfile& financeProfile, int* order, const char* type);
void printTopMonths(FinanceProfile& financeProfile, int* order, const char* type);
double getMonthValue(FinanceProfile& financeProfile, int monthIndex, const char* type);

/* forecast functionally */
void forecast(FinanceProfile& financeProfile, int monthAhead);
void calculateSavings(FinanceProfile& financeProfile, double& savings, double& averageChange);
void forecastPositive(double savings, double averageChange, int monthsAhead);
void forecastNegative(FinanceProfile& financeProfile, double savings, double averageChange);

/* chart functionally */
void chart(FinanceProfile& financeProfile);
int calculateChartStep(double minBalance, double maxBalance);
void drawChartBody(FinanceProfile& financeProfile, double minBalance, double maxBalance);
void printChartMonths(FinanceProfile& financeProfile);
void printChartHeader();

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
bool ensureProfile(FinanceProfile& financeProfile, const char* message);
double myRound(double value, int precision);
void printSpaces(int count);
void toLowerCase(char* text);

int main() {
	const char* defaultMonthNames[MAX_MONTH_NAME] = {
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

	FinanceProfile financeProfile;
	financeProfile.months = nullptr;
	financeProfile.totalMonths = 0;
	financeProfile.monthNames = defaultMonthNames;

	char command[MAX_COMMAND_LENGTH];
	bool exitProgram = false;
	printHelp();

	while (!exitProgram) {
		std::cout << "> ";
		std::cin.getline(command, MAX_COMMAND_LENGTH);

		char* commandWord = getCommandWord(command);
		toLowerCase(commandWord);
		char* argumentString = getArgumentFromCommand(command);

		handleCommand(financeProfile, commandWord, argumentString, exitProgram);

		delete[] commandWord;
		delete[] argumentString;
	}

	delete[] financeProfile.months;
}

void printHelp() {
	std::cout << "Available Commands";
	newLine();
	std::cout << "-------------------------------------------------------------";
	newLine();
	std::cout << "> setup <month> - Create a new finance profile.";
	newLine();
	std::cout << "> add - Add income and expenses for a month.";
	newLine();
	std::cout << "> report - Show report for all months.";
	newLine();
	std::cout << "> search <month> - Show information for selected month.";
	newLine();
	std::cout << "> sort <type> - Sort by income, expense or balance.";
	newLine();
	std::cout << "> forecast <monthsAhead> - Financial forecast for m months.";
	newLine();
	std::cout << "> chart - Show graphical chart";
	newLine();
	std::cout << "> exit - Exit the program.";
	newLine();
	std::cout << "> help - Show list of commands.";
	newLine();
	std::cout << "-------------------------------------------------------------";
	newLine();
}

void handleCommand(FinanceProfile& financeProfile, char* commandWord, char* argumentString, bool& exitProgram) {
	if (myStringCompare(commandWord, "setup") == 0) {
		setupProfile(financeProfile);
		return;
	}
	if (myStringCompare(commandWord, "exit") == 0) {
		if (financeProfile.months != nullptr) {
			report(financeProfile);
		}
		exitProgram = true;
		return;
	}

	if (requiresProfile(financeProfile, commandWord)) {
		return;
	}

	if (myStringCompare(commandWord, "add") == 0) {
		addData(financeProfile);
	}
	else if (myStringCompare(commandWord, "report") == 0) {
		report(financeProfile);
	}
	else if (myStringCompare(commandWord, "search") == 0) {
		handleSearchCommand(financeProfile, argumentString);
	}
	else if (myStringCompare(commandWord, "sort") == 0) {
		handleSortCommand(financeProfile, argumentString);
	}
	else if (myStringCompare(commandWord, "forecast") == 0) {
		handleForecastCommand(financeProfile, argumentString);
	}
	else if (myStringCompare(commandWord, "chart") == 0) {
		chart(financeProfile);
	}
	else if (myStringCompare(commandWord, "help") == 0) {
		printHelp();
	}
	else {
		std::cout << "Invalid command.";
		newLine();
	}
}

bool requiresProfile(FinanceProfile& financeProfile, const char* commandWord) {
	bool needsProfile =
		myStringCompare(commandWord, "add") == 0 ||
		myStringCompare(commandWord, "report") == 0 ||
		myStringCompare(commandWord, "search") == 0 ||
		myStringCompare(commandWord, "sort") == 0 ||
		myStringCompare(commandWord, "forecast") == 0 ||
		myStringCompare(commandWord, "chart") == 0;

	if (needsProfile && financeProfile.months == nullptr) {
		std::cout << "Profile not set. Setup first.";
		newLine();
		return true;
	}

	return false;
}

int parseMonthsAhead(const char* argumentString) {
	int monthAhead = 0;
	int i = 0;

	while (argumentString[i] != TERMINATE_SYMBOL) {
		monthAhead = monthAhead * DECIMAL_BASE + (argumentString[i] - '0');
		i++;
	}

	return monthAhead;
}

void handleForecastCommand(FinanceProfile& financeProfile, const char* argumentString) {
	if (isArgumentMissing(argumentString, "Months missing.")) {
		return;
	}
	else {
		int monthAhead = parseMonthsAhead(argumentString);

		if (monthAhead <= 0) {
			std::cout << "Invalid months.";
			newLine();
		}
		else {
			forecast(financeProfile, monthAhead);
		}
	}
}
void handleSearchCommand(FinanceProfile& financeProfile, const char* argumentString) {
	if (isArgumentMissing(argumentString, "Months missing.")) {
		return;
	}
	else {
		searchMonth(financeProfile, argumentString);
	}
}

void handleSortCommand(FinanceProfile& financeProfile, const char* argumentString)
{
	if (isArgumentMissing(argumentString, "Sort type missing.")) {
		return;
	}
	else {
		sortMonths(financeProfile, argumentString);
	}
}

bool isArgumentMissing(const char* argument, const char* message) {
	if (argument[0] == TERMINATE_SYMBOL) {
		std::cout << message;
		newLine();
		return true;
	}
	return false;
}

void setupProfile(FinanceProfile& financeProfile) {
	std::cout << "Enter number of months: ";
	std::cin >> financeProfile.totalMonths;

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Enter a number.";
		newLine();

		financeProfile.totalMonths = 0;
		return;
	}

	if (!isValidMonthCount(financeProfile.totalMonths)) {
		std::cout << "Invalid months!";
		newLine();

		financeProfile.totalMonths = 0;
		return;
	}

	delete[] financeProfile.months;
	financeProfile.months = new MonthData[financeProfile.totalMonths + 1];

	initializeMonths(financeProfile.months, financeProfile.totalMonths);

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Profile created successfully.";
	newLine();
}

void initializeMonths(MonthData* monthsArray, int monthsCount) {
	for (int i = 1; i <= monthsCount; i++) {
		monthsArray[i].income = 0;
		monthsArray[i].expense = 0;
	}
}

bool isValidMonthCount(int months) {
	return months > 0 && months <= MAX_MONTHS_IN_YEAR;
}

int countEnteredMonths(FinanceProfile& financeProfile) {
	int count = 0;

	for (int i = 1; i <= financeProfile.totalMonths; i++) {
		if (financeProfile.months[i].income != 0 || financeProfile.months[i].expense != 0) {
			count++;
		}
	}
	return count;
}

bool isMonthAlreadyEntered(FinanceProfile& financeProfile, int month) {
	return financeProfile.months[month].income != 0 ||
		financeProfile.months[month].expense != 0;
}

void addData(FinanceProfile& financeProfile) {
	if (!ensureProfile(financeProfile, "Profile not set.")) {
		return;
	}

	int month = 0;

	std::cout << "Enter month (1-" << financeProfile.totalMonths << "): ";
	std::cin >> month;

	if (!isValidMonthIndex(financeProfile, month)) {
		std::cout << "Invalid month!";
		newLine();

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}

	if (isMonthAlreadyEntered(financeProfile, month)) {
		std::cout << "Data for this month is already entered.";
		newLine();

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}

	inputMonthData(financeProfile, month);

	double balance = calculateMonthBalance(financeProfile, month);
	printMonthResult(financeProfile, month, balance);

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool isValidMonthIndex(FinanceProfile& financeProfile, int month) {
	return month >= 1 && month <= financeProfile.totalMonths;
}

void inputMonthData(FinanceProfile& financeProfile, int month) {
	do {
		std::cout << "Enter income: ";
		std::cin >> financeProfile.months[month].income;

		std::cout << "Enter expense: ";
		std::cin >> financeProfile.months[month].expense;

		if (financeProfile.months[month].income < 0
			|| financeProfile.months[month].expense < 0) {
			std::cout << "Income and expense must be positive or zero.";
			newLine();
		}
	} while (financeProfile.months[month].income < 0 || financeProfile.months[month].expense < 0);
}

double calculateMonthBalance(FinanceProfile& financeProfile, int month) {
	return financeProfile.months[month].income - financeProfile.months[month].expense;
}

void printMonthResult(FinanceProfile& financeProfile, int month, double balance) {
	std::cout << "Result: Balance for " << financeProfile.monthNames[month] << ": ";
	printBalanceColored(balance);
	newLine();
}

void report(FinanceProfile& financeProfile) {
	if (!ensureProfile(financeProfile, "No profile to report.")) {
		return;
	}

	double totalIncome = 0;
	double totalExpense = 0;

	printReportHeader();

	for (int i = 1; i <= financeProfile.totalMonths; i++) {
		if (financeProfile.months[i].income != 0 || financeProfile.months[i].expense != 0) {
			printMonthReport(financeProfile, i);
			totalIncome += financeProfile.months[i].income;
			totalExpense += financeProfile.months[i].expense;
		}
	}

	printReportSummary(financeProfile, totalIncome, totalExpense);
}

int countDigits(long long value)
{
	if (value == 0) {
		return 1;
	}

	int count = 0;
	long long temp = value;

	if (temp < 0) {
		temp = -temp;
	}

	while (temp != 0) {
		count++;
		temp /= DECIMAL_BASE;
	}

	return count;
}

void splitDouble(double originalValue, long long& wholePart, int& fractionalPart) {
	wholePart = (long long)originalValue;
	fractionalPart = (int)((originalValue - wholePart) * FRACTION_SCALE + 0.5);

	if (fractionalPart < 0) {
		fractionalPart = -fractionalPart;
	}
}

void printFraction(int fractionalPart) {
	if (fractionalPart < FRACTION_TWO_DIGITS) {
		std::cout << "0";
	}
	std::cout << fractionalPart;
}

void printTextAligned(const char* text, int width) {
	int length = myStringLength(text);
	std::cout << text;

	printSpaces(width - length);
}

void printDoubleFixed(double value) {
	long long wholePart;
	int fractionalPart;

	splitDouble(value, wholePart, fractionalPart);

	std::cout << wholePart << ".";
	printFraction(fractionalPart);
}

void printDoubleAligned(double value, int width) {
	long long wholePart;
	int fractionalPart;

	splitDouble(value, wholePart, fractionalPart);

	int length = countDigits(wholePart) + POINT_AND_TWO_SYMBOLS;

	printSpaces(width - length);
	std::cout << wholePart << ".";
	printFraction(fractionalPart);
}

void printBalanceAligned(double balance, int width) {
	long long intPart;
	int fracPart;

	splitDouble(balance, intPart, fracPart);

	int length = countDigits(intPart) + POINT_AND_TWO_SYMBOLS;

	if (balance >= 0) {
		length++;
	}

	int spaces = width - length;
	if (balance > 0) {
		spaces++;
	}

	printSpaces(spaces);
	printBalanceColored(balance);
}

void printHorizontalLine() {
	for (int i = 0; i < TOTAL_WIDTH; i++) {
		std::cout << "-";
	}
	newLine();
}

void printReportHeader() {
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

double printMonthReport(FinanceProfile& financeProfile, int monthIndex) {
	double balance = financeProfile.months[monthIndex].income - financeProfile.months[monthIndex].expense;

	printTextAligned(financeProfile.monthNames[monthIndex], COL_MONTH);
	std::cout << " | ";

	printDoubleAligned(financeProfile.months[monthIndex].income, COL_INCOME);
	std::cout << " | ";

	printDoubleAligned(financeProfile.months[monthIndex].expense, COL_EXPENSE);
	std::cout << " | ";

	printBalanceAligned(balance, COL_BALANCE);

	newLine();
	return balance;
}

void printReportSummary(FinanceProfile& financeProfile, double totalIncome, double totalExpense) {
	printHorizontalLine();

	int enteredMonths = countEnteredMonths(financeProfile);

	double average = 0;
	if (enteredMonths > 0) {
		average = (totalIncome - totalExpense) / enteredMonths;
		average = myRound(average, 2);
	}

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

void searchMonth(FinanceProfile& financeProfile, const char* name) {
	if (!ensureProfile(financeProfile, "Profile not set.")) {
		return;
	}

	if (isArgumentMissing(name, "Month name missing.")) {
		return;
	}

	int index = findMonthIndex(financeProfile, name);

	if (index == -1)
	{
		std::cout << "Month not found.";
		newLine();
		return;
	}

	printMonthDetails(financeProfile, index);
}

int findMonthIndex(FinanceProfile& financeProfile, const char* monthName) {
	for (int i = 1; i <= financeProfile.totalMonths; i++) {
		if (myStringCompare(monthName, financeProfile.monthNames[i]) == 0) {
			return i;
		}
	}
	return -1;
}

void printMonthDetails(FinanceProfile& financeProfile, int monthIndex) {
	double income = financeProfile.months[monthIndex].income;
	double expense = financeProfile.months[monthIndex].expense;
	double balance = income - expense;

	std::cout << "Income: " << income;
	newLine();

	std::cout << "Expense: " << expense;
	newLine();

	std::cout << "Balance: ";
	printBalanceColored(balance);
	newLine();

	if (income > 0) {
		double ratio = (expense * PERCENT) / income;
		ratio = myRound(ratio, 1);
		std::cout << "Expense ratio: " << ratio << "%";
		newLine();
	}
	else {
		std::cout << "Expense ratio: no income.";
		newLine();
	}
}

void sortMonths(FinanceProfile& financeProfile, const char* type) {
	if (!isValidSortType(type)) {
		std::cout << "Invalid sort type.";
		newLine();
		return;
	}

	int* order = new int[financeProfile.totalMonths + 1];
	for (int i = 1; i <= financeProfile.totalMonths; i++) {
		order[i] = i;
	}

	sortOrderByType(financeProfile, order, type);
	printTopMonths(financeProfile, order, type);

	delete[] order;
}

bool isValidSortType(const char* type) {
	return myStringCompare(type, "income") == 0 ||
		myStringCompare(type, "expense") == 0 ||
		myStringCompare(type, "balance") == 0;
}

void sortOrderByType(FinanceProfile& financeProfile, int* order, const char* type) {
	for (int i = 1; i <= financeProfile.totalMonths; i++) {
		for (int j = 1; j < financeProfile.totalMonths; j++) {
			double firstValue = getMonthValue(financeProfile, order[j], type);
			double secondValue = getMonthValue(financeProfile, order[j + 1], type);

			if (firstValue < secondValue) {
				mySwap(order[j], order[j + 1]);
			}
		}
	}
}

void printTopMonths(FinanceProfile& financeProfile, int* order, const char* type) {
	std::cout << "Sorted by monthly " << type << " (descending):";
	newLine();

	for (int k = 1; k <= MAX_K_LENGTH && k <= financeProfile.totalMonths; k++) {
		int monthIndex = order[k];
		std::cout << k << ". " << financeProfile.monthNames[monthIndex] << ": ";

		double value = getMonthValue(financeProfile, monthIndex, type);

		if (myStringCompare(type, "expense") == 0) {
			std::cout << "\033[1;31m";
			printDoubleFixed(value);
			std::cout << "\033[0m";
		}
		else {
			printBalanceColored(value);
		}
		newLine();
	}
}

double getMonthValue(FinanceProfile& financeProfile, int monthIndex, const char* type)
{
	if (myStringCompare(type, "income") == 0) {
		return financeProfile.months[monthIndex].income;
	}
	else if (myStringCompare(type, "expense") == 0) {
		return financeProfile.months[monthIndex].expense;
	}
	else if (myStringCompare(type, "balance") == 0) {
		return financeProfile.months[monthIndex].income - financeProfile.months[monthIndex].expense;
	}
	return 0;
}

void forecast(FinanceProfile& financeProfile, int monthAhead) {
	if (!ensureProfile(financeProfile, "Profile not set.")) {
		return;
	}

	double savings = 0;
	double averageChange = 0;

	calculateSavings(financeProfile, savings, averageChange);

	std::cout << "Current savings: ";
	printBalanceColored(savings);
	newLine();

	std::cout << "Average monthly change: ";
	printBalanceColored(averageChange);
	newLine();

	if (averageChange >= 0) {
		forecastPositive(savings, averageChange, monthAhead);
	}
	else {
		forecastNegative(financeProfile, savings, averageChange);
	}
}
void calculateSavings(FinanceProfile& financeProfile, double& savings, double& averageChange)
{
	double totalIncome = 0;
	double totalExpense = 0;

	for (int i = 1; i <= financeProfile.totalMonths; i++) {
		totalIncome += financeProfile.months[i].income;
		totalExpense += financeProfile.months[i].expense;
	}

	savings = totalIncome - totalExpense;
	int enteredMonths = countEnteredMonths(financeProfile);

	if (enteredMonths > 0) {
		averageChange = savings / enteredMonths;
	}
	else {
		averageChange = 0;
	}
}

void forecastPositive(double savings, double averageChange, int monthsAhead) {
	double futureSavings = savings + averageChange * monthsAhead;

	std::cout << "Predicted savings after " << monthsAhead << " months: ";
	printBalanceColored(futureSavings);
	newLine();
}

void forecastNegative(FinanceProfile& financeProfile, double savings, double averageChange) {
	double remainingSavings = savings;
	int month = 0;

	while (remainingSavings > EPSILON) {
		remainingSavings += averageChange;
		month++;
	}

	std::cout << "Expected to run out of money after " << month << " months.";
	newLine();
}

void chart(FinanceProfile& financeProfile) {
	if (!ensureProfile(financeProfile, "Profile not set.")) {
		return;
	}

	if (financeProfile.totalMonths == 0) {
		std::cout << "No data.";
		newLine();
		return;
	}

	printChartHeader();

	double minBalance = financeProfile.months[1].income - financeProfile.months[1].expense;
	double maxBalance = minBalance;

	for (int i = 2; i <= financeProfile.totalMonths; i++) {
		double balance = financeProfile.months[i].income - financeProfile.months[i].expense;

		if (balance < minBalance) {
			minBalance = balance;
		}
		if (balance > maxBalance) {
			maxBalance = balance;
		}
	}

	int step = calculateChartStep(minBalance, maxBalance);

	drawChartBody(financeProfile, minBalance, maxBalance);
	printChartMonths(financeProfile);
}

void printChartHeader() {
	std::cout << "=== YEARLY FINANCIAL CHART ===";
	newLine();
}

int calculateChartStep(double minBalance, double maxBalance) {
	double range = maxBalance - minBalance;

	if (range <= 0) {
		return MIN_STEP;
	}

	double rawStep = range / CHART_LEVELS;

	int scale = 1;
	while (rawStep / scale > SCALE_FACTOR) {
		scale *= SCALE_FACTOR;
	}

	int step = (int)((rawStep + scale - 1) / scale) * scale;

	return step;
}

void drawChartBody(FinanceProfile& financeProfile, double minBalance, double maxBalance) {
	int step = calculateChartStep(minBalance, maxBalance);

	for (double level = maxBalance; level >= minBalance; level -= step) {
		int printValue = (int)level;
		std::cout.width(5);
		std::cout << printValue << " | ";

		for (int m = 1; m <= financeProfile.totalMonths; m++) {
			double balance = financeProfile.months[m].income - financeProfile.months[m].expense;
			if (balance >= level) {
				std::cout << "# ";
			}
			else {
				std::cout << "  ";
			}
		}
		newLine();
	}

	std::cout << "      ";
	for (int m = 1; m <= financeProfile.totalMonths; m++) {
		std::cout << "--";
	}
	newLine();
}

void printChartMonths(FinanceProfile& financeProfile) {
	std::cout << "      ";

	for (int m = 1; m <= financeProfile.totalMonths; m++) {
		std::cout << financeProfile.monthNames[m][0]
			<< financeProfile.monthNames[m][1]
			<< financeProfile.monthNames[m][2]
			<< " ";
	}
	newLine();
}
int myStringCompare(const char* firstString, const char* secondString) {
	int i = 0;
	while (firstString[i] != TERMINATE_SYMBOL && secondString[i] != TERMINATE_SYMBOL) {
		if (firstString[i] < secondString[i]) {
			return -1;
		}
		if (firstString[i] > secondString[i]) {
			return 1;
		}
		i++;
	}
	if (firstString[i] == TERMINATE_SYMBOL && secondString[i] == TERMINATE_SYMBOL) {
		return 0;
	}
	if (firstString[i] == TERMINATE_SYMBOL) {
		return -1;
	}
	return 1;
}

void mySwap(int& firstValue, int& secondValue) {
	if (&firstValue == &secondValue) {
		return;
	}

	int tempValue = firstValue;
	firstValue = secondValue;
	secondValue = tempValue;
}

double myAbs(double value) {
	if (value < 0) {
		return -value;
	}
	return value;
}

void newLine() {
	std::cout << std::endl;
}

int myStringLength(const char* text) {
	int length = 0;
	while (text[length] != TERMINATE_SYMBOL) {
		length++;
	}
	return length;
}

void myStringConcat(char* sourceString, char* destinationString) {
	while (*destinationString != TERMINATE_SYMBOL) {
		destinationString++;
	}
	while (*sourceString != TERMINATE_SYMBOL) {
		*destinationString = *sourceString;
		sourceString++;
		destinationString++;
	}
	*destinationString = TERMINATE_SYMBOL;
}

char* getArgumentFromCommand(const char* fullCommand) {
	char* argumentString = new char[MAX_COMMAND_LENGTH];
	argumentString[0] = TERMINATE_SYMBOL;
	int currentIndex = 0;
	while (fullCommand[currentIndex] != TERMINATE_SYMBOL && fullCommand[currentIndex] != ' ') {
		currentIndex++;
	}
	while (fullCommand[currentIndex] == ' ') {
		currentIndex++;
	}
	myStringConcat((char*)(fullCommand + currentIndex), argumentString);
	return argumentString;
}

char* getCommandWord(const char* fullCommand) {
	char* commandWord = new char[30];
	int currentIndex = 0;
	while (fullCommand[currentIndex] != TERMINATE_SYMBOL && fullCommand[currentIndex] != ' ') {
		commandWord[currentIndex] = fullCommand[currentIndex];
		currentIndex++;
	}
	commandWord[currentIndex] = TERMINATE_SYMBOL;
	return commandWord;
}

void printBalanceColored(double balance) {
	if (balance > 0) {
		std::cout << "\033[1;32m+";
	}
	else if (balance < 0) {
		std::cout << "\033[1;31m";
	}
	else {
		std::cout << "\033[1;33m";
	}

	printDoubleFixed(balance);

	std::cout << "\033[0m";
}

bool ensureProfile(FinanceProfile& financeProfile, const char* message) {
	if (financeProfile.months == nullptr) {
		std::cout << message;
		newLine();
		return false;
	}
	return true;
}

double myRound(double value, int precision) {
	double factor = 1.0;
	for (int i = 0; i < precision; i++) {
		factor *= 10.0;
	}

	if (value >= 0) {
		return (long long)(value * factor + 0.5) / factor;
	}
	else {
		return (long long)(value * factor - 0.5) / factor;
	}
}

void printSpaces(int count) {
	for (int i = 0; i < count; i++) {
		std::cout << ' ';
	}
}

void toLowerCase(char* text) {
	int charIndex = 0;
	while (text[charIndex] != TERMINATE_SYMBOL) {
		if (text[charIndex] >= 'A' && text[charIndex] <= 'Z') {
			text[charIndex] = text[charIndex] - 'A' + 'a';
		}
		charIndex++;
	}
}