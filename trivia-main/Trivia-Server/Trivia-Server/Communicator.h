#pragma once
#include "WSAInitializer.h"
#include "IRequestHandler.h"
#include <iostream>
#include <thread>
#include <string>
#include <map>

#define PORT 8826
#define HEADER_SIZE 5

class Communicator
{
public:

	Communicator();
	~Communicator();
	
	void startHandleRequests();

private:

	SOCKET m_serverSocket;
	std::map <SOCKET, IRequestHandler*> m_clients;
	void bindAndListen();
	void handleNewClient(SOCKET);
	void accept();
};