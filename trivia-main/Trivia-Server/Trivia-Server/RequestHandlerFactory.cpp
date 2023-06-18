#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    LoginRequestHandler* request = new LoginRequestHandler;
    return request;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return this->m_loginManager;
}