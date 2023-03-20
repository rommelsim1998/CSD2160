#pragma once
#include <string>
#include <stdio.h>
#include <iostream>
#include <array>
#include <WS2tcpip.h>

static unsigned char connectClients;
static std::array<sockaddr_in, 2> clientAddresses;
const int MTU = 1000;
static bool is2PlayersConnected;

class System
{
public:
	enum TYPE
	{
		SERVER = 0,
		CLIENT
	};
	static SOCKET m_sendSocket;
	static SOCKET m_recvSocket;
	static sockaddr_in m_serverAddr;
	static char m_buffer[MTU];
	TYPE m_type;
	virtual void Init(const std::string& _ipAddress, unsigned short _portNumber) {}
	virtual void Send(void* buffer, size_t len, const std::string& ip, unsigned short port) {}
	virtual void Recieve(void* buffer, size_t len, const std::string& ip, unsigned short port) {}
	virtual void Update() {}
};

class Server : public System
{
public:
	void Init(const std::string& _ipAddress, unsigned short _portNumber);
	void Update();
};

class Client : public System
{
public:
	void Init(const std::string& _ipAddress, unsigned short _portNumber);
	void Update();
};