#include "HttpServer.h"
#include <iostream>
#include "HttpConnection.h"

Server::HTTPServer::HTTPServer(int _port)
{
	this->port = _port;
	serverSocket = INVALID_SOCKET;
	isRunning = false;

	WSAData wsaData;
	int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (wsaResult != 0)
	{
		std::cerr << "[httpServer] WSAStartup Failed : " << wsaResult << "\n";
		exit(1);
	}
}

Server::HTTPServer::~HTTPServer()
{
	Stop(serverSocket);
	WSACleanup();
}

void Server::HTTPServer::Start()
{
	SetupSockets();
	isRunning = true;
	acceptClients();
}

bool Server::HTTPServer::Stop(SOCKET ClientSocket)
{
	isRunning = false;
	if (serverSocket != INVALID_SOCKET)
	{
		closesocket(serverSocket);
		serverSocket = INVALID_SOCKET;
		return false;
	}
	return true;
}

void Server::HTTPServer::SetupSockets()
{
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		std::cerr << "[httpServer] Socket Creation Failed: " << WSAGetLastError() << "\n";
	}

	BOOL opt = TRUE;
	setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);

	if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		std::cerr << "[httpServer] Bind Failed: " << WSAGetLastError() << "\n";
		exit(1);
	}

	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cerr << "[httpServer] Listen Failed: " << WSAGetLastError() << "\n";
		exit(1);
	}

	std::cout << "Server listening on port : " << port << "\n";
}

void Server::HTTPServer::acceptClients()
{
	while (isRunning)
	{
		SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
		if (clientSocket == INVALID_SOCKET)
		{
			std::cerr << "[httpServer] Accept Failed: " << WSAGetLastError() << "\n";
			continue;
		}

		HTTPConnection connection(clientSocket);
		connection.handle();
	}
}
