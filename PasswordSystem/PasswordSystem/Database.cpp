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
        if (lineCount % 3 == 0) 
        {
            user.name = line;
        }
        else if (lineCount % 3 == 1)
        {
            user.password = decode(line);
        }
        else
        {
            user.first_login = line == "1";
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
        ofs << encode(userData[i].password).c_str() << std::endl;

        if(userData[i].first_login)
            ofs << "1" << std::endl;
        else ofs << "0" << std::endl;
    }

    ofs.close();
}

void Database::Register(const User& user)
{
    for (int i = 0; i < userData.size(); i++)
    {
        if (userData[i].name == user.name)
        {
            std::cout << "Error: user with the same name is already registered!\n";
            return;
        }
    }

    if (VerifyPassword(user))
    {
        userData.push_back(user);
        std::cout << "REGISTERED SUCCESFULLY!\n";
    }
    else
    {
        std::cout << "Error: [Register] Password has 2+ groups of 2 or 3+ duplicate symbols in a row!\n";
    }
}

void Database::Login(const User& user)
{
    for (int i = 0; i < userData.size(); i++)
    {
        if (userData[i].name == user.name && userData[i].password == user.password)
        {
            if (userData[i].first_login)
            {
                std::cout << "YOU MUST CHANGE PASSWORD AFTER FIRST LOGIN!\n";
                std::cout << "Enter New Password: ";

                User copy = user;
                std::string old_pass = copy.password;
                std::cin >> copy.password;

                if(ChangePassword(copy, old_pass))
                {
                    std::cout << "LOGGED IN SUCCESFULLY!\n";
                    userData[i].first_login = false;
                }
                else std::cout << "Logging in failed!\n";
            }
            else std::cout << "LOGGED IN SUCCESFULLY!\n";

            return;
        }
    }

    std::cout << "Error: [Login] Username not found or Password is wrong\n";
}

bool Database::ChangePassword(const User& user, const std::string& old_password)
{
    for (int i = 0; i < userData.size(); i++)
    {
        if (userData[i].name == user.name && userData[i].password == old_password)
        {
            if (VerifyPassword(user))
            {
                userData[i].password = user.password;
                std::cout << "CHANGED PASSWORD SUCCESFULLY!\n";
                return true;
            }
            else
            {
                std::cout << "Error: [ChangePassword] Password has 3+ duplicate symbols in a row!\n";
                return false;
            }
        }
    }

    std::cout << "Error: [ChangePassword] User with this name and password not found!\n";
    return false;
}

bool Database::VerifyPassword(const User& user)
{
    int size = user.password.size();
    int max_in_a_row = 0;
    int double_groups = 0;

    for (int i = 0; i < size; i++)
    {
        char symbol = user.password[i];
        int in_a_row = 0;

        for (int k = i; k < size; k++)
        {
            if (symbol == user.password[k])
            {
                in_a_row++;
            }
            else break;
        }

        if(in_a_row == 2)
        double_groups++;

        if (in_a_row > max_in_a_row)
        {
            max_in_a_row = in_a_row;
        }
    }

    std::cout << "[ChangePassword] max symbols in a row: " << max_in_a_row << "\n";

    return double_groups <= 1 && max_in_a_row < 3;
}

void Database::PrintData()
{
    for (int i = 0; i < userData.size(); i++)
    {
        std::cout << "Name: " << userData[i].name << " " << "Password: " << userData[i].password;
        if(userData[i].first_login) std::cout << "FirstLogin: YES" << std::endl;
        else std::cout << "FirstLogin: NO" << std::endl;
    }
}

std::string Database::encode(const std::string& str)
{
    std::string res = str;

    for (int i = 0; i < res.size(); i++)
    {
        res[i] = char((int)res[i] + 1);
    }

    return res;
}

std::string Database::decode(const std::string& str)
{
    std::string res = str;

    for (int i = 0; i < res.size(); i++)
    {
        res[i] = char((int)res[i] - 1);
    }

    return res;
}
