/*
	Author: Benjamin R. Olson
	Date: March 11, 2014
	Description: Test File input and output
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main (int argc, char * argv[])
{
	cout << "argv[0]: " << argv[0] << endl;
	cout << "argv[1]: " << argv[1] << endl;
	
	char *file = argv[1];
	cout << "file: " << file << endl;
	ifstream f;
	f.open(file);
	if (f.fail()) cout << "failed to open file" << endl;
	
	string str;
	
	while (getline(f, str))
	{
		if (str == "") continue;
		//getline(f, str);
		//cout << "line 29: str[str.length() - 1]:" << str[str.length() - 1] << endl;
		cout << str << endl;
	}
	cout << "str: " << str.length() << endl;
	
	
	getline(f, str);
	
	f.close();
	
	cout << endl;
	
	return 0;
}

