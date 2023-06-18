#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#define LOGIN_ID 1
#define SIGNUP_ID 2

class LoginManager;
class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
    bool isRequestRelevant(RequestInfo request);
    RequestResult handleRequest(RequestInfo request);
    LoginRequestHandler();
private:
    ~LoginRequestHandler();

    RequestResult login(RequestInfo request);
    RequestResult signup(RequestInfo request);

    LoginManager* m_loginManager;
    RequestHandlerFactory* m_handlerFactory;
};

class NewClient : public IRequestHandler
{
public:
    bool isRequestRelevant(RequestInfo request);
    RequestResult handleRequest(RequestInfo request);
};