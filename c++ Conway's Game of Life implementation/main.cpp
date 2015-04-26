/************************
* File: main.cpp
* Author: Benjamin R. Olson
* Date: April 9, 2014
* Title: Project 1, Implement Conway's Game of Life
* Description: This program illustrates the progression 
* 	of different Game of Life configurations
* Input: user enters on standard in 
* 	char as menu choice of configurations, 
* 	<enter> to display next generation,
* 	'q' to quit current generation process (return to config menu), 
* 	and also 'q' to quit program while in the config menu
* Output: dialog with user and display generation grid on stanard out
*************************/

#include <iostream>
#include <cstdlib>
#include "generation_copy.hpp"

using std::cin;
using std::cout;
using std::endl;

/*configurations*/
/* Each inner array contains the grid indexes of a configuration.
	 * Patterns taken from
	 * http://en.wikipedia.org/wiki/Conway's_Game_of_Life#Examples_of_patterns
	 * on April 9, 2014*/
//index locations based on single-dimension array displayed as 80 by 22 grid
int cnfg_a[] = {300, 301, 302};//a. blinker
int cnfg_b[] = {300, 301, 302, 379, 380, 381};//b. toad
int cnfg_c[] = {300, 301, 380, 381, 462, 463, 543, 544};//c. beacon
int cnfg_d[] = {117, 118, 119, 123, 124, 125,
				275, 280, 282, 287,
				355, 360, 362, 367,
				435, 440, 442, 447,
				517, 518, 519, 523, 524, 525,
				677, 678, 679, 683, 684, 685,
				755, 780, 782, 787,
				835, 840, 842, 847,
				880, 915, 920, 922, 927,
				1077, 1078, 1079, 1083, 1084, 1085};
				//d. beautiful stabilizer, accidentally created this
				//	cool configuration while trying to implement the pulsar.
				//	It slowly disintegrates into a few static and
				//	a few oscillating configurations.
//e. Gosper glider gun configuration set from Generation default constructor

char getConfiguration();
/* Pre-Condition: na
 * Post-Condition: Returns user's choice 
 * 	for the starting life configuration*/

bool continueGeneration();
/* Pre-Condition: na 
 * Post-Condition: Returns true if user decides to continue, 
 * otherwise returns false*/

void runPeriods(Generation& gen);
/* Pre-Condition: Generation object initNewLife() 
 * 	must be called beforehand 
 * Post-Condition: Runs periods for the gol configuration*/

int main()
{
	//instantiate Generation obj based on user config choice
	char choice = getConfiguration();
	switch (choice)
	{
		case 'a':
		{
			Generation g(cnfg_a, 3);
			g.initNewLife();
			runPeriods(g);
			break;
		}
		case 'b':
		{
			Generation g(cnfg_b, 6);
			g.initNewLife();
			runPeriods(g);
			break;
		}
		case 'c':
		{
			Generation g(cnfg_c, 8);
			g.initNewLife();
			runPeriods(g);
			break;
		}
		case 'd':
		{
			Generation g(cnfg_d, 48);
			g.initNewLife();
			runPeriods(g);
			break;
		}
		case 'e':
		{
			Generation g;
			g.initNewLife();
			runPeriods(g);
			break;
		}
		default:
			Generation g;
			g.initNewLife();
			runPeriods(g);
	}
	
	return 0;	
}

/* Pre-Condition: na
 * Post-Condition: Returns user's choice 
 * 	for the starting life configuration*/
char getConfiguration()
{
	char c;
	std::cout << "Configurations:" << std::endl;
	std::cout << "a. blinker\nb. toad\nc. beacon\nd. beautiful stabilizer\ne. Gosper glider gun"
			<< std::endl;
	std::cout << "Choose configuration to run from the above menu:";
	std::cin >> c;
	if (!(c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e'))
	{
		std::cout << "I'm sorry - you need to enter a, b, c, d, or e."
				<< std:: endl;
		std::cout << "Plese rerun this program." << std::endl;
		exit(1);
	}
	return c;
}


/* Pre-Condition: Used in do-while condition check
 * Post-Condition: Returns true if user hits only enter, otherwise false*/
bool continueGeneration()
{
	char c;
	std::cout << "Hit <Enter> to see the next period or hit any key to end program.";
	std::cin.get(c);
	if (c == '\n')
		return true;
	else
		return false;
}

/* Pre-Condition: Generation object initNewLife() 
 * 	must be called beforehand 
 * Post-Condition: Runs periods for the gol configuration*/
void runPeriods(Generation& gen)
{
	do
	{
		gen.displayGrid();//design f2()
		gen.calcGeneration();//design f1()
		gen.assignNewGeneration();//design f3()
	}
	while
	(
		//prompt user to display the next grid or end program
		continueGeneration()
	);
}
