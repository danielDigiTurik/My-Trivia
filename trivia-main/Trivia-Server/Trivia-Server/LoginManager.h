#pragma once

#include <iostream>
#include "IDatabase.h"
#include "LoggedUser.h"
#include "SqliteDatabase.h"
#include <vector>
#include <iterator>

class LoginManager
{
private:
	static std::vector<LoggedUser> _loggedUsers;

public:
	void signup(std::string, std::string ,std::string);
	void login(std::string, std::string);
	void logout(std::string);
};

