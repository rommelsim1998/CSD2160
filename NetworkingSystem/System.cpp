#pragma once
#include "System.h"

void System::Init(const std::string& _ipAddress, unsigned short _portNumber, TYPE _type)
{
	if (_type == TYPE::SERVER)
	{
		std::cout << "Initializing WSA and server information" << std::endl;

		//! Initialize WSA
		WSADATA wsaData{};
		int wsaErr{ WSAStartup(MAKEWORD(2, 2), &wsaData) };
		if (wsaErr)
		{
			std::cerr << "WSAStartup() error: " << wsaErr << std::endl;
			WSACleanup();
			std::exit(EXIT_FAILURE);
		}

		// Create listenitng socket
		m_recvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (m_recvSocket == INVALID_SOCKET)
		{
			std::cerr << "socket() error: " << WSAGetLastError() << std::endl;
			closesocket(m_recvSocket);
			WSACleanup();
			std::exit(EXIT_FAILURE);
		}
		std::cout << "Created Server socket.\n";

		//! Create hint structure for server information
		m_serverAddr.sin_family = AF_INET;					//IPv4
		m_serverAddr.sin_port = htons(54000);				// Port number
		m_serverAddr.sin_addr.S_un.S_addr = ADDR_ANY;		// ip
		//inet_pton(AF_INET, _ipAddress.c_str(), &m_serverAddr.sin_addr); // IP Address

		//! Bind socket to IP and port
		if (bind(m_recvSocket, reinterpret_cast<SOCKADDR*>(&m_serverAddr), sizeof(m_serverAddr)) == SOCKET_ERROR)
		{
			std::cout << "bind() error: " << WSAGetLastError() << std::endl;
			closesocket(m_recvSocket);
			WSACleanup();
			std::exit(EXIT_FAILURE);
		}
	}
	else if(_type == TYPE::CLIENT)
	{
		std::cout << "Initializing WSA and server information" << std::endl;
		//! Initialize WSA
		WSADATA wsaData{};
		int wsaErr{ WSAStartup(MAKEWORD(2, 2), &wsaData) };
		if (wsaErr)
		{
			std::cerr << "WSAStartup() error: " << wsaErr << std::endl;
			WSACleanup();
			std::exit(EXIT_FAILURE);
		}

		//! Create sending socket
		m_sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (m_sendSocket == INVALID_SOCKET)
		{
			std::cerr << "socket() error: " << WSAGetLastError() << std::endl;
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

		//! TESTING OF SENDING MESSAGE TO SERVER
		std::cout << "Sending message to server..." << std::endl;
		//if (!buffer) buffer = new char(1000);
		//std::memset(buffer, 0, 1000);
		//std::memcpy(buffer, "Hello!", 1000);

		//// Send buffer to server
		//Send(buffer, 1000, _ipAddress, _portNumber);
	}


}

void System::Send(void* buffer, size_t len, const std::string& ip, unsigned short port)
{
	sockaddr_in reciever{};
	reciever.sin_family = AF_INET;
	reciever.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &reciever.sin_addr);
	int send_result = sendto(m_sendSocket, (const char*)buffer, len, 0, reinterpret_cast<SOCKADDR*>(&reciever), sizeof(reciever));
	if (send_result == SOCKET_ERROR)
	{
		std::cerr << "sendto() error: " << WSAGetLastError() << std::endl;
		closesocket(m_sendSocket);
		WSACleanup();
		std::exit(EXIT_FAILURE);
	}
	std::cout << "Sent: " << buffer << std::endl;
}

void System::Recieve(void* buffer, size_t len, const std::string& ip, unsigned short port)
{
	std::memset(buffer, 0, len);
	
	sockaddr_in reciever{};
	reciever.sin_family = AF_INET;
	reciever.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &reciever.sin_addr);

	int bytesRecieved = recvfrom(m_sendSocket, (char*)buffer, MTU, 0, 0,0);
	if (bytesRecieved == SOCKET_ERROR)
	{
		int wsaError{ WSAGetLastError() };
		if (wsaError != WSAEWOULDBLOCK)
			std::cerr << "Error recvfrom: " << WSAGetLastError() << std::endl;
		std::exit(EXIT_FAILURE);
	}
	std::cout << "Recieved: " << buffer << std::endl;
}

void System::Update()
{
#if 0
	if (m_type == TYPE::SERVER) std::cout << "Server updating\n";
	else if (m_type == TYPE::CLIENT) std::cout << "Client updating\n";
#endif // 0

	std::memset(m_buffer, 0, MTU);

	sockaddr_in newClientAddress;
	int newClientAddress_size = sizeof(newClientAddress);
	std::memset(&newClientAddress, 0, newClientAddress_size);

	int BytesRecieved = recvfrom(m_recvSocket, (char*)m_buffer, MTU, 1, reinterpret_cast<SOCKADDR*>(&newClientAddress), &newClientAddress_size);
	if (BytesRecieved == SOCKET_ERROR)
	{
		int wsaError{ WSAGetLastError() };
		if (wsaError != WSAEWOULDBLOCK)
			std::cerr << "Error recvfrom: " << WSAGetLastError() << std::endl;
	}
	else
	{
		std::cout << "lol\n";
		for (const auto& clients : clientAddresses)
		{
			if (clients.sin_addr.S_un.S_addr == newClientAddress.sin_addr.S_un.S_addr) return;
		}

		for (auto& client : clientAddresses)
		{
			if (client.sin_addr.S_un.S_addr == 0)
			{
				client = newClientAddress;
				std::cout << "New client added\n";
				++connectClients;
				break;
			}
		}

		for (int i = 0; i < clientAddresses.size(); ++i)
		{
			if (clientAddresses[i].sin_addr.S_un.S_addr == 0)
				continue;

			char clientMsg[MTU] = "HEHE\n";
			sendto(m_recvSocket, clientMsg, MTU, 1, reinterpret_cast<SOCKADDR*>(&clientAddresses[i]), sizeof(clientAddresses));
		}
	}
}
