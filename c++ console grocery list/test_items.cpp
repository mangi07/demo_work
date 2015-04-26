/************************
* File: test_items.cpp
* Author: Benjamin R. Olson
* Date: April 23, 2014
* Title: Items Class Test File
* Description: Tests all functions,
* 	including default constructor, in items.cpp
* Input: Hard-coded values
* Output: cout object files and return values 
* 	of functions of this class
*************************/

#include "items.hpp"
#include <iostream>
#include <string>

int main()
{
	Items i;
	
	/*Function #1: 
	 * std::vector<Items::item> * Items::getAisle(int location)*/
	std::cout << "\tFunction 1" << std::endl;
	//1. Positive Case
	std::cout << "i.getAisle(5): " << i.getAisle(5) << std::endl;
	//1. Negative Case
	std::cout << "i.getAisle(-1): " << i.getAisle(-1) << std::endl;
	//1. Boundary Case
	std::cout << "i.getAisle(0): " << i.getAisle(0) << std::endl;
	//1. Boundary Case
	std::cout << "i.getAisle(9): " << i.getAisle(9) << std::endl;
	//1. Negative Case
	std::cout << "i.getAisle(10): " << i.getAisle(10) << std::endl;
	
	/*Function #2: 
	 * std::string Items::getAisleName(int location)*/
	std::cout << "\tFunction 2" << std::endl;
	//1. Positive Case
	std::cout << "i.getAisleName(5): " << i.getAisleName(5) << std::endl;
	//2. Negative Case
	//std::cout << "i.getAisleName(-1): " << i.getAisleName(-1) << std::endl;
	//3. Boundary Case
	std::cout << "i.getAisleName(0): " << i.getAisleName(0) << std::endl;
	//4. Boundary Case
	std::cout << "i.getAisleName(9): " << i.getAisleName(9) << std::endl;
	//5. Negative Case
	//std::cout << "i.getAisleName(10): " << i.getAisleName(10) << std::endl;
	
	/*Function #3:
	 * void Items::addItem(int location, std::string name, int quantity)*/
	 std::cout << "\tFunction 3" << std::endl;
	 //1. Positive Case
	 i.addItem(5, "noodles", 2);
	 std::cout << "(*i.getAisle(5)).at(0).name: " 
	 		<< (*i.getAisle(5)).at(0).name << std::endl;
	 std::cout << "(*i.getAisle(5)).at(0).quantity: " 
	 		<< (*i.getAisle(5)).at(0).quantity << std::endl;
	 //2. Negative Case
	 i.addItem(-1, "reject", 3);
	 //3. Boundary Case
	 i.addItem(0, "bananas", 12);
	 std::cout << "(*i.getAisle(0)).at(0).name: " 
	 		<< (*i.getAisle(0)).at(0).name << std::endl;
	 std::cout << "(*i.getAisle(0)).at(0).quantity: " 
	 		<< (*i.getAisle(0)).at(0).quantity << std::endl;
	 //4. Boundary Case
	 i.addItem(9, "toilet paper", 6);
	 std::cout << "(*i.getAisle(9)).at(0).name: " 
	 		<< (*i.getAisle(9)).at(0).name << std::endl;
	 std::cout << "(*i.getAisle(9)).at(0).quantity: " 
	 		<< (*i.getAisle(9)).at(0).quantity << std::endl;
	 //5. Negative Case
	 i.addItem(10, "reject2", 3);
	 
	/*Function #4:
	 * void Items::deleteItem(int location, int item_id)*/
	 std::cout << "\tFunction 4" << std::endl;
	 //1. Positive Case
	 /*
	 i.deleteItem(5, 0);
	 std::cout << "(*i.getAisle(5)).at(0).name: " 
	 		<< (*i.getAisle(5)).at(0).name << std::endl;
	 std::cout << "(*i.getAisle(5)).at(0).quantity: " 
	 		<< (*i.getAisle(5)).at(0).quantity << std::endl;
	 */
	 //2. Negative Case
	 //i.deleteItem(-1, 0);
	 //3. Boundary Case
	 i.deleteItem(0, 0);
	 /*
	 std::cout << "(*i.getAisle(0)).at(0).name: " 
	 		<< (*i.getAisle(0)).at(0).name << std::endl;
	 std::cout << "(*i.getAisle(0)).at(0).quantity: " 
	 		<< (*i.getAisle(0)).at(0).quantity << std::endl;
	 */
	 //4. Boundary Case
	 
	 i.deleteItem(9, 0);
	 /*
	 std::cout << "(*i.getAisle(9)).at(0).name: " 
	 		<< (*i.getAisle(9)).at(0).name << std::endl;
	 std::cout << "(*i.getAisle(9)).at(0).quantity: " 
	 		<< (*i.getAisle(9)).at(0).quantity << std::endl;
	 */
	 //5. Negative Case
	 //i.deleteItem(10, 0);
	 
	return 0;
}
