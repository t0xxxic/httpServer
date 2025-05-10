#pragma once

#include <winsock2.h>

namespace Server
{
	class HTTPConnection 
	{
	private:
		SOCKET clientSocket;
	public:
		HTTPConnection(SOCKET socket);
		~HTTPConnection();

		void handle();
	};
}