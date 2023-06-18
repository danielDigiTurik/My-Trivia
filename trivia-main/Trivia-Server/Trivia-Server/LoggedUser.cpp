#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string user)
{
	this->_username = user;
}

std::string LoggedUser::getUserName()
{
	return this->_username;
}

bool LoggedUser::operator==(const LoggedUser& other)
{
    if (this->_username == other._username)
    {
        return true;
    }
    else
    {
        return false;
    }
}