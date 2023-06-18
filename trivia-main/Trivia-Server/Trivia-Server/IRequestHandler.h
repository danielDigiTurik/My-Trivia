#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

class IRequestHandler;

typedef struct RequestResult
{
	std::vector<unsigned char> response;
	IRequestHandler* newHandler;
}RequestResult;

typedef struct RequestInfo
{
	int id;
	time_t receivalTime;
	std::vector<unsigned char> buf;

}RequestInfo;

class IRequestHandler
{

public:
	virtual ~IRequestHandler() {};
	virtual bool isRequestRelevant(RequestInfo request) = 0;
	virtual RequestResult handleRequest(RequestInfo request) = 0;
};
