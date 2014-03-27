#include <stdio.h>
#include <stdlib.h>
#include "bigInt.h"
#include <iostream>
#include <string.h>
using namespace std;

void noArguments();
void printUsage();
bool checkArguments(int argc, char* argv[]);
bool getFromFiles(char* fileA, char* fileB, char* fileMod, char operation, bool binary, bigInt& A, bigInt& B, bigInt& modulus);
bool process(bigInt A, bigInt B, bigInt modulus, char operation, bigInt& res);
bool saveRes(char* fileRes, bool binary, bigInt res);


int main(int argc, char* argv[])
{
	if (!checkArguments(argc, argv))
		return -1;

	char* fileA = argv[1];
	char operation = argv[2][0];
	char* fileB = argv[3];
	char* fileMod = NULL;
	char* fileRes = NULL;
	bool binary = false;

	if (operation == '^')
	{
		fileMod = argv[4];
		fileRes = argv[5];
		if (argc == 7)
			binary = true;
	}
	else
	{
		fileRes = argv[4];
		if (argc == 6)
			binary = true;
	}

	bigInt A, B, modulus;
	if (!getFromFiles(fileA, fileB, fileMod, operation, binary, A, B, modulus))
		return -1;

	bigInt res;
	if (!process(A, B, modulus, operation, res))
		return -1;

	if (!saveRes(fileRes, binary, res))
		return -1;

	return 0;
}

void noArguments()
{
	cout << "Launched without parameters." << endl;
	cout << "Perform all kind of oparations with entered numbers." << endl;
	
	bigInt a, b;
	cout << "Enter A: ";
	cin >> a;
	cout << "Enter B: ";
	cin >> b;

	cout << "A + B = " << a << " + " << b << " = " << a + b << endl;
	cout << "A - B = " << a << " - " << b << " = " << a - b << endl;
	cout << "A * B = " << a << " * " << b << " = " << a * b << endl;
	try
	{
		cout << "A / B = " << a << " / " << b << " = " << a / b << endl;
	}
	catch (int err)
	{
		if (err == DIVISION_BY_ZERO)
			cout << "Division by zero" << endl;
	}
	try
	{
		cout << "A % B = " << a << " % " << b << " = " << a % b << endl;
	}
	catch (int err)
	{
		if (err == DIVISION_BY_ZERO)
			cout << "Division by zero" << endl;
	}
	
	bigInt mod;
	cout << endl << "Enter modulus for pow: ";
	cin >> mod;
	cout << "A ^ B mod N = " << a << " ^ " << b << " mod " << mod << " = " << pow(a, b, mod) << endl;

	/*if (!a.getFromTextFile("input.txt"))
	cout << "Reading from text file failed" << endl;

	a *= b;

	if (!a.saveToBinFile("output.bin"))
	cout << "Saving to binary file failed" << endl;

	if (!a.getFromBinFile("output.bin"))
	cout << "Reading from binary file failed" << endl;

	a++;

	if (!a.saveToTextFile("output.txt"))
	cout << "Saving to text file failed" << endl;*/

	cout << "That's all. Press Enter... ";
	getchar();
	getchar();
	cout << endl;
}

void printUsage()
{
	cout << "Usage: " << endl;
	cout << "TCHMK_1 <A filelame> <operation> <B filelame> [<modulus filename>] <result filename> [-b]" << endl << endl;
	cout << "Parameters:" << endl;
	cout << "  operations:" << endl;
	cout << "    \"+\" - addition" << endl;
	cout << "    \"-\" - subtraction" << endl;
	cout << "    \"*\" - multiplication" << endl;
	cout << "    \"/\" - division" << endl;
	cout << "    \"%\" - taking the remainder" << endl;
	cout << "    \"^\" - involution (pow)" << endl;
	cout << "  -b for operations with binary files" << endl;
	cout << "  [<modulus filename>] using when operation is ^ (pow)" << endl;
}

bool checkArguments(int argc, char* argv[])
{
	if (argc < 2)
	{
		noArguments();
		return false;
	}

	if (argc > 7)
	{
		cout << "Too many arguments passed." << endl;
		printUsage();
		return false;
	}

	if ((argc > 1) && (argc < 5))
	{
		cout << "Not enough arguments passed." << endl;
		printUsage();
		return false;
	}

	if (strlen(argv[2]) > 1)
	{
		cout << "Wrong operation." << endl;
		printUsage();
		return false;
	}

	if (argv[2][0] == '^')
	{
		if (argc < 6)
		{
			cout << "Not enough arguments passed." << endl;
			printUsage();
			return false;
		}
		if (argc == 6)
		{
			if (!strcmp(argv[5], "-b"))
			{
				cout << "No modulus passed. " << endl;
				printUsage();
				return false;
			}
		}
		if (argc == 7)
		{
			if (strcmp(argv[6], "-b"))
			{
				cout << "Wrong parameter passed." << endl;
				printUsage();
				return false;
			}
		}
	}
	else
	{
		if (argc == 6)
		{
			if (strcmp(argv[5], "-b"))
			{
				cout << "Wrong parameter passed." << endl;
				printUsage();
				return false;
			}
		}
	}
	return true;
}

bool getFromFiles(char* fileA, char* fileB, char* fileMod, char operation, bool binary, bigInt& A, bigInt& B, bigInt& modulus)
{
	if (binary)
	{
		if (!A.getFromBinFile(fileA))
		{
			cout << "Can't get number from " << fileA << endl;
			return false;
		}
		if (!B.getFromBinFile(fileB))
		{
			cout << "Can't get number from " << fileB << endl;
			return false;
		}
		if (operation == '^')
		{
			if (!modulus.getFromBinFile(fileMod))
			{
				cout << "Can't get number from " << fileMod << endl;
				return false;
			}
		}
	}
	else
	{
		if (!A.getFromTextFile(fileA))
		{
			cout << "Can't get number from " << fileA << endl;
			return false;
		}
		if (!B.getFromTextFile(fileB))
		{
			cout << "Can't get number from " << fileB << endl;
			return false;
		}
		if (operation == '^')
		{
			if (!modulus.getFromTextFile(fileMod))
			{
				cout << "Can't get number from " << fileMod << endl;
				return false;
			}
		}
	}

	return true;
}

bool process(bigInt A, bigInt B, bigInt modulus, char operation, bigInt& res)
{
	switch (operation)
	{
	case '+':
		res = A + B;
		return true;
	
	case '-':
		res = A - B;
		return true;
	
	case '*':
		res = A * B;
		return true;
	
	case '/':
		if (B == (longDigit)0)
		{
			cout << "Division by zero" << endl;
			return false;
		}
		res = A / B;
		return true;
	
	case '%':
		if (B == (longDigit)0)
		{
			cout << "Division by zero" << endl;
			return false;
		}
		res = A % B;
		return true;
	
	case '^':
		res = pow(A, B, modulus);
		return true;
	
	default:
		cout << "Wrong operation." << endl;
		printUsage();
		return false;
	}
}

bool saveRes(char* fileRes, bool binary, bigInt res)
{
	if (binary)
	{
		if (!res.saveToBinFile(fileRes))
		{
			cout << "Can't save result to " << fileRes << endl;
			return false;
		}
	}
	else
	{
		if (!res.saveToTextFile(fileRes))
		{
			cout << "Can't save result to " << fileRes << endl;
			return false;
		}
	}
	return true;
}
