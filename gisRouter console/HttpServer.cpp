#include "HttpServer.h"

Router::IO::HttpServer::HttpServer(int port)
{
	WSADATA wsadata = { 0 };
	memset(&this->_addrin, 0, sizeof this->_addrin);

	this->_rqSocket = INVALID_SOCKET;

	this->_addrin.sin_port = htons(port);
	this->_addrin.sin_addr.s_addr = 0;
	this->_addrin.sin_family = AF_INET;

	WSAStartup(MAKEWORD(2, 2), &wsadata);

	this->_listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(this->_listener, (sockaddr*)&this->_addrin, sizeof this->_addrin);
	listen(this->_listener, SOMAXCONN);

}

Router::IO::HttpServer::~HttpServer()
{
	closesocket(this->_listener);
	WSACleanup();
}

void Router::IO::HttpServer::Start()
{

}

bool Router::IO::HttpServer::WaitRequest()
{
	if (this->_rqSocket != INVALID_SOCKET)
	{
		closesocket(this->_rqSocket);
		this->_connectedSockets.erase(this->_rqSocket);
	}
	
	for (;;)
	{
		fd_set fds = { 0 };
		FD_SET(this->_listener, &fds);
		for (auto connectedSocket : this->_connectedSockets)
			FD_SET(connectedSocket, &fds);
		if (SOCKET_ERROR == select(0, &fds, NULL, NULL, NULL))
			throw std::exception(std::string("SOCKET ERROR: select error ->" + std::to_string(WSAGetLastError())).c_str());

		if (FD_ISSET(this->_listener, &fds))
			this->_connectedSockets.insert(accept(this->_listener, NULL, NULL));

		for (auto cl : this->_connectedSockets)
			if (FD_ISSET(cl, &fds))
			{
				this->_rqSocket = cl;
				return true;
			}
	}
	return false;
}

std::string Router::IO::HttpServer::GetRequest()
{
	constexpr auto buf_sz = 1024 * 1024;
	std::shared_ptr<char> buffer(new char[buf_sz]);
	int rcv_sz = recv(this->_rqSocket, buffer.get(), buf_sz, 0);
	if (rcv_sz < 0)
		throw std::exception(std::string("SOCKET ERROR: select error ->" + std::to_string(WSAGetLastError())).c_str());
	std::string rq(buffer.get(), buffer.get() + rcv_sz);
	auto find = rq.find("\r\n\r\n");
	if (find != rq.npos)
		return std::string(rq.begin() + find + 4, rq.end());
	return std::string();
}

void Router::IO::HttpServer::SendResponse(const std::string& response)
{

	std::stringstream ss;
	ss
		<< "HTTP/1.1 200 OK\n"
		<< "Content-Length: " << response.size()
		<< "\n\n"
		<< response;
	send(this->_rqSocket, ss.str().c_str(), ss.str().size() , 0);
}

