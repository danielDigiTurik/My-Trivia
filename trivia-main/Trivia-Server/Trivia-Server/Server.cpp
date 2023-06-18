#include "Server.h"

void Server::run()
{
	std::string exitStr = "";
	std::thread t_connector(&Communicator::startHandleRequests, this->m_communicator);
	t_connector.detach();

	while (exitStr != EXIT_CONDITION)
	{
		std::cin >> exitStr;
	}
	std::cout << "EXIT" << std::endl;
}