/************************
* File: test1.cpp
* Author: Benjamin R. Olson
* Date: April 11, 2014
* Title: Project 1, Implement Conway's Game of Life
* Description: Test file used during implementation
* Input: none
* Output: test results
*************************/

#include <iostream>

int main()
{
	int len = 15;
	char arr[] = {'*', '*', '*', '*', '*', 
				  '*', '*', '*', '0', '1', 
				  '*', '*', '*', '3', 'x'};
	for (int x = 0, y = 0; x < len; x++, y++)
	{
		if (y==5)
		{
			std:: cout << '|' << std::endl;
			y = 0;
		}
		std::cout << arr[x];
	}
	std::cout << '|' << std::endl;
	
	//work the following into live(x): returns true if x should live next gen, else false
	//get values of neighbor cells for given cell x
	char neighbors[8];//left to right, top to bottom, maybe not necessary
	bool live;
	int liveNeighbors;
	int width = 5;
	int x = 14;
	{
		//out of bounds "ghost" cells considered dead
		
		if (x == 0)//upper-left corner
		{
			std::cout << "upper-left corner" << std::endl;
			for (int y = 0; y < 4; y++)//not necessary
				neighbors[y] = ' ';//not necessary
			neighbors[4] = arr[x+1];
			neighbors[5] = ' ';
			neighbors[6] = arr[width];
			neighbors[7] = arr[width + 1];
		}
		else if (x==(width-1))//upper-right corner
		{
			std::cout << "upper-right corner" << std::endl;
			for (int y = 0; y < 3; y++)//not necessary
				neighbors[y] = ' ';//not necessary
			neighbors[3] = arr[x-1];
			neighbors[4] = ' ';//not necessary
			neighbors[5] = arr[x + width - 1];//x
			neighbors[6] = arr[x + width];//*
			neighbors[7] = ' ';//not necessary
		}
		else if (x==(len-width))//lower-left corner
		{
			std::cout << "lower-left corner" << std::endl;
			neighbors[0] = ' ';//not necessary
			neighbors[1] = arr[x-width];
			neighbors[2] = arr[x-width+1];
			neighbors[3] = ' ';
			neighbors[4] = arr[x+1];
			neighbors[5] = ' ';//not necessary
			neighbors[6] = ' ';//not necessary
			neighbors[7] = ' ';//not necessary
		}
		else if (x==(len-1))//lower-right corner
		{
			std::cout << "lower-right corner" << std::endl;
			neighbors[0] = arr[x - width - 1];
			neighbors[1] = arr[x-width];
			neighbors[2] = ' ';//not necessary
			neighbors[3] = arr[x-1];
			neighbors[4] = ' ';//not necessary
			neighbors[5] = ' ';//not necessary
			neighbors[6] = ' ';//not necessary
			neighbors[7] = ' ';//not necessary
		}
		else if (x > 0 && x < (width - 1))//top row
		{
			std::cout << "top row" << std::endl;
			for (int y = 0; y < 3; y++)//not necessary
				neighbors[y] = ' ';//not necessary
			neighbors[3] = arr[x - 1];
			neighbors[4] = arr[x + 1];
			neighbors[5] = arr[x + width - 1];
			neighbors[6] = arr[x + width];
			neighbors[7] = arr[x + width + 1];
		}
		else if (x > (len-width) && x < (len))//bottom row
		{
			std::cout << "bottom row" << std::endl;
			for (int y = 0; y < 3; y++)//flip signs and do sim. for top row
			{
				neighbors[y] = arr[x - (width+1) + y];
				//add to int live counter with conditional on each iteration
			}
			neighbors[3] = arr[x - 1];//add to int live counter with conditional
			neighbors[4] = arr[x + 1];//add to int live counter with conditional
		}
		else//inner cells (not edge cells)
		{
			std::cout << "inner cell" << std::endl;
			//conditional ran on 8 surrounding cells to determine how many are live	
			for (int y = 0; y < 3; y++)//flip signs and do sim. for top row
			{
				neighbors[y] = arr[x - (width+1) + y];
				//add to int live counter with conditional on each iteration
			}
			neighbors[3] = arr[x - 1];//add to int live counter with conditional
			neighbors[4] = arr[x + 1];//add to int live counter with conditional
			for (int y = 5; y < 8; y++)//flip signs and do sim. for top row
			{
				neighbors[y] = arr[x + (width-1) + y];
				//add to int live counter with conditional on each iteration
			}
		}
	}
	for (int y = 0; y < 8; y++)
		std::cout << "neighbors[y]: " << neighbors[y] << std::endl;
	
	return 0;
}
