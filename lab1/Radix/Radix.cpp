#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 

using namespace std;

int StringToInt(const string& str, int radix, bool& wasError) 
{
	try 
	{
		int result = stoi(str, nullptr, radix);
		return result;
	}
	catch (out_of_range & err) 
	{
		cout << err.what() << endl;
		wasError = true;
		return 0;
	}
}

string IntToString(int n, int radix) {
	string result = "";
	string negativeSwitch = "";
	if (n < 0) 
	{
		negativeSwitch = "-";
		n = abs(n);
	}
	while (n > 0) 
	{
		if (n % radix > 9) 
		{
			result = (char)((n % radix) + 'A' - 10) + result;
		}
		else 
		{
			result = (char)((n % radix) + '0') + result;
		}
		n = n / radix;
	}
	if (result == "")
	{
		result = "0";
	}
	result = negativeSwitch + result;
	return result;
}

int ConvertNotation(const string& str)
{
	if (all_of(str.begin(), str.end(), ::isdigit)) 
	{
		int result = stoi(str);
		if ((result >= 2) && (result <= 36)) 
		{
			return result;
		}
		else 
		{
			return -1;
		}
	}
	else 
	{
		return -1;
	}
}

bool CheckValue(int& arg1, int& arg2, string& arg3) 
{
	if (arg1 != -1 && arg2 != -1) 
	{
		string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		int negativeSwitch = 0;
		if (arg3[0] == '-') 
		{
			negativeSwitch = 1;
		}
		if (arg3.substr(negativeSwitch, arg3.size()).find_first_not_of(alphabet.substr(0, arg1)) == string::npos) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

int GetInt(string& source, string& destination, string& value, bool& wasError, int& destinationInt)
{
	int sourceInt = ConvertNotation(source);
	destinationInt = ConvertNotation(destination);
	if (sourceInt != -1 && destinationInt != -1)
	{
		if (CheckValue(sourceInt, destinationInt, value))
		{
			int decimal = StringToInt(value, sourceInt, wasError);
			if (!wasError) 
			{
				return decimal;
			}
			else 
			{
				wasError = true;
				return 0;
			}
		}
		else 
		{
			cout << "Error in 3rd argument: Check your input" << endl;
			wasError = true;
			return 0;
		}
	}
	else 
	{
		cout << "Error in 1st or 2nd argument: Check your input" << endl;
		wasError = true;
		return 0;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	string source = argv[1];
	string destination = argv[2]; 
	string value = argv[3];

	int destinationInt = 0;
	bool err = false;
	int decimal = GetInt(source, destination, value, err, destinationInt);
	if (err) 
	{
		return 1;
	}
	cout << IntToString(decimal, destinationInt) << endl;
	return 0;
}