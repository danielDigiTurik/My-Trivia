#include "LoginManager.h"

std::vector<LoggedUser> LoginManager::_loggedUsers;

void LoginManager::signup(std::string username, std::string pass, std::string email)
{
    SqliteDatabase _db = SqliteDatabase();
    if (!_db.doesUserExist(username))//if user doesn't exist
    {
        _db.addNewUser(username, pass, email);//add user
        LoggedUser user = LoggedUser(username);
        this->_loggedUsers.push_back(user);//adds to users
        std::cout << "user added" << std::endl;
    }
    else
        throw std::string("user already exists");
}

void LoginManager::login(std::string username, std::string pass)
{
    SqliteDatabase _db = SqliteDatabase();
    if (_db.doesUserExist(username))//checks if user exists
    {
        if (_db.doesPasswordMatch(username, pass))//checks password
        {
            std::vector<LoggedUser>::iterator userIt = find(_loggedUsers.begin(), _loggedUsers.end(), username);
            if (userIt == _loggedUsers.end())
            {
                this->_loggedUsers.push_back(LoggedUser(username));//adds to logged user
                std::cout << "logged" << std::endl;
            }
            else
                throw std::string("user already logged in");
        }
        else
            throw std::string("password not match");
    }
    else
        throw std::string("user does not exist");
}

void LoginManager::logout(std::string username)
{

    std::vector<LoggedUser>::iterator userIt = find(_loggedUsers.begin(), _loggedUsers.end(), username);

    if (userIt != _loggedUsers.end())
    {
        std::cout << "consider it done. he has been erased" << std::endl;
        this->_loggedUsers.erase(userIt);
    }
    else
    {
        throw std::string("This user is not logged");
    }
}