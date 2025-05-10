#include "Core/HttpServer.h"
#include "defines.h"


int main() 
{
	Server::HTTPServer server(DEFAULT_PORT);
	server.Start();
	return 0;
}
