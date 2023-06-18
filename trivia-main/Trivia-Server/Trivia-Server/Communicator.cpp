#include "Communicator.h"
#include "JsonResponsePacketSerializer.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"

Communicator::Communicator()
{
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
}

Communicator::~Communicator()
{
	try
	{
		closesocket(m_serverSocket);
	}
	catch (...) {}
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;

	if (bind(m_serverSocket, (struct sockaddr*) & sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	std::cout << "Binded" << std::endl;

	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening to port: " << PORT << std::endl;

	while (true)
	{
		std::cout << "accepting client..." << std::endl;
		accept();
	}
}

void Communicator::accept()
{
	SOCKET client_socket = ::accept(m_serverSocket, NULL, NULL);

	RequestHandlerFactory factory;

	IRequestHandler* login = factory.createLoginRequestHandler();
	m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, login));
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted!" << std::endl;

	std::thread clientThread(&Communicator::handleNewClient, this, client_socket);
	clientThread.detach();
}

void Communicator::handleNewClient(SOCKET client_socket)
{
	bool run = true;

	while (run)
	{
		char header[HEADER_SIZE] = { 0 };
		char* data = nullptr;
		int size = 0;
		std::string string_data = "";
		recv(client_socket, header, HEADER_SIZE, 0);
		for (int i = 1; i < HEADER_SIZE; i++)
		{
			string_data += header[i];
		}
		size = atoi(string_data.c_str());

		data = new char[size];
		recv(client_socket, data, size, 0);

		RequestInfo request;

		std::vector<unsigned char> vector_data;
		std::vector<unsigned char> buffer;

		for (int i = 0; i < size; i++)
		{
			vector_data.push_back(data[i]);
		}
		for (int i = 0; i < size; i++)
		{
			buffer.push_back(data[i]);
		}

		request.buf = buffer;
		time_t now = time(0);
		request.receivalTime = now;
		request.id = header[0] - 48;

		try
		{
			RequestResult result = m_clients.at(client_socket)->handleRequest(request);
			std::string resultStr(result.response.begin(), result.response.end());

			if (send(client_socket, resultStr.c_str(), result.response.size(), 0) == INVALID_SOCKET)
			{
				std::cout << "ERROR INVALID SOCKET" << std::endl;
				run = false;
			}
			else
			{
				m_clients[client_socket] = result.newHandler;
			}
		}
		catch (std::string e)
		{
			std::cout << "Message: " << e << std::endl;
			ErrorResponse error;
			error._message = e;

			std::vector<unsigned char> errorVec = JsonResponsePacketSerializer::serializeResponse(error);
			std::string errorStr(errorVec.begin(), errorVec.end());
			send(client_socket, errorStr.c_str(), errorStr.size(), 0);
		}
		catch (std::exception e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
}

void Communicator::startHandleRequests()
{
	this->bindAndListen();
}