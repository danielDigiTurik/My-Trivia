#include "JsonResponsePacketSerializer.h"

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse error)
{
	json j;
	j["message"] = error._message;
	std::vector<unsigned char> buffer;
	std::string message = j.dump();
	std::string msgSize = std::to_string(message.length());

	buffer.push_back(ERROR_STATUS);
	intToBytes(buffer, msgSize);
	for (int i = 0; i < message.length(); i++)
	{
		buffer.push_back(message[i]);
	}

	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse login)
{
	json j;
	j["status"] = login.status;
	std::vector<unsigned char> buffer;
	std::string message = j.dump();
	std::string msgSize = std::to_string(message.length());

	buffer.push_back(LOGIN_STATUS);
	intToBytes(buffer, msgSize);
	for (int i = 0; i < message.length(); i++)
	{
		buffer.push_back(message[i]);
	}

	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse signup)
{
	json j;
	j["status"] = signup.status;
	std::vector<unsigned char> buffer;
	std::string message = j.dump();
	std::string msgSize = std::to_string(message.length());

	buffer.push_back(SIGNUP_STATUS);
	intToBytes(buffer, msgSize);
	for (int i = 0; i < message.length(); i++)
	{
		buffer.push_back(message[i]);
	}

	return buffer;
}

void JsonResponsePacketSerializer::intToBytes(std::vector<unsigned char>& buffer, std::string size)
{
	for (int i = 0; i < 4 - size.length(); i++)
	{
		buffer.push_back('0');
	}

	for (int i = 0; i < size.length(); i++)
	{
		buffer.push_back(size[i]);
	}
}
