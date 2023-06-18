#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <map>
#include <string>
#include <io.h>

int callbackCheckPassword(void*, int, char**, char**);
int callbackDoesExist(void*, int, char**, char**);

class SqliteDatabase : public IDatabase
{
private:
    sqlite3* _db;

   

public:
    SqliteDatabase();

    bool doesUserExist(std::string) override;
    bool doesPasswordMatch(std::string, std::string) override;
    void addNewUser(std::string, std::string, std::string) override;

    
};