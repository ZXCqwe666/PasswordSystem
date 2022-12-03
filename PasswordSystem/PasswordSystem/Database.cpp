#include "Database.h"

#include <iostream>
#include <fstream>

void Database::Init(const std::string& filepath)
{
    std::ifstream file;
    file.open(filepath);

    std::string line;
    int lineCount = 0;
    User user;

    userData = std::vector<User>();

    while (std::getline(file, line))
    {
        if (lineCount % 2 == 0) user.name = line;
        else
        {
            user.password = line;
            userData.push_back(user);
        }   

        lineCount++;
    }

    file.close();
}

void Database::SaveChanges(const std::string& filepath)
{
    std::ofstream ofs;
    ofs.open(filepath, std::ofstream::out | std::ofstream::trunc);

    for (int i = 0; i < userData.size(); i++)
    {
        ofs << userData[i].name.c_str() << std::endl;
        ofs << userData[i].password.c_str() << std::endl;
    }

    ofs.close();
}

void Database::AddData(const User& user)
{
    userData.push_back(user);
}

void Database::ChangePassword(const std::string& name, const std::string& new_password)
{
    for (int i = 0; i < userData.size(); i++)
    {
        if (userData[i].name == name)
        {
            userData[i].password = new_password;
            return;
        }
    }
}

void Database::PrintData()
{
    for (int i = 0; i < userData.size(); i++)
    {
        std::cout << "Name: " << userData[i].name << " " << "Password: " << userData[i].password << std::endl;
    }
}
