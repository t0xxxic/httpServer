#pragma once

#include <winsock2.h>
#include "defines.h"
#pragma comment(lib, "ws2_32.lib")

namespace Server
{
	class HTTPServer {
	public:
		HTTPServer(int _port);
		~HTTPServer();

		void Start();
		bool Stop(SOCKET ClientSocket);

	private:
		SOCKET serverSocket;
		int port;
		bool isRunning;

		void SetupSockets();
		void acceptClients();
	};

}