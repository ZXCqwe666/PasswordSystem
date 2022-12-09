#pragma once

#include <iostream>
#include <vector>
#include <string>

struct User
{
	std::string name;
	std::string password;
	bool first_login = true;
};

class Database
{
private:
	std::vector<User> userData;

public: 
	void Init(const std::string& filepath);
	void SaveChanges(const std::string& filepath);

	void Register(const User& user);
	void Login(const User& user);
	bool ChangePassword(const User& user, const std::string& old_password);
	bool VerifyPassword(const User& user);

	void PrintData();

	std::string encode(const std::string& str);
	std::string decode(const std::string& str);
};
