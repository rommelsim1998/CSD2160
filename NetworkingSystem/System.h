#pragma once

#include <string>
#include <stdio.h>
#include <iostream>
#include <array>
#include <vector>
#include <WS2tcpip.h>

//static std::array<sockaddr_in, 2> clientAddresses;
const int MTU = 1000;
static int connectedClient = 0;
static bool playersConnected2;

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
	static char m_buffer_game[MTU];

	static char m_buffer_send[MTU];
	static char m_buffer_recieve[MTU];

	static std::vector<sockaddr_in> clientAddresses;
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
	void Send(void* buffer, int len);
	static Server& getInstance()
	{
		static Server _instance;
		return _instance;
	}

	// use this to read from client
	int GetPlayers();
	void Read(int& x1, int& y1, int& x2, int& y2);
	void Send(int& x1, int& y1, int& x2, int& y2);
	void SendClientID(int& id);
	void SendFlagFor2Players(bool& flag);
};

class Client : public System
{
public:
	void Init(const std::string& _ipAddress, unsigned short _portNumber);
	void Update();
	void Send(void* buffer, int len);
	
	void Read(int& value);				// read bool
	void Read(float& x, float& y);
	static Client& getInstance()
	{
		static Client _instance;
		return _instance;
	}
	
	// use this to send to server
	void Send(int& x1, int& y1, int& x2, int& y2);
	void Read(int& x1, int& y1, int& x2, int& y2);
	int GetClientId();
	bool WaitFor2Players();
};

//static std::unique_ptr<Client> ClientHandle;
//static std::unique_ptr<Server> ServerHandle;
