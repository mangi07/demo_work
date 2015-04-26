
/*
 * Filename: combat_midified.cpp
 * Author: Benjamin R. Olson
 * Date: May 24, 2014
 * Description: Project 4, Combat Game Modified
 * 	4 Players Compete with each other
 * 	until only one player remaings with
 * 	strength greater than 0.
 * Input: (1) User enters ints to decide players to instantiate
 * 	and players to fight each other
 * 	(2) User promts to resume game or quit at the end of each round
 * Output: Game state after each round is calculated.
 * */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

//abstract parent class
class character
{
public:
	character()
	{
		attackType = {0, 0};
		defenseType = {0, 0};
		this->armor = 0;
		this->strength = 0;
		this->name = "error: Default constructor called.\n";
	}
	character(int attkDiceCount, int attkDiceSides, 
		int defDiceCount, int defDiceSides,
		int armor, int strength, std::string name)
	{
		attackType = {attkDiceCount, attkDiceSides};
		defenseType = {defDiceCount, defDiceSides};
		this->armor = armor;
		this->strength = strength;
		this->name = name;
	}
	virtual void modifyRoll(bool attacker) = 0;//modification
	void rollDice(bool attacker);//modification
	virtual void calcDamage(character* a);//modification
	int getRoll();
	int getAttackDiceAmount();
	int getAttackDiceSides();
	int getDefenseDiceAmount();
	int getDefenseDiceSides();
	int getArmor();
	std::string getName();
	int getStrength();
	void setStrength(int strength);

protected://modification
	int roll;
	struct dice{int diceCount; int sides;};
	dice attackType;
	dice defenseType;
	int armor;
	int strength;
	std::string name;
};

class goblin : public character
{
public:
	goblin() : character()
	{
		//intentionally left blank	
	}
	goblin(int attkDiceCount, int attkDiceSides, 
		int defDiceCount, int defDiceSides,
		int armor, int strength, std::string name) : 
		character(
			attkDiceCount, attkDiceSides, 
			defDiceCount, defDiceSides,
			armor, strength, name
		)
	{
		//intentionally left blank
	}
	void modifyRoll(bool attacker)
	{
		//intentionally does nothing
	}
	//damage is 4 less than it would be in the parent class,
	//	but never to increase strength - just to boost defense
	//Pre-condition: called after modifyRoll()
	//a is attacker
	void calcDamage(character* a)//modification
	{
		int damage = a->getRoll() - roll;
		if(damage > 0)//attack was greater than defense,
		//so damage is against the defender
		{	
			damage = damage - armor;
			if(damage > 0)
			{
				if(damage > 4)
				{
					damage = damage - 4;
					std::cout << "\tGoblin's damage was reduced by 4."
						<< std::endl;
					std::cout << "\tNew damage: " << damage
						<< std::endl;
				}
				strength = strength - damage;
				std::cout << name << "'s strength reduced by " 
					<< damage << "." << std::endl;
			}
		}
		else//defense was greater than attack,
		//so damage is against the attacker
		{
			damage = (-damage) - a->getArmor();
			if(damage > 0)
			{
				//access a's private members directly?
				a->setStrength(a->getStrength() - damage);
				std::cout << a->getName() << "'s strength reduced by " 
					<< damage << "." << std::endl;
			}
		}
	}
};

class barbarian : public character
{
public:
	barbarian() : character()
	{
		//intentionally left blank
	}
	barbarian(int attkDiceCount, int attkDiceSides, 
		int defDiceCount, int defDiceSides,
		int armor, int strength, std::string name) : 
		character(
			attkDiceCount, attkDiceSides, 
			defDiceCount, defDiceSides,
			armor, strength, name
		)
	{
		shield = 5;
		sword = 7;
	}
	//Pre-condition: call after roll
	void modifyRoll(bool attacker)
	{
		if(attacker)
		{
			roll = roll + sword;
			std::cout << "\tBarbarian's sword increased roll by "
					<< sword << "." << std::endl;
		}
		else
		{
			roll = roll + shield;
			std::cout << "\tBarbarian's shield increased roll by "
					<< shield << "." << std::endl;
		}
		std::cout << "\tNew roll: " << roll << std::endl;
	}
	//Pre-condition: called after modifyRoll()
	//a is attacker
	void calcDamage(character* a)//modification
	{//modifications to body
		//int strength;
		int damage = a->getRoll() - roll;
		if(damage > 0)//attack was greater than defense,
		//so damage is against the defender
		{	
			damage = damage - armor;
			if(damage > 0)
			{
				strength = strength - damage;
				std::cout << name << "'s strength reduced by " 
					<< damage << "." << std::endl;
			}
		}
		else//defense was greater than attack,
		//so damage is against the attacker
		{
			damage = (-damage) - a->getArmor();
			if(damage > 0)
			{
				//access a's private members directly?
				a->setStrength(a->getStrength() - damage);
				std::cout << a->getName() << "'s strength reduced by " 
					<< damage << "." << std::endl;
			}
		}
	}
private:
	int shield;
	int sword;
	
};

class reptile : public character
{
public:
	reptile() : character()
	{
		//intentionally left blank	
	}
	reptile(int attkDiceCount, int attkDiceSides, 
		int defDiceCount, int defDiceSides,
		int armor, int strength, std::string name) : 
		character(
			attkDiceCount, attkDiceSides, 
			defDiceCount, defDiceSides,
			armor, strength, name
		)
	{
		//intentionally left blank
	}
	//Pre-condition: called after modifyRoll()
	//a is attacker
	void calcDamage(character* a)//modification
	{//modifications to body
		//int strength;
		int damage = a->getRoll() - roll;
		if(damage > 0)//attack was greater than defense,
		//so damage is against the defender
		{	
			damage = damage - armor;
			if(damage > 0)
			{
				strength = strength - damage;
				std::cout << name << "'s strength reduced by " 
					<< damage << "." << std::endl;
			}
		}
		else//defense was greater than attack,
		//so damage is against the attacker
		{
			damage = (-damage) - a->getArmor();
			if(damage > 0)
			{
				a->setStrength(a->getStrength() - damage);
				std::cout << a->getName() << "'s strength reduced by " 
					<< damage << "." << std::endl;
			}
		}
	}
	void modifyRoll(bool attacker)
	{
		tailWhip(attacker);
	}
protected:
	/*
	Pre-condition: Call after roll.
	If dragon is attacking, tailWhip() adds 2 to the dragon's roll. If dragon is defending,
	adds 3 to the dragon's roll.
	 */
	//modification
	void tailWhip(bool attacker)
	{
		if(attacker)
		{
			roll = roll + 2;
			std::cout << "\tReptile's tail whip increased roll by 2."
					<< std::endl;
		}
		else
		{
			roll = roll + 3;
			std::cout << "\tReptile's tail whip increased roll by 3."
					<< std::endl;
		}
		std::cout << "\tNew roll: " << roll << std::endl;
	}
};

class dragon : public reptile
{
public:
	dragon() : reptile()
	{
		//intentionally left blank	
	}
	dragon(int attkDiceCount, int attkDiceSides, 
		int defDiceCount, int defDiceSides,
		int armor, int strength, std::string name) : 
		reptile(
			attkDiceCount, attkDiceSides, 
			defDiceCount, defDiceSides,
			armor, strength, name
		)
	{
		//intentionally left blank
	}
	//Pre-condition: called after modifyRoll()
	//a is attacker
	void calcDamage(character* a)//modification
	{//modifications to body
		//int strength;
		int damage = a->getRoll() - roll;
		if(damage > 0)//attack was greater than defense,
		//so damage is against the defender
		{	
			damage = damage - armor;
			if(damage > 0)
			{
				strength = strength - damage;
				std::cout << name << "'s strength reduced by " 
					<< damage << "." << std::endl;
			}
		}
		else//defense was greater than attack,
		//so damage is against the attacker
		{
			damage = (-damage) - a->getArmor();
			if(damage > 0)
			{
				a->setStrength(a->getStrength() - damage);
				std::cout << a->getName() << "'s strength reduced by " 
					<< damage << "." << std::endl;
			}
		}
	}
	void modifyRoll(bool attacker)
	{
		tailWhip(attacker);
	}
protected:
	//redefined from parent class reptile
	//called in modifyRoll() of parent class
	void tailWhip(bool attacker)
	{
		if(attacker)
		{
			roll = roll + 2;
			std::cout << "\tDragon's tail whip increased roll by 2."
					<< std::endl;
		}
		else
		{
			roll = roll + 10;
			std::cout << "\tDragon's tail whip increased roll by 10."
					<< std::endl;
		}
		std::cout << "\tNew roll: " << roll << std::endl;
	}	
};

class blueMan : public character
{
public:
	blueMan() : character()
	{
		//intentionally left blank	
	}
	blueMan(int attkDiceCount, int attkDiceSides, 
		int defDiceCount, int defDiceSides,
		int armor, int strength, std::string name) : 
		character(
			attkDiceCount, attkDiceSides, 
			defDiceCount, defDiceSides,
			armor, strength, name
		)
	{
		//intentionally left blank
	}
	void modifyRoll(bool attacker)
	{
		//intentionally does nothing
	}
};


//The following functions are commented in more detail with their definitions.
void calcRound(character* attacker, character* defender);
//with local variables int attackRoll and int
//defenseRoll, calls some of the functions below
void choosePair(std::vector<character*> &c, int &attacker, int &defender);
//Pre-Condition: vector arg must have been initiated by initVector()
//randomly generates an attacker id# 0
//through size of vector → assigns id# to attacker → similarly assigns second id# to defender.
void removePlayer(std::vector<character*> &c);
bool isWinner(std::vector<character*> &c);
void initVector(std::vector<character*> &c, character* c1, 
		character* c2, character* c3, character* c4, character* c5,
		character* c6, character* c7, character* c8, character* c9, 
		character* c10);//modification
//adds each character to the vector
void showRules();
void showInitialStats(std::vector<character*> &c);
void showStats(std::vector<character*> &c, int attacker, int defender);
void winMessage(std::vector<character*> &c, int winner);
void quitMessage();
int rand_int(int min, int max);

int main()
{
	std::vector<character*> c;
	goblin* g1 = new goblin(2, 6, 1, 6, 3, 8, "Goblin 1"); 
	barbarian* b1 = new barbarian(2, 6, 2, 6, 0, 12, "Barbarian 1");
	reptile* r1 = new reptile(3, 6, 1, 6, 7, 18, "Reptile 1");
	blueMan* bm1 = new blueMan(2, 10, 3, 6, 3, 12, "Blue Man 1");
	dragon* d1 = new dragon(3, 6, 1, 6, 7, 18, "Dragon 1");
	
	goblin* g2 = new goblin(2, 6, 1, 6, 3, 8, "Goblin 2"); 
	barbarian* b2 = new barbarian(2, 6, 2, 6, 0, 12, "Barbarian 2");
	reptile* r2 = new reptile(3, 6, 1, 6, 7, 18, "Reptile 2");
	blueMan* bm2 = new blueMan(2, 10, 3, 6, 3, 12, "Blue Man 2");
	dragon* d2 = new dragon(3, 6, 1, 6, 7, 18, "Dragon 2");
	
	initVector(c, g1, b1, r1, bm1, d1, g2, b2, r2, bm2, d2);
	
	showRules();
	std::string input;
	std::cout << "(any key to continue)" << std::endl;
	std::getline(std::cin, input);
	
	showInitialStats(c);
	std::cout << "(any key to continue)" << std::endl;
	std::getline(std::cin, input);
	
	bool next_round = true;
	int attacker;
	int defender;
	int temp;
	//attacker and defender swapped each round, using temp
	//both are used as an index in vector c
	choosePair(c, attacker, defender);
	do
	{
		calcRound(c.at(attacker), c.at(defender));
		showStats(c, attacker, defender);
		//removePlayer(c);
		if(c.at(defender)->getStrength() <= 0)
		{
			winMessage(c, attacker);
			quitMessage();
			return 0;
		}
		else if(c.at(attacker)->getStrength() <= 0)
		{
			winMessage(c, defender);
			quitMessage();
			return 0;
		}
		std::cout << "\nWould you like to continue with next round?\n"
			<< "Hit <Enter> to continue or any key to quit game: ";
		std::getline(std::cin, input);
		if(input == "")
			next_round = true;
		else
			next_round = false;
		temp = attacker;
		attacker = defender;
		defender = temp;
	}
	while(next_round);

	return 0;
}

//parent class functions
int character::getRoll()
{
	return this->roll;
}
int character::getAttackDiceAmount()
{
	return attackType.diceCount;	
}
int character::getAttackDiceSides()
{
	return attackType.sides;
}
int character::getDefenseDiceAmount()
{
	return defenseType.diceCount;
}
int character::getDefenseDiceSides()
{
	return defenseType.sides;
}
int character::getArmor()
{
	return armor;
}
std::string character::getName()
{
	return name;
}
int character::getStrength()
{
	return strength;
}
void character::setStrength(int strength)
{
	this->strength = strength;
}
/*Pre-condition: Dice have been rolled before this function is called.
 *Post-condition: The calling object is the defender
 * 	and the attacker is passed in as arg a.
 * 	Either defender's or attacker's strength may possibly
 * 	be reduced by the difference between the 2 players' dice,
 * 	depending on who rolled more and the armor of the player
 * 	who rolled less.*/
void character::calcDamage(character* a)//modification
{//modifications to body
	//int strength;
	int damage = a->getRoll() - roll;
	if(damage > 0)//attack was greater than defense,
	//so damage is against the defender
	{	
		damage = damage - armor;
		if(damage > 0)
		{
			strength = strength - damage;
			std::cout << name << "'s strength reduced by " 
				<< damage << "." << std::endl;
		}
	}
	else//defense was greater than attack,
	//so damage is against the attacker
	{
		damage = (-damage) - a->getArmor();
		if(damage > 0)
		{
			//access a's private members directly?
			a->setStrength(a->getStrength() - damage);
			std::cout << a->getName() << "'s strength reduced by " 
				<< damage << "." << std::endl;
		}
	}
}
/*Pre-conditions: n/a
 *Return: If attacker, then attacker's dice are rolled
 * 	and their sum is returned,
 * 	otherwise the defender's dice are rolled
 * 	and their sum is returned. */
void character::rollDice(bool attacker)//modification
{
	int dice_count;
	int dice_sides;
	int total_roll = 0;
	if (attacker)
	{
		dice_count = attackType.diceCount;
		dice_sides = attackType.sides;
	}
	else
	{
		dice_count = defenseType.diceCount;
		dice_sides = defenseType.sides;
	}
	for(int x = 0; x < dice_count; x++)
	{
		total_roll += rand_int(1, dice_sides);
	}
	roll = total_roll;
}
//end parent class functions

/*Pre-conditions: initVector(...) has been called
 *Post-conditions: Either a or b's strength may be reduced*/
void calcRound(character* attacker, character* defender)
{
	attacker->rollDice(true);//modification
	defender->rollDice(false);//modification
	
	std::cout << "\nAttacker " << attacker->getName()
		<< " (armor = " << attacker->getArmor() << ")" 
		<< " rolled " << attacker->getRoll() << "." << std::endl;//modification
	attacker->modifyRoll(true);//modification
	
	std::cout << "Defender " << defender->getName() 
		<< " (armor = " << defender->getArmor() << ")"
		<< " rolled " << defender->getRoll() << "." << std::endl;//modification
	defender->modifyRoll(false);//modification
	defender->calcDamage(attacker);//modification
}
/*Pre-condition: Vector arg has been initiated by initVector()
 *Post-condition: Randomly generates an attacker id# 0
 *	through size of vector → assigns id# to attacker → 
 * 	similarly assigns second id# to defender.*/
void choosePair(std::vector<character*> &c, int &attacker, int &defender)
{
	std::cout << "Please choose a pair to compete:" << std::endl;
	for (unsigned int x = 0; x < c.size(); x++)
	{
		std::cout << "Player " << x << ": "
			<< c.at(x)->getName() << std::endl;
	}
	std::cout << "Enter attacker's # and defender's # with a space in between:"
		<< std::endl;
	std::string entry;
	bool invalid_entry = true;
	while(invalid_entry)
	{
		std::getline(std::cin, entry);
		try
		{
			attacker = static_cast<int>(entry.at(0) - '0');
			defender = static_cast<int>(entry.at(2) - '0');
			if(entry.at(1) != ' ')
			{
				std::cout << "There must be a space in bewteen. "
					<< "Please try again." << std::endl;
				continue;
			}
		}
		catch(...)
		{
			std::cout << "Invalid entry. Please try again." << std::endl;
			continue;
		}
		if(attacker < 0 || attacker > c.size()
			|| defender < 0 || defender > c.size())
			std::cout << "Invalid entry.  Please try again:";
		else
			invalid_entry = false;
	}
	std::cout << "You chose " << c.at(attacker)->getName()
		<< " as the attacker and\n"
		<< c.at(defender)->getName()
		<< " as the defender." << std::endl;
}
/*Pre-condition: n/a
 *Post-condition: a character from vector c is removed
 * 	if its strength is 0 or less*/
void removePlayer(std::vector<character*> &c)
{
	for (unsigned int x = 0; x < c.size(); x++)
	{
		if(c.at(x)->getStrength() <= 0)
		{
			std::cout << "\n" << c.at(x)->getName() 
			<< " is eliminated!\n" << std::endl;
			delete c.at(x);
			c.erase(c.begin() + x);
		}
	}
}
/*Return: If vector size is 1, returns true, else returns false*/
//bool isWinner(std::vector<character*> &c)
//{
	//return c.size() == 1;
//}
/*Post-condition: Adds each character arg to the vector arg.*/
void initVector(std::vector<character*> &c, character* c1, 
		character* c2, character* c3, character* c4, character* c5,
		character* c6, character* c7, character* c8, character* c9, 
		character* c10)
{
	c.push_back(c1);
	c.push_back(c2);
	c.push_back(c3);
	c.push_back(c4);
	c.push_back(c5);
	c.push_back(c6);
	c.push_back(c7);
	c.push_back(c8);
	c.push_back(c9);
	c.push_back(c10);
}
/*Called only once, at the start of the game.*/
void showRules()//modification
{
	std::cout << "\nPROJECT 3, COMBAT GAME WITH DICE\n" << std::endl;
	std::cout << "This game is played entirely by the computer itself."
		<< std::endl;
	std::cout << "\tRules:" << std::endl;
	std::cout << "Each round is determined by following rules 1 - 6 "
		<< "in order:" << std::endl;
	std::cout << "1. You select two players out of four to compete."
		<< std::endl;
	std::cout << "2. The attacker and defender both roll dice\n" 
		<< "based on the type of each player's dice.\n"
		<< "(eg: 2d6 is 2 dice with 6 sides each)." << std::endl;
	std::cout << "3. If the difference is in favor of the attacker\n"
		<< "and greater than the defender's armor,\n"
		<< "the defenders strength decreases by the following amount:\n"
		<< "(attack - defense) - armor." << std::endl;
	std::cout << "4. If the difference is in favor of the defender\n"
		<< "the attacker's strength may be deducted in the same manner."
		<< std::endl;
	std::cout << "5. The pair of combatants take turns attacking "
		<< "and defending each other." << std::endl;
	std::cout << "6. If one player loses all strength, that player\n"
		<< "is eliminated from the game and the other one wins." << std::endl;
	std::cout << "\nYou may choose to continue the game or quit\n"
		<< "at the conclusion of each round." << std::endl;
}
/*Pre-condition: vector c must be instantiated where each element/object's
 * 	members have been assigned values.
 * Iterates through vector to show all features of each character*/
void showInitialStats(std::vector<character*> &c)
{
	std::cout << "\tOutput Format:" << std::endl;
	std::cout << "Name: attack<#dice>d<#sides>, "
		<< "attack<#dice>d<#sides>, "
		<< "armor, strength" << std::endl;
	for (unsigned int x = 0; x < c.size(); x++)
	{
		std::cout << c.at(x)->getName() << ":\t"
				<< c.at(x)->getAttackDiceAmount() << "d"
				<< c.at(x)->getAttackDiceSides() << ", "
				<< c.at(x)->getDefenseDiceAmount() << "d"
				<< c.at(x)->getDefenseDiceSides() << ", "
				<< c.at(x)->getArmor() << ", "
				<< c.at(x)->getStrength() << std::endl;
	}	
}
/*Pre-condition: vector c must be instantiated where each element/object's
 * 	members have been assigned values.
 * Iterates through vector to show name and strength 
 * 	of each remaining character*/
void showStats(std::vector<character*> &c, int attacker, int defender)
{
	std::cout << c.at(attacker)->getName() << "'s strength value:\t" 
		<< c.at(attacker)->getStrength() << std::endl;
	std::cout << c.at(defender)->getName() << "'s strength value:\t" 
		<< c.at(defender)->getStrength() << std::endl;	
}

/*If there is only one character remaining in the vector,
 * this function shows a message to the user stating who the winner is*/
void winMessage(std::vector<character*> &c, int winner )//modification
{
	std::cout << c.at(winner)->getName() << " is the winner!" 
			<< std::endl;	
}
/*Displayed if user decides to quit or when the game ends*/
void quitMessage()
{
	std::cout << "\n\tThank you for playing!\n\n";	
}

/*Return: A random int between min and max, inclusive*/
int rand_int(int min, int max)
{
	return ( rand() % (max - (min - 1)) ) + min;
}


