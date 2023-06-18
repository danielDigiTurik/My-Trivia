#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializelLoginRequest(std::vector<unsigned char> buffer)
{
	LoginRequest login_request;
	std::string string_data;

	for (int i = 0; i < buffer.size(); i++)
	{
		string_data += buffer[i];
	}
	std::cout << string_data << std::endl;
	try
	{
		auto j = json::parse(string_data);
		std::string data = j.dump();
		json::iterator it = j.begin();
		login_request.username = it.value();
		it++;
		login_request.password = it.value();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
		exit(-1);
	}

	return login_request;
}
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
	SignupRequest signup_request;
	std::string string_data;

	for (int i = 0; i < buffer.size(); i++)
	{
		string_data += buffer[i];
	}
	std::cout << string_data << std::endl;
	try
	{
		auto j = json::parse(string_data);
		std::string data = j.dump();
		json::iterator it = j.begin();
		signup_request.username = it.value();
		it++;
		signup_request.password = it.value();
		it++;
		signup_request.email = it.value();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
		exit(-1);
	}

	return signup_request;
}