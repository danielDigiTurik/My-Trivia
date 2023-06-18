#pragma once
#include <string>
#include <iostream>
#include "sqlite3.h"

class IDatabase
{
public:
	virtual bool doesUserExist(std::string) = 0;
	virtual bool doesPasswordMatch(std::string, std::string) = 0;
	virtual void addNewUser(std::string, std::string, std::string) = 0;
};