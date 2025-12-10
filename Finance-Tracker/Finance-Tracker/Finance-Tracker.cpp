#include <iostream>
int const MAX_COMMAND_LENGTH = 30;
char const TERMINATE_SYMBOL = '\0';
int myStringCompare(const char* a, const char* b);

int main()
{
    char command[MAX_COMMAND_LENGTH];
    while (true) {
        std::cout << "> ";
        std::cin.getline(command, MAX_COMMAND_LENGTH);
        if (myStringCompare(command, "setup") == 0)
        {
			//TODO: Implement setup functionality
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
