/************************
* File: items.cpp
* Author: Benjamin R. Olson
* Date: April 23, 2014
* Title: Items Class File
* Description: This file defines
* 	the Items class
* Input: arguments to functions of this class
* Output: return values of functions of this class
*************************/

#include <vector>
#include <string>
#include <iostream>

class Items
{
	public:
		//grocery list item {name, quantity}
		struct item 
		{
			std::string name;
			int quantity;
		};
		
		Items();//initialize aisles array
		
		//mutator functions, commented with their definitions
		void addItem(int location, std::string name, int quantity);
		void deleteItem(int location, int item_id);
		 
		//accessor functions, commented with their definitions
		std::vector<item> * getAisle(int location); 
		std::string getAisleName(int location);
		
		//display functions, commented with its definition
		void displayItems();
		void displayAisleNames();
		
	private:
		//each vector is part of the grocery list
		std::vector<item> produce;	//in aisle 1
		std::vector<item> dairy_meat;	//in aisle 2
		std::vector<item> canned;		//in aisle 3
		std::vector<item> cereal;		//in aisle 4
		std::vector<item> baking;		//in aisle 5
		std::vector<item> pasta;		//in aisle 6
		std::vector<item> oils_wine;	//in aisle 7
		std::vector<item> bread_condiments;//in aisle 8
		std::vector<item> kitchenware;//in aisle 9
		std::vector<item> paper;		//in aisle 10
		//used to refer to one of the 10 vectors above...
		std::vector<item>* item_ptr;
		/*this array is used in conjuction with location paramaters above*/
		/*each index of this array is related to one of the 10 vectors above*/
		std::string items_arr[10];
		
};

Items::Items()
{
		items_arr[0] = "Fresh Produce";
		items_arr[1] = "Dairy/Meat";
		items_arr[2] = "Canned Goods";
		items_arr[3] = "Cereal/Morning";
		items_arr[4] = "Baking";
		items_arr[5] = "Pasta/Sauces/Etc.";
		items_arr[6] = "Oils/Wine";
		items_arr[7] = "Bread/Condiments";
		items_arr[8] = "Kitchenware";
		items_arr[9] = "Paper";
		item_ptr = NULL;
}

/*Pre-condition: location must be an int 0 through 9
 * 	(aisles indexes)
 *Post-condition: struct {name, quantity} added to correct
 * 	vector as indicated by location,
 * 	and does nothing if location is not 0 through 9*/
void Items::addItem(int location, std::string name, int quantity)
{
	item i = {name, quantity};
	/*
	switch(location)
	{
		case 0:
			produce.push_back(i);
			break;
		case 1:
			dairy_meat.push_back(i);
			break;
		case 2:
			canned.push_back(i);
			break;
		case 3:
			cereal.push_back(i);
			break;
		case 4:
			baking.push_back(i);
			break;
		case 5:
			pasta.push_back(i);
			break;
		case 6:
			oils_wine.push_back(i);
			break;
		case 7:
			bread_condiments.push_back(i);
			break;
		case 8:
			kitchenware.push_back(i);
			break;
		case 9:
			paper.push_back(i);
			break;
		default:
			return;
	}
	*/
	
	item_ptr = getAisle(location);
	item_ptr->push_back(i);
	
	return;
}

/*Pre-condition: location must be an int 0 through 9
 * 	(aisles indexes), and item_id must not exceed the size
 * 	of the vector indicated by location.
 *Post-condition: The item (struct) -- indicated by 
 * 	location (corresponding to a vector) and 
 * 	item_id (vector index) -- will be deleted.*/
void Items::deleteItem(int location, int item_id)
{
	item_ptr = getAisle(location);
	if(item_ptr->empty())
	{
		std::cout << "There are no items in this aisle to delete."
				<< std::endl;
		return;	
	}
	if(item_id > item_ptr->size() - 1)
	{
		std::cout << "No item with this ID exists.  Please try again."
				<< std::endl;
		return;	
	}
	item_ptr->erase(item_ptr->begin() + item_id);
}
 
//accessor functions
/*Pre-condition: location must be an int 0 through 9
 *Return: A pointer to the vector identified by location arg,
 * 	and if an incorrect location is given as an argument,
 * 	returns NULL*/
std::vector<Items::item> * Items::getAisle(int location)
{
	switch(location)
	{
		case 0:
			item_ptr = &produce;
			break;
		case 1:
			item_ptr = &dairy_meat;
			break;
		case 2:
			item_ptr = &canned;
			break;
		case 3:
			item_ptr = &cereal;
			break;
		case 4:
			item_ptr = &baking;
			break;
		case 5:
			item_ptr = &pasta;
			break;
		case 6:
			item_ptr = &oils_wine;
			break;
		case 7:
			item_ptr = &bread_condiments;
			break;
		case 8:
			item_ptr = &kitchenware;
			break;
		case 9:
			item_ptr = &paper;
			break;
		default:
			item_ptr = NULL;
	}
	return item_ptr;
} 

/*Pre-condition: location must be an int 0 through 9
 *Return: std::str name of the aisle indicated by location arg*/
std::string Items::getAisleName(int location)
{
	return items_arr[location];
}

/*Pre-condition: na
 * Post-condition: displays all the items categorized by each vector,
 * 	except for null vectors.
 * 	In other words, items for every non-empty aisle are displayed,
 * 	aisle by aisle.*/
void Items::displayItems()
{
	std::string aisleName;
	std::cout << "\nItems Listed By Aisle:\n";
	for(int x = 0; x < 10; x++)//iterate through the ten aisles
	{
		item_ptr = getAisle(x);
		aisleName = getAisleName(x);
		int y = 0;
		if(item_ptr->empty())
			continue;
		std::cout << "Aisle #" << x << ": " << aisleName << std::endl;
		for(auto i = item_ptr->begin(); i != item_ptr->end(); ++i)
		{
			std::cout << "\tItem ID: " << y 
					<< "\tItem: " << i->name 
					<< "\t\tQuantity: " << i->quantity << std::endl;
			y++;
		}
	}
}

/*Pre-conditions: na
 * Post_conditions: Aisle names displayed to user*/
void Items::displayAisleNames()
{
	for(int x = 0; x < 10; x++)
	{
		std::cout << "Aisle #" << x << ": " 
				<< items_arr[x] << std::endl;
	}
}
