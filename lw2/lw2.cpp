#include "stdafx.h"
#include "BigInteger.h"
#include <exception>

int main()
{
	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open input.txt\n";
		return 1;
	}

	std::ofstream outputFile("output.txt", std::ios::out);
	if (!outputFile.is_open())
	{
		std::cout << "Failed to create output.txt\n";
		return 1;
	}

	std::string leftNumber;
	char operation;
	std::string rightNumber;

	while (inputFile >> leftNumber >> operation >> rightNumber)
	{
		CBigInteger leftBigInt(leftNumber);
		CBigInteger rightBigInt(rightNumber);
		CBigInteger result;

		switch (operation)
		{
		case '+':
			result = leftBigInt + rightBigInt;
			break;
		case '-':
			result = leftBigInt - rightBigInt;
			break;
		case '*':
			result = leftBigInt * rightBigInt;
			break;
		case '/':
			try
			{
				result = leftBigInt / rightBigInt;
			}
			catch (std::logic_error e)
			{
				outputFile << e.what() << " (" << leftNumber << ' ' << operation << ' ' << rightNumber << ")\n";
				continue;
			}
			break;
		}
		outputFile << leftNumber << ' ' << operation << ' ' << rightNumber << " = " << result.toString() << '\n';
	}
    return 0;
}
