#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "JsonResponsePacketSerializer.h"

typedef struct LoginRequest
{
	std::string username;
	std::string password;
}LoginRequest;

typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
}SignupRequest;

class JsonRequestPacketDeserializer
{

public:
	static LoginRequest deserializelLoginRequest(std::vector<unsigned char>);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned char>);
};

