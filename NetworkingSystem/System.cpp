#pragma once
#include "System.h"

SOCKET System::m_sendSocket;
SOCKET System::m_recvSocket;
sockaddr_in System::m_serverAddr;
//int connectClients = 1;
//bool playersConnected2 = false;
char System::m_buffer[MTU];


void Server::Init(const std::string& _ipAddress, unsigned short _portNumber)
{
	std::cout << "[Server]: Initializing WSA and server information" << std::endl;

	//! Initialize WSA
	WSADATA wsaData{};
	int wsaErr{ WSAStartup(MAKEWORD(2, 2), &wsaData) };
	if (wsaErr)
	{
		std::cerr << "[Server]: WSAStartup() error: " << wsaErr << std::endl;
		WSACleanup();
		std::exit(EXIT_FAILURE);
	}

	// Create listenitng socket
	m_recvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_recvSocket == INVALID_SOCKET)
	{
		std::cerr << "[Server]: socket() error: " << WSAGetLastError() << std::endl;
		closesocket(m_recvSocket);
		WSACleanup();
		std::exit(EXIT_FAILURE);
	}
	std::cout << "[Server]: Created Server socket.\n";

	//! Create hint structure for server information
	m_serverAddr.sin_family = AF_INET;					//IPv4
	m_serverAddr.sin_port = htons(54000);				// Port number
	m_serverAddr.sin_addr.S_un.S_addr = ADDR_ANY;		// ip
	//inet_pton(AF_INET, _ipAddress.c_str(), &m_serverAddr.sin_addr); // IP Address

	//! Bind socket to IP and port
	if (bind(m_recvSocket, reinterpret_cast<SOCKADDR*>(&m_serverAddr), sizeof(m_serverAddr)) == SOCKET_ERROR)
	{
		std::cout << "[Server]: bind() error: " << WSAGetLastError() << std::endl;
		closesocket(m_recvSocket);
		WSACleanup();
		std::exit(EXIT_FAILURE);
	}

	unsigned long mode{ 1 };
	ioctlsocket(m_recvSocket, FIONBIO, &mode);
}

void Server::Update()
{
	//std::cout << "[Server]: " << connectClients << std::endl;
	std::memset(&m_buffer, 0, MTU);
	sockaddr_in newClientAddress;
	int newClientAddress_size = sizeof(newClientAddress);
	std::memset(&newClientAddress, 0, newClientAddress_size);

	int BytesRecieved = recvfrom(m_recvSocket, m_buffer, MTU, 0, reinterpret_cast<SOCKADDR*>(&newClientAddress), &newClientAddress_size);
	if (BytesRecieved == SOCKET_ERROR)
	{
		int wsaError{ WSAGetLastError() };
		if (wsaError != WSAEWOULDBLOCK)
			std::cerr << "[Server]: Error recvfrom: " << WSAGetLastError() << std::endl;
	}
	else
	{
		std::cout << "[Server]: " << BytesRecieved << " bytes received. Message is: " << m_buffer << std::endl;
		for (auto& clients : clientAddresses)
		{
			if (clients.sin_addr.S_un.S_addr == newClientAddress.sin_addr.S_un.S_addr) return;
		}

		for (auto& client : clientAddresses)
		{
			if (client.sin_addr.S_un.S_addr == 0)
			{
				++connectedClient;

				client = newClientAddress;
				std::cout << "[Server]: New client added\n";
				break;
			}
		}

		for (int i = 0; i < clientAddresses.size(); ++i)
		{
			if (clientAddresses[i].sin_addr.S_un.S_addr == 0)
				continue;

			char clientMsg[MTU] = "[Server]: Welcome new player!\n";
			sendto(m_recvSocket, clientMsg, MTU, 0, reinterpret_cast<SOCKADDR*>(&clientAddresses[i]), sizeof(clientAddresses[i]));

		}
	}

	char clientIP[256];
	inet_ntop(AF_INET, &newClientAddress.sin_addr, clientIP, 256);
}

void Server::Send(void* buffer, int len)
{

	for (int i = 0; i < clientAddresses.size(); ++i)
	{
		if (clientAddresses[i].sin_addr.S_un.S_addr == 0)
			continue;

		sendto(m_recvSocket, (const char*)buffer, MTU, 0, reinterpret_cast<SOCKADDR*>(&clientAddresses[i]), sizeof(clientAddresses[i]));
		std::cout << "[Server]: Sending " << len << " bytes of data to " << clientAddresses[i].sin_addr.S_un.S_addr << std::endl;
	}
	//sendto(m_sendSocket, (const char*)buffer, len, 0, reinterpret_cast<SOCKADDR*>(&m_serverAddr), sizeof(m_serverAddr));
}

void Client::Init(const std::string& _ipAddress, unsigned short _portNumber)
{
	std::cout << "[Client]: Initializing WSA and server informationdddd" << std::endl;
	//! Initialize WSA
	WSADATA wsaData{};
	int wsaErr{ WSAStartup(MAKEWORD(2, 2), &wsaData) };
	if (wsaErr)
	{
		std::cerr << "[Client]: WSAStartup() error: " << wsaErr << std::endl;
		WSACleanup();
		std::exit(EXIT_FAILURE);
	}

	//! Create sending socket
	m_sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_sendSocket == INVALID_SOCKET)
	{
		std::cerr << "[Client]: socket() error: " << WSAGetLastError() << std::endl;
		closesocket(m_sendSocket);
		WSACleanup();
		std::exit(EXIT_FAILURE);
	}

	//! Set socket as non blocking for receiving from server
	unsigned long mode{ 1 };
	ioctlsocket(m_sendSocket, FIONBIO, &mode);

	//! Create hint structure for server information
	m_serverAddr.sin_family = AF_INET; //IPv4
	m_serverAddr.sin_port = htons(_portNumber); // Port number
	inet_pton(AF_INET, _ipAddress.c_str(), &m_serverAddr.sin_addr); // IP Address

	// must be 0!
	int sendresult{ sendto(m_sendSocket, m_buffer, MTU, 0, reinterpret_cast<SOCKADDR*>(&m_serverAddr), sizeof(m_serverAddr)) };
	if (sendresult == SOCKET_ERROR)
	{
		std::cerr << "[Client]: Sendto() error: " << WSAGetLastError() << std::endl;
		closesocket(m_sendSocket);
		WSACleanup();
		std::exit(EXIT_FAILURE);
	}
}

void Client::Update()
{
	std::memset(m_buffer, 0, MTU);
	int bytes = recvfrom(m_sendSocket, m_buffer, MTU, 0, nullptr, nullptr);
	if (bytes == SOCKET_ERROR)
	{
		int wsaErr{ WSAGetLastError() };
		if(wsaErr != WSAEWOULDBLOCK)
			std::cerr << "[Client]: error: " << wsaErr << std::endl;
	}
	else
	{
		std::cout << "[Client]: Receiving " << bytes << " of data. Message is: " << m_buffer << std::endl;
	}
}

void Client::Send(void* buffer, int len)
{
	sendto(m_sendSocket, (const char*)buffer, len, 0, reinterpret_cast<SOCKADDR*>(&m_serverAddr), sizeof(m_serverAddr));
	std::cout << "[Client]: Sending " << len << " bytes of data\n";

}

