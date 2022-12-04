#include <iostream>

#include "Database.h"

void help()
{
	std::cout << "\n";
	std::cout << "Commands: \n";
	std::cout << "help - see list of all commands \n";
	std::cout << "register - register new user \n";
	std::cout << "login - login as user \n";
	std::cout << "changepass - change password \n";
	std::cout << "print - print user data \n";
	std::cout << "exit - close the program \n";
	std::cout << "\n";
}

int main()
{
	help();

	Database database;
	database.Init("data.txt");
	
	bool run = true;

	while (run)
	{
		std::cout << "\n";
		std::string command;
		std::cin >> command;

		if (command == "register")
		{
			User new_user;
			std::cout << "Enter Name: ";
			std::cin >> new_user.name;
			std::cout << "Enter Password: ";
			std::cin >> new_user.password;

			database.Register(new_user);
		}

		if (command == "login")
		{
			User new_user;
			std::cout << "Enter Name: ";
			std::cin >> new_user.name;
			std::cout << "Enter Password: ";
			std::cin >> new_user.password;

			database.Login(new_user);
		}

		if (command == "changepass")
		{
			User user;
			std::cout << "Enter Name: ";
			std::cin >> user.name;
			std::cout << "Enter Old Password: ";
			std::string old_password;
			std::cin >> old_password;
			std::cout << "Enter New Password: ";
			std::cin >> user.password;

			database.ChangePassword(user, old_password);
		}

		if (command == "help") help();
		if (command == "print") database.PrintData();
		if (command == "exit") run = false;
	}

	database.SaveChanges("data.txt");

	return 0;
}
