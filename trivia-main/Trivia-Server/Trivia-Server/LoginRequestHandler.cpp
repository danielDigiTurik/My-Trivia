#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler()
{
    this->m_handlerFactory = new RequestHandlerFactory();
    this->m_loginManager = new LoginManager();
}

LoginRequestHandler::~LoginRequestHandler()
{
    delete m_handlerFactory;
    delete m_loginManager;
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
    if (request.id == LOGIN_ID || request.id == SIGNUP_ID)
    {
        return true;
    }
    else
    {
        return false;
    }
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo request)
{
    RequestResult result;
    if (!isRequestRelevant(request))
    {
        result.response;
        return result;
    }

    if (request.id == LOGIN_ID)
    {
        return login(request);
    }
    else
    {
        return signup(request);
    }

}

RequestResult LoginRequestHandler::login(RequestInfo request)
{
    RequestResult result;
    LoginRequest logReq = JsonRequestPacketDeserializer::deserializelLoginRequest(request.buf);
    LoginResponse response;
    response.status = 1;
    result.newHandler = new NewClient;
    result.response = JsonResponsePacketSerializer::serializeResponse(response);
    m_loginManager->login(logReq.username, logReq.password);
    return result;
}

RequestResult LoginRequestHandler::signup(RequestInfo request)
{
    RequestResult result;
    SignupRequest signReq = JsonRequestPacketDeserializer::deserializeSignupRequest(request.buf);
    SignupResponse response;
    response.status = 2;
    result.newHandler = new NewClient;
    result.response = JsonResponsePacketSerializer::serializeResponse(response);
    m_loginManager->signup(signReq.username, signReq.password, signReq.email);
    return result;
}

bool NewClient::isRequestRelevant(RequestInfo request)
{
    return true;
}

RequestResult NewClient::handleRequest(RequestInfo request)
{
    RequestResult result;
    return result;
}