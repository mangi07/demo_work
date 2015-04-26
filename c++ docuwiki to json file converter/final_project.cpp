/************************
* File Name: final_project.cpp
* Author: Benjamin R. Olson
* Date: March 14, 2014
* Title: Final Project, DocuWiki to Json Parser
* Description: Converts DocuWiki files of a
* 	specific format into Json files.
* Input: CLI filename(s) and cin towards the end
* 	to dialog with the user.
* Output: Json file in the working directory,
* 	and information to the user about the status
*************************/


#include <iostream>
#include <cstdlib> //rand
#include <ctime> //time
#include <string>
#include <cstring>
#include <cctype>
#include <fstream>

using namespace std;

//prototypes
class DocuWikiParser
/*An int ID determines how the syntax for that current line of text is validated and parsed,
 *	and this ID changes based on what kind of data was parsed from the previous line
 *	of the same file.
 *This class could be extended to accept and parse additional DocuWiki syntax*/
{
	public:
		DocuWikiParser ();
		//string getData (string text, int ID, string syntaxToken);
		string getData(string text);
		//these overloaded functions extract values from the input file
		
	private:
		//variables
		int ID;//ints 1 - 4 identify different stages of the parsing
		
		//two overloaded functions
		string stripSyntax(string textLine, int x, char c);
		//returns textLine stripped of x char's on both ends
		//	if there are at least x number of counsecutive same char's
		//	on both ends of textLine...
		//	otherwise exits the program with file syntax error message
		//	Example: args: ("====== Title ======", 6, '=')
		//			return: " Title "
		string stripSyntax(string textLine, int x, char c1, char c2);
		//returns textLine stripped of x1 consecutive same c1 char's on left side
		//	and x2 consecutive same c1 char's on right side of textLine
		//	otherwise exits the program with file syntax error message
		//	Example: arg: "{{dir:subdir:pic.jpg}}"
		//			return: "dir:subdir:pic.jpg"
		
		string docuToDir(string dir);
		//parses given file directory string (eg: "dir:subdir:pic.jpg")
		//returns HTML-readable directory format (eg: "dir/subdir/pic.jpg")
		
		void insertEscapeQuotes(string &str);
		//pass-by-value
		/*Inserts '\\' before every occurrence of
		 * '\"' in the argument passed in.
		 * */
}dwp;

struct FileData
{
	string title;
	string **picTextPairs;
	string footer;	
}fd;

string * filterArgs(int arg_nums, char *args[]);
/*Takes a pointer to an array of c-strings (argv[]) from CLI
 *	and checks their extensions for ".txt"
 *Exits program with error message if at least one filename extension
 *	does not end in ".txt"
 *On success (no input errors), returns a pointer to a string array
 *	of filenames.*/

int countPicTextPairs (string filename);
/*Returns the number of lines starting with '{'
 *	in file with filename*/

void extractValues(const string filename, DocuWikiParser * dwp, 
					FileData * fd, int pairs);
/*Opens file with filename, extracts values using dwp.getData,
 *	and assigns these values to fd struct*/

void initPairs ( string **& arr, int pairs );
/*initialize 2d array pointer, pic-text pairs*/

string createJsonString(FileData * fd, int pairs);
/*creats a Json string using values from fd struct*/

void displayRandomFile(const string * filenames, int fileNums);
/*displays the contents of a randomly chosen file 
	within the given range of filenames*/

void printHelp();
/*display information to the user about how to use the program*/

/*Arguments: string of four 0s and 1s in Twos Compliment
Return: int equivalent of given binary string*/
int binaryToInt(string str);

int main (int argc, char * argv[])
{
	//variables
	DocuWikiParser *dwp_ptr = &dwp;
	//pointer to dwp object of DocuWikiParser class
	
	/*	TEST class DocuWikiParser:
	cout << "dwp.getData(): " << dwp.getData("======title======") << endl;
	cout << "dwp.getData(): " << dwp.getData("{{:dir:subdir:pic.jpg}}") << endl;
	cout << "dwp.getData(): " << dwp.getData("text text text text") << endl;
	cout << "dwp.getData(): " << dwp.getData("{{:dir:subdir:pic.jpg}}") << endl;
	cout << "dwp.getData(): " << dwp.getData("text text text text") << endl;
	cout << "dwp.getData(): " << dwp.getData("//footer//") << endl;
	*/
	
	
	FileData *fd_ptr = &fd;
	//pointer to fd object of FileData struct
	string *files = filterArgs(argc, argv);
	//pointer to an array of strings representing input filenames
	
	
	string *jsonfiles = new string[argc-1];
	for (int x = 0; x < argc-1; x++)
	{
		cout << "\nParsing \"" << files[x] << "\"..." << endl; 
		
		int pairs = countPicTextPairs (argv[x+1]);
		extractValues(files[x], dwp_ptr, fd_ptr, pairs);
		
		string JsonStr = createJsonString(fd_ptr, pairs);
			//cout << "JsonStr: " << endl << JsonStr << endl;
		ofstream of;
		
		//replace ".txt" extension with ".json"
		jsonfiles[x] = files[x].substr( 0, (files[x].length()-4) ) + ".json";
		
		//prepare for file output
		of.open(jsonfiles[x].c_str());
		if (of.fail())
		{
			cout << "error: Could not creat Json file." << endl;
			exit(EXIT_FAILURE);
		}
		
		//write to file
		of << JsonStr;
		cout << "File #" << x+1 << " " << jsonfiles[x] << "\n  successfully created." << endl;
		of.close();
	}
	
	char y_n;
	cout << "\nWould you like to choose a random *.json file to view its contents? (y/n)" << endl;
	cout << "(If you choose n, you will move straight to the two's compliment binary conversions demo.)" << endl;
	cin.get(y_n);
	if (y_n == 'y')
	{	
		displayRandomFile( jsonfiles, argc-1 );
		cout << "********END OF FILE********" << endl << endl;
	}
	
	delete [] files;
	delete [] jsonfiles; delete [] *(fd).picTextPairs;
	
	//two's compliment binary conversions demo
	cout << "\tTwo's Compliment Demo:" << endl << endl;
	cout << "1110 to int: " << binaryToInt("1110") << endl;//-2
	cout << "0110 to int: " << binaryToInt("0110") << endl;//6
	cout << "0111 to int: " << binaryToInt("0111") << endl;//7
	cout << "1001 to int: " << binaryToInt("1001") << endl;//-7
	
	
	
	return 0;

}

//function declarations
string * filterArgs(int arg_nums, char *args[])
{
	if (arg_nums == 1) printHelp();
	int start_pos;
	string *filenames = new string[arg_nums-1];
	for  (int i = 0; i < arg_nums-1; i++)
	{
		filenames[i] = args[i+1];
		if (filenames[i].length()<5)
		{
			cout << "\nerror: input filename " << filenames[i] << " is too short." << endl << endl;
			exit(EXIT_FAILURE);
		}
		//cout << "filenames[i]: " << filenames[i] << endl;
		start_pos = filenames[i].length()-4;
		//cout << "filenames[i].substr(start_pos, 4): " << filenames[i].substr(start_pos, 4) << endl;
		if (filenames[i].substr(start_pos, 4) != ".txt")
		{
			cout << "\nerror: input filename #" << (i+1) 
				<< ", \"" << filenames[i] << "\", must be a text file (*.txt)." << endl << endl;
			exit(EXIT_FAILURE);
		}	 
	}
	return filenames;
}

//parser class constructor
DocuWikiParser::DocuWikiParser()
{
	ID = 1;	
}

//parser class functions
string DocuWikiParser::getData (string text)
{
	string dir;//used in cases 2 and 4
	switch (ID)
	{
		case 1:
			//cout << "case1: parse title" << endl;
			ID = 2;//change status to parse picture directory
			insertEscapeQuotes(text);
			return stripSyntax(text, 6, '=');
		case 2:
			//cout << "case2: parse picture directory" << endl;
			ID = 3;
			dir = stripSyntax(text, 2, '{', '}');
			insertEscapeQuotes(text);
			return docuToDir(dir);
		case 3:
			//cout << "case3: getting text" << endl;
			ID = 4;
			insertEscapeQuotes(text);
			return text;//no processing necessary
		case 4:
			//cout << "case4: parse pic dir or getting footer" << endl;
			if (text[0] != '/')
			{
				ID = 3;//there must be another pic-text pair...
				//too early for the footer
				//cout << "case 4 text for pic: " << text << endl;
				dir = stripSyntax(text, 2, '{', '}');
				return docuToDir(dir);
			}
			ID = 1;//reset ID for next file to be processed
			insertEscapeQuotes(text);
			return stripSyntax(text, 2, '/');
		default:
			cout << "error: unknown" << endl;
			exit(EXIT_FAILURE);	
	}
	return text;
}

/*returns textLine stripped of x char's on both ends
	if there are at least x number of counsecutive same char's
	on both ends of textLine...
	otherwise exits the program with file syntax error message*/
string DocuWikiParser::stripSyntax(string textLine, int x, char c)
{
	int len = textLine.length();
	char a = textLine[0];//first char
	char z = textLine[len - 1];//last char
	//cout << "a: '" << a << "' and z: '" << z << "' and c: '" << c << "'"<< endl;
	if (x == 0)
	{
		return textLine;
	}
	
	else if (a != c || z != c)
	{
		cout << "\nerror: Current file syntax" << endl << endl;
		exit(EXIT_FAILURE);
	}	
	else if (a == z)
	{
		//cout << "textLine.substr(1, len-2): " << textLine.substr(1, len-2) << endl;
		//cout << "x: " << x << endl;
		return stripSyntax( textLine.substr(1, len-2), --x, c );
	}
	else
	{
		cout << "\nerror: Current file syntax" << endl << endl;
		exit(EXIT_FAILURE);
	}
}

/*returns textLine stripped of x consecutive same c1 char's on left side
	and x consecutive same c1 char's on right side of textLine
	otherwise exits the program with file syntax error message
Example usage: arg: "{{dir:subdir:pic.jpg}}"
		return: "dir:subdir:pic.jpg" */
string DocuWikiParser::stripSyntax(string textLine, int x, char c1, char c2)
{
	int len = textLine.length();
	char a = textLine[0];//first char
	char z = textLine[len - 1];//last char
	
	if (x == 0)
	{
		return textLine;
	}
	else if (a != c1 || z != c2)
	{
		cout << "\nerror: Current file syntax" << endl << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		//cout << "textLine.substr(1, len-2): " << textLine.substr(1, len-2) << endl;
		//cout << "x: " << x << endl;
		return stripSyntax( textLine.substr(1, len-2), --x, c1, c2 );
	}	
}

//pass by value
//This function could be modified and made more modular by adding two formal arguments
//	one for '/' (character to replace) and one for ':' (the replacement)
/*returns dir with every occurrence of ':'
	replaced with '/' */
string DocuWikiParser::docuToDir(string dir)
{
	for (int i = 0; i < dir.length(); i++)
	{
		if (dir[i] == ':')
			dir[i] = '/';	
	}
	return dir;
}


//pass by value
/*Inserts '\\' before every occurrence of
 * '\"' in the argument passed in.
 * */
void DocuWikiParser::insertEscapeQuotes(string &str)
{
	for (int x = 0; x < str.length(); x++)
	{
		if (str[x]=='\"')
		{
			str.insert(x, 1, '\\');
			x++;
		}	
	}	
}

/*Opens file with filename, extracts values using dwp.getData(),
	and assigns these values to fd struct*/
int countPicTextPairs (string filename)
{
	ifstream f;
	const char *c = filename.c_str();
	f.open(c);
	
	if (f.fail())
	{
		cout << "\nerror: Failed to open file: " << 
			filename << endl << endl;
		exit(EXIT_FAILURE);
	}
	//count number of pic-text pairs
	int counter = 0;
	string str;
	while (getline(f, str))
	{
		//cout << "in while loop" << endl;
		if (str == "") continue;
		if (str[0] == '{') counter++;
	}
	f.close();
	return counter;	
}

/*Opens file with filename, extracts values using dwp.getData,
	and assigns these values to fd struct*/
void extractValues(const string filename, DocuWikiParser * dwp, 
					FileData * fd, int pairs)
{
	ifstream f;
	string str;
	const char *c = filename.c_str();
	f.open(c);
	if (f.fail())
	{
		cout << "error: Failed to open file: " << 
			filename << endl << endl;
		exit(EXIT_FAILURE);
	}
	
	//cout << "getting title into struct" << endl;
	while (getline(f, str)) if (str != "") break;
	fd->title = dwp->getData(str);
	
	//cout << "getting pic-text pairs into struct" << endl;
	initPairs ( fd->picTextPairs, pairs );
	for ( int i = 0; i < pairs; i++ )
	{
		//get pic
		while (getline(f, str)) if (str != "") break;
		fd->picTextPairs[i][0] = dwp->getData(str);
		
		//get text
		while (getline(f, str)) if (str != "") break;
		//cout << "line 376: text str: " << str << endl;
		fd->picTextPairs[i][1] = dwp->getData(str);
		
	}
	
	//cout << "getting footer into struct" << endl;
	while (getline(f, str)) if (str != "") break;
	fd->footer = dwp->getData(str);
	
	f.close();
}

/*initialize 2d array pointer, pic-text pairs*/
void initPairs ( string **& arr, int pairs )
{
	arr = new string*[pairs];
	for ( int i = 0; i < pairs; i++ )
		arr[i] = new string[2];
}

/*creats a Json string using values from fd struct*/
string createJsonString(FileData * fd, int pairs)
{
	string JsonStr;
	
	//title
	JsonStr = 
		(string)"{\n" +
			"\t\"title\":\"" + fd->title + "\",\n" +
			"\t\"picTextPairs\":[\n";
			
	//pic-text pairs
	for (int x = 0; x < pairs-1; x++)
	{
		JsonStr += "\t\t{\"picture\":\"" + fd->picTextPairs[x][0] + "\",\n" +
					"\t\t \"text\":\"" + fd->picTextPairs[x][1] + "\"},\n\n";
	}
	JsonStr += "\t\t{\"picture\":\"" + fd->picTextPairs[pairs-1][0] + "\",\n" +
					"\t\t \"text\":\"" + fd->picTextPairs[pairs-1][1] + "\"}\n\n";
	
	//footer
	JsonStr += (string)"\t],\n" + 
				"\t\"footer\":\"" + fd->footer + "\"\n" +
				"}\n";
	
	return JsonStr;		
}

/*displays the contents of a randomly chosen file 
	within the given range of filenames*/
void displayRandomFile(const string * filenames, int fileNums)
{
	int min = 0, max = fileNums-1;
	srand ( time(0) );
	int num = ( rand() % (max - (min - 1)) ) + min;
	string file = filenames[num];
	cout << "\n********The contents of " << "\"" << file << "\"********\n\n";
	ifstream inFile;
	inFile.open( file.c_str() );
	string line;
	while (getline(inFile, line))
		cout << line << endl;
}

/*Arguments: string of four 0s and 1s in Twos Compliment
Return: int equivalent of given binary string*/
int binaryToInt(string str)
{
	int num = 0;
	
	//input handling
	if ( str.length() > 4 )
	{
		cout << "\nerror: Binary string must be exactly four digits long.\n";
		exit(1);
	}
	for (int x = 0; x < str.length(); x++)
	{
		if ( !isdigit(str[x]) && (str[x] != '0' || str[x] != '1') )
		{
			cout << "\nerror: Input must contain only 0s and 1s.\n";
			exit(1);
		}
	}
	
	int digit;
	bool neg = false;
	int arr[] = {0, 4, 2, 1};
	if (str[0] == '1')
	{
		neg = true;
		//flip bits
		for (int x = 0; x < str.length(); x++)
		{
			str[x] = (str[x]=='0')?'1':'0';
		}
		//add 1 to the binary string
		bool carry = true;
		for (int x = str.length()-1; x > 0 && carry; x--)
		{
			if (str[x]=='1')
			{
				str[x] = '0';
			}
			else
			{
				carry = false;
				str[x] = '1';
			}
		}
	}
	//do the binary additions
	for (int x = 0; x < str.length(); x++)
	{
		//implicit cast from char to int
		digit = str[x] - '0';
		if (digit == 1) num += arr[x];
		//cout << "digit: " << digit << endl;
		//cout << "num: " << num << endl;
	}
	if (neg) return -num;
	else return num;
}

void printHelp()
{
	cout << "\n*******Usage: ./final <file1>.txt (<file2>.txt...)"	<< endl;
	cout << "\nThis will parse the given file(s) and create json files containing their data." << endl;
	cout << "For example, given filename story1.txt, this will produce story1.json in the working directory." << endl;
	cout << "\nEach input file must end in .txt" << endl;
	cout << (string)"The expected format of each DocuWiki input file, <story>.txt, is as follows:\n" +
		"====== Title ======\n\n" +

		"{{dir:subdir:...pic1.jpg}}\n\n" +

		"Test corresponding to above picture link.\n\n" +

		"{{dir:subdir:...pic2.jpg}}\n\n" +

		"Test corresponding to above picture link.\n" +
		"...and so on, to the end of the story, followed by...\n\n" +

		"//footer text//" << endl << endl;
	exit(0);
}
