#include <iostream>

#include "Database.h"

void help()
{
	std::cout << "\n";
	std::cout << "Commands: \n";
	std::cout << "help - see list of all commands \n";
	std::cout << "print - print user data \n";
	std::cout << "exit - close the program \n";
	std::cout << "\n";
}

int main()
{
	Database database;
	database.Init("data.txt");
	
	bool run = true;

	while (run)
	{
		std::string command;
		std::cin >> command;

		if (command == "help") help();
		if (command == "print") database.PrintData();
		if (command == "exit") run = false;
	}

	database.SaveChanges("data.txt");

	return 0;
}
