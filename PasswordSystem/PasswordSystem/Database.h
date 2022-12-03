#pragma once

#include <iostream>
#include <vector>
#include <string>

struct User
{
	std::string name;
	std::string password;
};

class Database
{
private:
	std::vector<User> userData;

public: 
	void Init(const std::string& filepath);
	void SaveChanges(const std::string& filepath);

	void AddData(const User& user);
	void ChangePassword(const std::string& name, const std::string& new_password);

	void PrintData();
};