/**
*
* Solution to course project #1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Katerina Aleksandrova Dimitrova
* @idnumber 8MI0600563
* @compiler GCC
*
* Utility helper functions
*
*/
#include <iostream>

extern char const TERMINATE_SYMBOL = '\0';

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