#pragma once

#include <WinSock2.h>
#include <sstream>
#include <set>
#include <memory>
namespace Router
{
	namespace IO
	{
		class HttpServer
		{
		public:
			HttpServer(int port);
			~HttpServer();
			void Start();
			bool WaitRequest();
			std::string GetRequest();
			void SendResponse(const std::string& response);
			
		private:
			sockaddr_in _addrin;
			SOCKET _listener;
			std::set<SOCKET> _connectedSockets;
			SOCKET _rqSocket;
		};
	}
}