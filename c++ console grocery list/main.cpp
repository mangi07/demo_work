/************************
* File: main.cpp
* Author: Benjamin R. Olson
* Date: April 24, 2014
* Title: Grocery List
* Description: Program Driver
* Input: User input from getline(cin, input)
* Output: Information to the user about the grocery list
*************************/

#include "items.hpp"
#include <iostream>
#include <string>

/*Input Constraints, commented with their definitions*/
bool isIntInRange(std::string input, int & i, int min, int max, int max_digits);
bool isValidItemName(std::string input, int max_chars);

/*User input functions, commented with their definitions*/
void inputItemDeletion(int max_id, int & var);
void inputLocation(int & var);
void inputName(std::string & var);
void inputQuantity(int & var);

/*Main functions, commented with their definitions*/
void displayList(Items * i, int aisle);
void addToList(Items * i);
void deleteFromList(Items * i);

int main()
{
	Items shopping_list;
	int loc = -1;		//number of aisle vector
	int item_id = -1;	//index of aisle vector
	std::string name = "";//to be entered in item.name
	int quant = -1;		//to be entered in item.quantity
	std::string input;
	int choice;			//choice from main menu
	bool loop = true;
	//true: program do-while loops again, false: program ends
	
	/*
	//inputItemDeletion(10, item_id);
	//std::cout << "item_id: " << item_id << std::endl;
	//inputLocation(loc);
	//std::cout << "loc: " << loc << std::endl;
	//inputName(name);
	//std::cout << "name: " << name << std::endl;
	//inputQuantity(quant);
	//std::cout << "quant: " << quant << std::endl;
	*/

	std::cout << "\tGROCERY SHOPPING LIST" << std:: endl;
	std::cout << "Please add at least one item to the list "
			<< "before displaying it or trying to delete an item.\n";
	do
	{
		std::cout << "\nPlease choose an action (1 - 5) from this menu:"
				 << std::endl;
		std::cout << "1. Add Item\t\t2. Display Items By Aisle\n"
				<< "3. Display Aisle Names\t4. Delete An Item\n"
				<< "5. Quit\n";
		std::getline(std::cin, input);
		if(isIntInRange(input, choice, 1, 5, 1))
		{
			switch(choice)
			{
				case 1://add item
					std::cout << "Please add an item...\n";
					inputLocation(loc);
					inputName(name);
					inputQuantity(quant);
					shopping_list.addItem(loc, name, quant);
					break;
				case 2:
					shopping_list.displayItems();
					break;
				case 3:
					shopping_list.displayAisleNames();
					break;
				case 4://delete an item
					std::cout << "Please choose an aisle "
							<< "from which to delete your item: \n\n";
					inputLocation(loc);
					inputItemDeletion(100, item_id);
					shopping_list.deleteItem(loc, item_id);
					break;
				case 5://quit
					loop = false;
					break;
				default:
				//this should never be encountered, but here
				//for added safety
					std::cout << "\n\nI'm sorry.  Please try entering "
							<< "your choice again.\n\n";
			}
		}
	}
	while(loop);
	
	std::cout << "\nThank you for using the GROCERY SHOPPING LIST!\n\n";
	
	return 0;
}

/*
Highest level functions in main menu (switch within do-while loop), for user interaction:
displayList: Takes a pointer to an item object (grocery list), displays an ID#, name, and
quantity for each item struct in the item object.
addToList: uses inputLocation, inputName, inputQuantity, and object.addItem
deleteFromList: uses inputItemDeletion and object.deleteItem
*/



/*INPUT CONSTRAINTS*/

/* Pre-Condition: max_digits must be the number of digits in max
 * Post-Condition: returns true and assigns input (as int) to arg i
 * if arg input is an integer within range min to max, inclusive,
 * otherwise returns false and does not assign input (as int) to arg i*/ 
bool isIntInRange(std::string input, int & i, int min, int max, int max_digits)
{
	if(input.length() < 1 || input.length() > max_digits)
		return false;
	for(int x = 0; x < input.length(); x++)
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

/*USER INPUT FUNCTIONS*/

/* Pre-Condition: Use after an aisle has been selected, 
 * 	where max_id is obtained from the number of elements in that aisle
 * Post-Condition: valid number that user chose is assigned to var,
 * 	representing the item to delete, 
 * 	or gives user the option to retry entry if there is an error, 
 * 	not assigning to var*/
void inputItemDeletion(int max_id, int & var)
{
	std::string input;
	std::cout << "Enter an item id#, from the list, to delete: ";
	std::getline(std::cin, input);
	if(isIntInRange(input, var, 0, max_id, 7))
	{
		return;//input has been assigned to var as an int
	}
	else
	{
		std::cout << "That is not a valid id#.  "
				<< "Would you like to retry? (y/n): ";
		std::getline(std::cin, input);
		if(input == "y")
			inputItemDeletion(max_id, var);
		else
			return;
	}	
}
/* Pre-Condition: na
 * Post-Condition: valid number that user chose is assigned to var, 
 * representing the aisle, returns 0 if user opts out of retry*/
void inputLocation(int & var)
{
	std::string input;
	std::cout << "Enter the aisle number, 0 through 9: ";
	std::getline(std::cin, input);
	if(isIntInRange(input, var, 0, 9, 1))
	{
		std::cout << "\tAisle " << var 
				<< " has been chosen." << std::endl;
	}
	else
	{
		std::cout << "That is not a valid aisle#.  "
				<< "If you do not retry your entry, you will need to "
				<< "accept a default entry of '0' and delete it later\n"
				<< "Would you like to retry? (y/n): ";
		std::getline(std::cin, input);
		if(input == "y")
			inputLocation(var);
		else
			return;
	}	
}
/* Pre-Condition: na
 * Post-Condition: valid name that user chose is assigned to var, 
 * 	to be added to the shopping list.  If user opts out of retry,
 * 	then var is not assigned.*/
void inputName(std::string & var)
{
	std::string input;
	std::cout << "Enter the item name (1 to 20 characters long): ";
	std::getline(std::cin, input);
	if(isValidItemName(input, 20))
	{
		var = input;
		std::cout << "\tItem name entered: " << var << std::endl;
	}
	else
	{
		std::cout << "Name chosen is either too big or too small.\n"
				<< "If you do not retry your entry, you will need to "
				<< "accept a default entry and delete it later\n"
				<< "Would you like to retry? (y/n): ";
		std::getline(std::cin, input);
		if(input == "y")
			inputName(var);
		else
			return;
	}
}
/* Pre-Condition: na
 * Post-Condition: valid number that user chose is assigned to var, 
 * 	representing the quantity of a certain item.
 * 	If user opts out of retry, then var is not assigned*/
void inputQuantity(int & var)
{
	std::string input;
	std::cout << "Enter the item quantity (max of 1000): ";
	std::getline(std::cin, input);
	if(isIntInRange(input, var, 1, 1000, 4))
	{
		std::cout << "Quantity entered: " << var << std::endl;
	}
	else
	{
		std::cout << "Invalid quantity.  "
				<< "Would you like to retry? (y/n): ";
		std::getline(std::cin, input);
		if(input == "y")
			inputQuantity(var);
		else
			return;
	}
}





