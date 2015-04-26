/************************
* File: test_input.cpp
* Author: Benjamin R. Olson
* Date: April 23, 2014
* Title: Input Constrants Test File
* Description: Test user input filtering
* Input: Mixture of hard-coded values and 
* 	user input
* Output: relevant pre-conditions,
* 	return values of functions tested,
* 	and relevant post-conditions
*************************/

#include "items.hpp"
#include <iostream>
#include <string>

/*Input Constraints*/
bool isValidItemName(std::string input, int max_chars);
/* Pre-Condition: must be no longer than max_chars
 * Return: True if arg input is <= max_chars, otherwise false*/
bool isIntInRange(std::string input, int & i, int min, int max, int max_digits);
/* Pre-Condition: must be an integer within range
 * Post-Condition: returns true and assigns input (as int) to arg i
 * if arg input is an integer 1 through 10,
 * otherwise returns false and does not assign input (as int) to arg i*/

int main()
{
	std::string input;
	int x;
	int min = 1;
	int max = 1000;
	int max_digits = 4;
	int max_chars = 20;
	while (true)
	{
		std::cout << "Enter input: ";
		std::getline(std::cin, input);
		/*
		std::cout << "x: " << x << std::endl;
		std::cout << "isIntInRange(input, x, min, max, max_digits): "
				<< isIntInRange(input, x, min, max, max_digits) 
				<< std::endl;
		std::cout << "x: " << x << std::endl;
		*/
		std::cout << "isValidItemName(input, max_chars): "
				<< isValidItemName(input, max_chars)
				<< std::endl;
	}
	
	
	return 0;	
}

/* Pre-Condition: must be an integer within range
 * Post-Condition: returns true and assigns input (as int) to arg i
 * if arg input is an integer 1 through 10,
 * otherwise returns false and does not assign input (as int) to arg i*/ 
bool isIntInRange(std::string input, int & i, int min, int max, int max_digits)
{
	if(input.length() < 1 || input.length() > max_digits)
		return false;
	for(unsigned int x = 0; x < input.length(); x++)
	{
		if(!isdigit(input.at(x)))
			return false;
	}
	int temp = std::atoi(input.c_str());
	if(temp < min || temp > max)
		return false;
	i = temp;
	return true;
}

/* Pre-Condition: na
 * Return: True if arg input is between 1 and max_chars long, inclusive,
 * 	otherwise returns false*/
bool isValidItemName(std::string input, int max_chars)
{
	return (input.length() <= max_chars && input.length() > 0);
}
