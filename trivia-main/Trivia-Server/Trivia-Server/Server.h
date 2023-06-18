#pragma once
#include "Communicator.h"
#include <iostream>
#include <thread>
#include "IDatabase.h"
#include "RequestHandlerFactory.h"

#define EXIT_CONDITION "exit"

class Server
{
public:
	void run();

private:
	Communicator m_communicator;
	IDatabase* m_database;
};