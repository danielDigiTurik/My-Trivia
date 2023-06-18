#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

#define ERROR_STATUS '0'
#define LOGIN_STATUS '1'
#define SIGNUP_STATUS '2'

typedef struct ErrorResponse
{
	std::string _message;
}ErrorResponse;

typedef struct LoginResponse
{
	unsigned int status;
}LoginResponse;

typedef struct SignupResponse
{
	unsigned int status;
}SignupResponse;

class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse error);
	static std::vector<unsigned char> serializeResponse(LoginResponse login);
	static std::vector<unsigned char> serializeResponse(SignupResponse signup);

private:
	static void intToBytes(std::vector<unsigned char>& buffer, std::string size);
};