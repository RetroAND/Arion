// Arion.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <algorithm>
#include "dependencies/FloppyLib/include/FloppyLib.h"
#include "commands.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("ERROR: Not enough parameters supplied.");
		return 1;
	}
	string command = argv[1];
	transform(command.begin(), command.end(), command.begin(),[](unsigned char c) { return tolower(c); });
	string path = "";
	if (argc >= 3)
	{
		path = argv[2];
	}
	string savePath = "";
	if (argc >= 4)
	{
		savePath = argv[3];
	}
	if (command == "dir" || command == "ls")
	{
		dir(path);
	}
	else if (command == "statistics" || command == "stats")
	{
		statistics(path);
	}
	else if(command == "volume" || command == "vol")
	{
		volume(path);
	}
	else if (command == "extract-all" || command == "all")
	{
		extractAll(path, savePath);
	}
	else if (command == "help")
	{
		help();
	}
	else
	{
		printf("ERROR");
	}
	return 0;
}
