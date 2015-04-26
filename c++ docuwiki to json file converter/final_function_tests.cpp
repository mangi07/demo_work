/************************
* Author: Benjamin R. Olson
* Date: March 11, 2014
* Title: Final Project Function Tests, 
* 	DocuWiki to Json Parser
* Description: Converts a DocuWiki file of a
* 	specific format into a Json file
* Input: none
* Output: cout statements indicating
* 	function return values and
* 	post-conditions
*************************/
//while processing files, cout current file being processed so that
//	error messages will have a frame of reference

#include <iostream>
#include <cstdlib> //rand
#include <ctime> //time
#include <string>
#include <cstring>
#include <fstream>

using namespace std;


string stripSyntax(string textLine, int x, char c);
string docuToDir(string dir);
string stripSyntax(string textLine, int x1, char c1, char c2);
int countPicTextPairs (string filename);
void insertEscapeQuotes(string &str);

int main (int argc, char * argv[])
{
	/*
	//TEST string stripSyntax(string textLine, int x, char c)
	cout << "\tTest 1: stripSyntax(string textLine, int x, char c)" << endl;
	cout << stripSyntax("====== Title ======", 6, '=') << endl << endl;
	//expected return value: " Title "
	
	//cout << "\tTest 2: stripSyntax(string textLine, int x, char c)" << endl;
	//cout << stripSyntax("====== Title =====", 6, '=') << endl << endl;
	//expected: exits with error
	
	//cout << "\tTest 3: stripSyntax(string textLine, int x, char c)" << endl;
	//cout << stripSyntax("====== Title ======", 6, '/') << endl << endl;
	//expected: exits with error
	
	//cout << "\tTest 4: stripSyntax(string textLine, int x, char c)" << endl;
	//cout << stripSyntax("====== Title ======", 7, '=') << endl << endl;
	//expected: exits with error
	
	cout << "\tTest 5: stripSyntax(string textLine, int x, char c)" << endl;
	cout << stripSyntax("====== Title ======", 5, '=') << endl << endl;
	//expected return value: "= Title ="
	
	//TEST string docuToDir(string dir)
	string oldDir = ":dir:subdir:pic.jpg";
	string newDir = docuToDir(oldDir);
	cout << "\tTest1: string docuToDir(string dir)" << endl;
	cout << "oldDir: " << oldDir << endl;
	cout << "newDir: " << newDir << endl << endl;
	//expected return value: "/dir/subdir/pic.jpg"
	
	//TEST string stripSyntax(string textLine, int x, char c1, char c2)
	string oldStr = "{{:dir:subdir:pic.jpg}}";
	string newStr = stripSyntax(oldStr, 2, '{', '}');
	cout << "\tTest1: stripSyntax(string textLine, int x, char c1, char c2)" << endl;
	cout << "oldStr: " << oldStr << endl;
	cout << "newStr: " << newStr << endl << endl;
	//expected return value: ":dir:subdir:pic.jpg"
	
	string oldStr2 = "{{{:dir:subdir:pic.jpg}}";
	string newStr2 = stripSyntax(oldStr2, 2, '{', '}');
	cout << "\tTest2: stripSyntax(string textLine, int x, char c1, char c2)" << endl;
	cout << "oldStr2: " << oldStr2 << endl;
	cout << "newStr2: " << newStr2 << endl << endl;
	//expected return value: "{:dir:subdir:pic.jpg"
	
	string oldStr3 = "{:dir:subdir:pic.jpg}}";
	string newStr3 = stripSyntax(oldStr3, 2, '{', '}');
	cout << "\tTest3: stripSyntax(string textLine, int x, char c1, char c2)" << endl;
	cout << "oldStr3: " << oldStr3 << endl;
	cout << "newStr3: " << newStr3 << endl << endl;
	//expected: exits with error
	
	
	//TEST int countPicTextPairs (string filename)
	cout << "\tTest 1: int countPicTextPairs (string filename)" << endl;
	cout << countPicTextPairs ("01-the-creation.txt") << endl << endl;
	//expected return value: 16
	//	the number of times '{' appears as the first char of a line
	//	in the filename
	*/
	
	//TEST string insertEscapeQuotes(string str)
	string strIEQ = "He said, \"Hello there.\" Then I said, \"Hi to you.\"";
	cout << "strIEQ before function call: " << strIEQ << endl;
	insertEscapeQuotes(strIEQ);
	cout << "strIEQ: " << strIEQ << endl;
	
	return 0;
}

string stripSyntax(string textLine, int x, char c)
//returns textLine stripped of x char's on both ends
//	if there are at least x number of counsecutive same char's
//	on both ends of textLine...
//	otherwise exits the program with file syntax error message
{
	int len = textLine.length();
	char a = textLine[0];//first char
	char z = textLine[len - 1];//last char
	cout << "a: '" << a << "' and z: '" << z << "' and c: '" << c << "'"<< endl;
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

//pass by value
string docuToDir(string dir)
//returns dir with every occurrence of ':'
//	replaced with '/'
{
	for (int i = 0; i < dir.length(); i++)
	{
		if (dir[i] == ':')
			dir[i] = '/';	
	}
	return dir;
}

string stripSyntax(string textLine, int x, char c1, char c2)
		//returns textLine stripped of x consecutive same c1 char's on left side
		//	and x consecutive same c1 char's on right side of textLine
		//	otherwise exits the program with file syntax error message
		//	Example: arg: "{{dir:subdir:pic.jpg}}"
		//			return: "dir:subdir:pic.jpg"
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

int countPicTextPairs (string filename)
//Returns the number of lines starting with '{'
//	in file with filename
{
	ifstream f;
	const char *c = filename.c_str();
	f.open(c);
	
	if (f.fail())
	{
		cout << "error: Failed to open file: " << 
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

void insertEscapeQuotes(string &str)
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
