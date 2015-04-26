/************************
* File: generation.hpp
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

#ifndef OLSONBE_GENERATION_HPP
#define OLSONBE_GENERATION_HPP

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
		int* config1_ptr;
		int config1_len;
};
/*
Function #4 (f4): Helper to function #1. This function takes an int representing the number of
live surrounding cells that surround cell x and evaluates that number based on the 4 rules to return true
(cell x will be live in next generation) or false (cell x will be dead in next generation).
*/

#endif
