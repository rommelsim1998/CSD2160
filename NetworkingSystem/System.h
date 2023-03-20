#pragma once
#include <string>
#include <stdio.h>
#include <iostream>
#include <array>
#include <WS2tcpip.h>

static unsigned char connectClients;
static std::array<sockaddr_in, 2> clientAddresses;
const int MTU = 1000;

class System
{
public:
	enum TYPE
	{
		SERVER = 0,
		CLIENT
	};
	SOCKET m_sendSocket;
	SOCKET m_recvSocket;
	sockaddr_in m_serverAddr;
	char m_buffer[MTU];
	TYPE m_type;
	void Init(const std::string& _ipAddress, unsigned short _portNumber, TYPE _type);
	void Send(void* buffer, size_t len, const std::string& ip, unsigned short port);
	void Recieve(void* buffer, size_t len, const std::string& ip, unsigned short port);
	void Update();
};