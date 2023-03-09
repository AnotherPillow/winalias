// winalias.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <lmcons.h>
using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
	//string alias = "test";
	//string command = "echo hello world lol";

	

	
	
	
	if (argc < 3) {
		printf("Please provide a alias and a command!");
		return 0;
	}
	/*for (int i = 0; i < argc; i++)
	{
		printf("arg %d: %s\n", i, argv[i]);
	}*/

	string alias = argv[1];
	string command = argv[2];

	
	TCHAR username[UNLEN + 1];
	DWORD size = UNLEN + 1;
	GetUserName((TCHAR*)username, &size);

	//convert username from TCHAR[257] to string
	string username_str = "";
	for (int i = 0; i < UNLEN + 1; i++)
	{
		if (username[i] == '\0') break;
		username_str += username[i];
	}
	
	string appdata = "C:\\Users\\" + username_str + "\\AppData\\Roaming";
	string winalias_path = string(appdata) + "\\winalias";

	//printf("appdata: %s\n", appdata.c_str());

	string* aliases = new string[0];
	for (const auto& entry : fs::directory_iterator(winalias_path))
	{
		//printf("%s
		//add to aliases
		string* temp = new string[1];
		temp[0] = entry.path().string();
		aliases = temp;
	}

	//write fileData to file.bat
	string fileData = "@echo off\n" + command;
	string path = winalias_path + "\\" + alias + ".bat";
	ofstream file(path);
	file << fileData;
	file.close();

	printf("Created alias %s for command %s", alias.c_str(), command.c_str());
	
		

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
