/************************
* File: generation.cpp
* Author: Benjamin R. Olson
* Date: April 9, 2014
* Title: Project 1, Implement Conway's Game of Life
* Description: 
* Input: user enters on standard in 
* 	char as menu choice of configurations, 
* 	<enter> to display next generation,
* 	'q' to quit current generation process (return to config menu), 
* 	and also 'q' to quit program while in the config menu
* Output: dialog with user and display generation grid on stanard out
*************************/

#include <iostream>
#include <cstring>//used in assignNewGeneration()

using std::cin;
using std::cout;
using std::endl;

class Generation
{
	public:
		Generation(int* cnfg, int cnfg_len);
		Generation();
		void initNewLife();
		/* Pre-Condition: Only call once, before all other function calls
		 * 	on the object
		 * Post-Condition: grid1 and grid2 are filled 
		 * 	according to the configuration*/
		void displayGrid();
		/* Pre-Condition: assignNewGeneration() has just been called
		 * Post-Condition: grid1 is displayed as an 80 by 22 grid*/
		void calcGeneration();//design f1()
		/* Pre-Condition: displayGrid() has just been called
		 * Post-Condition: grid2 stores the contents to be displayed
		 * 	in the next period*/
		void assignNewGeneration();//design f3()
		/* Pre-Condition: calcGeneration() has just been called
		 * Post-Condition: grid1 and grid2 have identical array contents*/

	private:
		int countLive(int x, char* arr, int width, int len);
		/* Pre-Condition: x: current cell being evaluated,
		 * 	arr: grid in which cell x resides
		 * 	width: width of grid represented by arr
		 * 	len: length of arr
		 * Post-Condition: Returns the number of live cells 
		 * 	surrounding given cell x*/
		bool isLive(char c, int x);
		/* Pre-Condition: c: contents of a cell - either ' ' or '*'
		 * 	x: the number of live cells that are neighbors of cell c
		 * Post-Condition: Returns true if given cell c should live 
		 * 	and false if it should die based on 
		 * 	the number of live neighbor cells, x*/

		/*Data declarations*/
		//grid is 80 by 22 cells
		int* config;//design d3
		char grid1[1760];
		char grid2[1760];
		int grid_len;
		int grid_width;
		int* config_ptr;
		int config_len;
};

Generation::Generation(int* cnfg, int cnfg_len)
{
	grid_len = 1760;
	grid_width = 80;
	config_len = cnfg_len;
	config_ptr = cnfg;
}

Generation::Generation()
{
	grid_len = 1760;
	grid_width = 80;
	/* Each inner array contains the grid indexes of a configuration.
	 * Patterns taken from
	 * http://en.wikipedia.org/wiki/Conway's_Game_of_Life#Examples_of_patterns
	 * on April 9, 2014*/
	int config[36] = 
			{105, 
			 183, 185, 
			 253, 254, 261, 262, 275, 276, 
			 332, 336, 341, 342, 355, 356, 
			 401, 402, 411, 417, 421, 422,
			 481, 482, 491, 495, 497, 498, 503, 505, 
			 571, 577, 585,
			 733, 734,
			 752, 756};//Gosper glider gun
	config_len = 36;
	config_ptr = new int(config_len);//delete somewhere - make a function to access and delete!!
	for (int x = 0; x < config_len; x++)
	{
		config_ptr[x] = config[x];
	}
}
/* Pre-Condition: Only call once, before all other function calls
 * 	on the object
 * Post-Condition: grid1 and grid2 are filled 
 * 	according to the configuration*/
void Generation::initNewLife()
{
	int len = config_len;
	//fill grid1 based on configuration
	int y = 0;
	for (int x = 0; x < grid_len; x++)
	{
		if ((y < len) && (x == config_ptr[y]))
		{
			grid1[x] = '*';
			grid2[x] = '*';
			y++;
		}
		else
		{
			grid1[x] = ' ';
			grid2[x] = ' ';
		}
	}
}
/* Pre-Condition: assignNewGeneration() has just been called
 * Post-Condition: grid1 is displayed as an 80 by 22 grid*/
void Generation::displayGrid()//design f2()
{
	//80 x 22 grid = 1760
	//int gridLength = 1760;
	std::cout << "grid" << std::endl;	
	for (int x = 0, y = 0; x < grid_len; x++, y++)
	{
		if (y==grid_width)
		{
			std:: cout << '|' << std::endl;
			y = 0;
		}
		std::cout << grid1[x];
	}
	std::cout << '|' << std::endl;
	std::cout << "end grid" << std::endl;
}

/* Pre-Condition: calcGeneration() has just been called
 * Post-Condition: grid1 and grid2 have identical array contents*/
void Generation::assignNewGeneration()//design f3()
{
	//memcpy(grid1, grid2, sizeof(grid1));
	for (int x = 0; x < grid_len; x++)
	{
		grid1[x] = grid2[x];
	}
}

/* Pre-Condition: displayGrid() has just been called
 * Post-Condition: grid2 stores the contents to be displayed
 * 	in the next period*/
void Generation::calcGeneration()//design f1()
{
	char cell = ' ';
	int liveNeighbors = 0;
	for (int x = 0; x < grid_len; x++)
	{
		cell = grid1[x];
		liveNeighbors = countLive(x, grid1, grid_width, grid_len);
		if (isLive(cell, liveNeighbors))
			grid2[x] = '*';
		else
			grid2[x] = ' ';
	}
}

/* Pre-Condition: x: current cell being evaluated,
 * 	arr: grid in which cell x resides
 * 	width: width of grid represented by arr
 * 	len: length of arr
 * Post-Condition: Returns the number of live cells 
 * 	surrounding given cell x*/
int Generation::countLive(int x, char* arr, int width, int len)
{
		//out of bounds "ghost" cells considered dead
	int counter = 0;
	if (x == 0)//upper-left corner
	{
		//std::cout << "upper-left corner" << std::endl;
		counter += (arr[x + 1]			== ' ')?0:1;
		counter += (arr[width]			== ' ')?0:1;
		counter += (arr[width + 1]		== ' ')?0:1;
	}
	else if (x==(width-1))//upper-right corner
	{
		//std::cout << "upper-right corner" << std::endl;
		counter += (arr[x - 1]			== ' ')?0:1;
		counter += (arr[x + width - 1]	== ' ')?0:1;
		counter += (arr[x + width]		== ' ')?0:1;
	}
	else if (x==(len-width))//lower-left corner
	{
		//std::cout << "lower-left corner" << std::endl;
		counter += (arr[x - width]		== ' ')?0:1;
		counter += (arr[x - width + 1]	== ' ')?0:1;
		counter += (arr[x + 1]			== ' ')?0:1;
	}
	else if (x==(len-1))//lower-right corner
	{
		//std::cout << "lower-right corner" << std::endl;
		counter += (arr[x - width - 1]	== ' ')?0:1;
		counter += (arr[x - width]		== ' ')?0:1;
		counter += (arr[x - 1]			== ' ')?0:1;
	}
	else if (x > 0 && x < (width - 1))//top row
	{
		//std::cout << "top row" << std::endl;
		counter += (arr[x - 1]			== ' ')?0:1;
		counter += (arr[x + 1]			== ' ')?0:1;
		counter += (arr[x + width - 1]	== ' ')?0:1;
		counter += (arr[x + width]		== ' ')?0:1;
		counter += (arr[x + width + 1]	== ' ')?0:1;
	}
	else if (x > (len-width) && x < (len))//bottom row
	{
		//std::cout << "bottom row" << std::endl;
		for (int y = 0; y < 3; y++)
			counter += (arr[x - (width+1) + y] == ' ')?0:1;
		counter += (arr[x - 1]==' ')?0:1;
		counter += (arr[x + 1]==' ')?0:1;
	}
	else if (x > (width - 1) && x < (len - width)
		 && (x % width) == 0)//left edge
	{
		//std::cout << "left edge" << std::endl;
		counter += (arr[x - width]		== ' ')?0:1;
		counter += (arr[x - width + 1]	== ' ')?0:1;
		counter += (arr[x + 1]			== ' ')?0:1;
		counter += (arr[x + width]		== ' ')?0:1;
		counter += (arr[x + width + 1]	== ' ')?0:1;
	}
	else if (x > width && x < (len - width) 
		&& (x % width) == (width - 1))//right edge
	{
		//std::cout << "right edge" << std::endl;
		counter += (arr[x - width - 1]	== ' ')?0:1;
		counter += (arr[x - width]		== ' ')?0:1;
		counter += (arr[x - 1]			== ' ')?0:1;
		counter += (arr[x + width - 1]	== ' ')?0:1;
		counter += (arr[x + width]		== ' ')?0:1;
	}
	else//inner cells (not edge cells)
	{
		//std::cout << "inner cell" << std::endl;
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

/* Pre-Condition: c: contents of a cell - either ' ' or '*'
 * 	x: the number of live cells that are neighbors of cell c
 * Post-Condition: Returns true if given cell c should live 
 * 	and false if it should die based on 
 * 	the number of live neighbor cells, x*/
bool Generation::isLive(char c, int x)
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


