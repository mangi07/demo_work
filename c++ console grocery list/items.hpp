/************************
* File: items.hpp
* Author: Benjamin R. Olson
* Date: April 23, 2014
* Title: Items Class Header
* Description: This class manages
* 	the grocery list data
* Input: arguments to functions of this class
* Output: return values of functions of this class
*************************/

#ifndef ITEMS_OLSONBE
#define ITEMS_OLSONBE

#include <vector>
#include <string>

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
		
		//mutator functions
		void addItem(int location, std::string name, int quantity);
		/*Pre-condition: location must be an int 0 through 9
		 * 	(aisles indexes)
		 *Post-condition: struct {name, quantity} added to correct
		 * 	vector as indicated by location*/
		void deleteItem(int location, int item_id);
		/*Pre-condition: location must be an int 0 through 9
		 * 	(aisles indexes), and item_id must not exceed the size
		 * 	of the vector indicated by location.
		 *Post-condition: The item (struct) -- indicated by 
		 * 	location (corresponding to a vector) and 
		 * 	item_id (vector index) -- will be deleted.*/
		 
		//accessor functions
		std::vector<item> * getAisle(int location); 
		/*Pre-condition: location must be an int 0 through 9
		 *Return: A pointer to the vector identified by location arg*/
		std::string getAisleName(int location);
		/*Pre-condition: location must be an int 0 through 9
		 *Return: std::str name of the aisle indicated by location arg*/
		
		//display functions
		void displayItems();
		/*Pre-conditions: na
		 * Post-conditions: Every non-empty aisle is displayed*/
		void displayAisleNames();
		/*Pre-conditions: na
		 * Post_conditions: Aisle names displayed to user*/
		
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

#endif
