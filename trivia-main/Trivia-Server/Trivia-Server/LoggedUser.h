#pragma once
#include <string>
#include <iostream>

class LoggedUser
{
private:
	std::string _username;

public:
	LoggedUser(std::string);
	std::string getUserName();
	bool operator==(const LoggedUser& other);
};