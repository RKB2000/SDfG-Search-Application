// SID: 1903490
// Date: 18/05/2020

#pragma once

#include "HelperFunctions.h"

#include <string>
#include <iostream>

using namespace std;

// Asks for an integer input between 2 limits
int IntInput(string prompt, int min = 0, int max = 10000)
{
	int input = 0;
	bool isValid = false;
	
	// While input is invalid
	while (!isValid)
	{
		// Display Prompt
		cout << prompt;

		// Ask for input
		cin >> input;

		// Check ranges
		isValid = cin && input >= min && input <= max;

		cin.clear();
		cin.ignore(10000, '\n');

		// If invalid
		if (!isValid)
		{
			// Display error prompt
			cout << "Please enter a number between " << min << " & " << max << "." << endl;
		}

		cout << endl;
	}

	// Return input
	return input;
}

string StringInput(string prompt, string errorPrompt, unsigned int minLength = 0, unsigned int maxLength = 10000, string formatWhitelist = "")
{
	string input = "";
	bool isValid = false;

	// While input is invalid
	while (!isValid)
	{
		// Display Prompt
		cout << prompt;

		// Ask for input
		cin >> input;

		// Check ranges
		isValid = cin && input.length() >= minLength && input.length() <= maxLength && Format(input, formatWhitelist);

		cin.clear();
		cin.ignore(10000, '\n');

		// If invalid
		if (!isValid)
		{
			// Display error prompt
			cout << errorPrompt << endl;
		}

		cout << endl;
	}

	// Return input
	return input;
}

bool Confirm()
{
	string input = "";
	bool isValid = false;

	// While input is invalid
	while (!isValid)
	{
		// Display Prompt
		cout << "Are you sure (Y/N)?: ";

		// Ask for input
		cin >> input;

		// Check ranges
		isValid = cin && input.length() == 1 && Format(input) && (input == "y" || input == "n");

		cin.clear();
		cin.ignore(10000, '\n');

		if (!isValid)
		{
			// Display error if invalid
			cout << "Please enter Y (yes) or N (no)." << endl;
			cout << endl;
		}
	}

	return input == "y";
}