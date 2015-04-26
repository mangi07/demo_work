/************************
* File: test2.cpp
* Author: Benjamin R. Olson
* Date: April 11, 2014
* Title: Project 1, Implement Conway's Game of Life
* Description: Test file used during implementation
* Input: none
* Output: test results
*************************/

#include <iostream>

int countLive(int x, char* arr, int width, int len);
//returns the number of live cells surrounding given cell x

bool isLive(char c, int x);
//Returns true if given cell x should live and false if it should die

void displayGrid(char* arr, int width, int len);

int main()
{
	int len = 20;
	int width = 5;
	bool live;
	int liveNeighbors;
	int x = 10;
	
	char arr[] = {'*', '*', '*', '*', '*', 
				  ' ', ' ', '*', '*', '*', 
				  ' ', '*', '*', '*', '*',
				  '*', '*', '*', '*', '*'};
	char arr2[] = {' ', ' ', ' ', ' ', ' ', 
				   ' ', ' ', ' ', '*', ' ', 
				   ' ', ' ', ' ', '*', ' ',
				   ' ', ' ', ' ', '*', ' '};
	
	displayGrid(arr2, width, len);
	
	/*
	std::cout << "around " << x << " are " << 
		countLive(x, arr, width, len) << 
		" live cells." << std::endl;
	*/
	
	return 0;
}

void displayGrid(char* arr, int width, int len)
{
	for (int x = 0, y = 0; x < len; x++, y++)
	{
		if (y==width)
		{
			std:: cout << '|' << std::endl;
			y = 0;
		}
		std::cout << arr[x];
	}
	std::cout << '|' << std::endl;
}
	
//returns the number of live cells surrounding given cell x
int countLive(int x, char* arr, int width, int len)
{
	//out of bounds "ghost" cells considered dead
	int counter = 0;
	if (x == 0)//upper-left corner
	{
		std::cout << "upper-left corner" << std::endl;
		counter += (arr[x + 1]			== ' ')?0:1;
		counter += (arr[width]			== ' ')?0:1;
		counter += (arr[width + 1]		== ' ')?0:1;
	}
	else if (x==(width-1))//upper-right corner
	{
		std::cout << "upper-right corner" << std::endl;
		counter += (arr[x - 1]			== ' ')?0:1;
		counter += (arr[x + width - 1]	== ' ')?0:1;
		counter += (arr[x + width]		== ' ')?0:1;
	}
	else if (x==(len-width))//lower-left corner
	{
		std::cout << "lower-left corner" << std::endl;
		counter += (arr[x - width]		== ' ')?0:1;
		counter += (arr[x - width + 1]	== ' ')?0:1;
		counter += (arr[x + 1]			== ' ')?0:1;
	}
	else if (x==(len-1))//lower-right corner
	{
		std::cout << "lower-right corner" << std::endl;
		counter += (arr[x - width - 1]	== ' ')?0:1;
		counter += (arr[x - width]		== ' ')?0:1;
		counter += (arr[x - 1]			== ' ')?0:1;
	}
	else if (x > 0 && x < (width - 1))//top row
	{
		std::cout << "top row" << std::endl;
		counter += (arr[x - 1]			== ' ')?0:1;
		counter += (arr[x + 1]			== ' ')?0:1;
		counter += (arr[x + width - 1]	== ' ')?0:1;
		counter += (arr[x + width]		== ' ')?0:1;
		counter += (arr[x + width + 1]	== ' ')?0:1;
	}
	else if (x > (len-width) && x < (len))//bottom row
	{
		std::cout << "bottom row" << std::endl;
		for (int y = 0; y < 3; y++)
			counter += (arr[x - (width+1) + y] == ' ')?0:1;
		counter += (arr[x - 1]==' ')?0:1;
		counter += (arr[x + 1]==' ')?0:1;
	}
	else if (x > (width - 1) && x < (len - width)
		 && (x % width) == 0)//left edge
	{
		std::cout << "left edge" << std::endl;
		counter += (arr[x - width]		== ' ')?0:1;
		counter += (arr[x - width + 1]	== ' ')?0:1;
		counter += (arr[x + 1]			== ' ')?0:1;
		counter += (arr[x + width]		== ' ')?0:1;
		counter += (arr[x + width + 1]	== ' ')?0:1;
	}
	else if (x > width && x < (len - width) 
		&& (x % width) == (width - 1))//right edge
	{
		std::cout << "right edge" << std::endl;
		counter += (arr[x - width - 1]	== ' ')?0:1;
		counter += (arr[x - width]		== ' ')?0:1;
		counter += (arr[x - 1]			== ' ')?0:1;
		counter += (arr[x + width - 1]	== ' ')?0:1;
		counter += (arr[x + width]		== ' ')?0:1;
	}
	else//inner cells (not edge cells)
	{
		std::cout << "inner cell" << std::endl;
		counter += (arr[x - width - 1]	== ' ')?0:1;
		counter += (arr[x - width]		== ' ')?0:1;
		counter += (arr[x - width + 1]	== ' ')?0:1;
		counter += (arr[x - 1]			== ' ')?0:1;
		counter += (arr[x + 1]			== ' ')?0:1;
		counter += (arr[x + width - 1]	== ' ')?0:1;
		counter += (arr[x + width]		== ' ')?0:1;
		counter += (arr[x + width + 1]	== ' ')?0:1;
	}
	return counter;
}

//Returns true if given cell c should live and false if it should die
//	based on the number of live neighbor cells, x
bool isLive(char c, int x)
{
	/*If a live cell x has exactly 0 or 1 live neighbor cells...
	 * OR if it has more than 3 live neighbors, cell x 
	 * will die in the next generation.
	 * If a dead cell x has exactly 3 live neighbor cells, 
	 * cell x will become live in the next generation.*/
	if (  (c == ' ' && x == 3) //dead cell to be revived
		||(c == '*' && (x == 2 || x == 3)) ) //live cell to stay live
		return true;
	else
		return false;
}

/*
 * If a live cell x has exactly 0 or 1 live neighbor cells...OR if it has more than 3 live neighbors, cell x
will die in the next generation.
3. If a dead cell x has exactly 3 live neighbor cells, cell x will become live in the next generation.
 * */
