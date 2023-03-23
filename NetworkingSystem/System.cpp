#include "System.h"
#include "System.h"
#include "System.h"
#pragma once
class GameObject;

SOCKET System::m_sendSocket;
SOCKET System::m_recvSocket;
sockaddr_in System::m_serverAddr;
//int connectClients = 1;
//bool playersConnected2 = false;
char System::m_buffer[MTU];
char System::m_buffer_game[MTU];
std::vector<sockaddr_in> System::clientAddresses{};
char System::m_buffer_send[MTU];
char System::m_buffer_recieve[MTU];

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

static bool isSending = true;

void Server::Update()
{
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

		// skip if current list of IP contains new one
		for (auto& clients : System::clientAddresses)
		{
			if (clients.sin_addr.S_un.S_addr == newClientAddress.sin_addr.S_un.S_addr) return;
		}

		// Append new client IP into my list
		if(newClientAddress.sin_addr.S_un.S_addr != 0)
		{
			System::clientAddresses.push_back(newClientAddress);
			++connectedClient;
			Send(&connectedClient, MTU);
			return;
		}
		//else
		//{
		//	for (auto& client : clientAddresses)
		//	{
		//		if (client.sin_addr.S_un.S_addr == 0)
		//		{
		//			//client = newClientAddress;
		//			clientAddresses.push_back(newClientAddress);
		//			std::cout << "[Server]: New client added\n";
		//			++connectedClient;
		//			break;
		//		}
		//	}
		//}

		//for (int i = 0; i < clientAddresses.size(); ++i)
		//{
		//	if (clientAddresses[i].sin_addr.S_un.S_addr == 0)
		//		continue;
		//	//std::string clientMsg = std::to_string(connectedClient);
		//	//sendto(m_recvSocket, clientMsg.c_str(), MTU, 0, reinterpret_cast<SOCKADDR*>(&clientAddresses[i]), sizeof(clientAddresses[i]));
		//}
		
	}

	//char clientIP[256];
	//inet_ntop(AF_INET, &newClientAddress.sin_addr, clientIP, 256);
}

void Server::Send(void* buffer, int len)
{
	std::memset(m_buffer, 0, MTU);
	std::memcpy(m_buffer, buffer, len);
	for (int i = 0; i < System::clientAddresses.size(); ++i)
	{
		if (System::clientAddresses[i].sin_addr.S_un.S_addr == 0)
			continue;

		sendto(m_recvSocket, reinterpret_cast<const char*>(m_buffer), len, 0, reinterpret_cast<SOCKADDR*>(&System::clientAddresses[i]), sizeof(System::clientAddresses[i]));
		//std::cout << "[Server]: Sending " << len << " bytes of data to " << System::clientAddresses[i].sin_addr.S_un.S_addr << std::endl;
	}
	//sendto(m_sendSocket, (const char*)buffer, len, 0, reinterpret_cast<SOCKADDR*>(&m_serverAddr), sizeof(m_serverAddr));
}

void Server::Send(int& x1, int& y1, int& x2, int& y2)
{
	// Way to read!
	char buf[MTU];
	std::memset(buf, 0, MTU);
	std::memcpy(buf		, &x1, 4);
	std::memcpy(buf + 4 , &y1, 4);
	std::memcpy(buf + 8 , &x2, 4);
	std::memcpy(buf + 12, &y2, 4);

#if 0
	int a = 10, b = 20, c = 30, d = 40;
	std::memcpy(buf, &a, 4);
	std::memcpy(buf + 4, &b, 4);
	std::memcpy(buf + 8, &c, 4);
	std::memcpy(buf + 12, &d, 4);
#endif
	size_t len = sizeof(int) * 4;
	for(auto& clients : System::clientAddresses)
	{
		if (clients.sin_addr.S_un.S_addr == 0) continue;
		sendto(m_recvSocket, reinterpret_cast<const char*>(buf), len, 0, reinterpret_cast<SOCKADDR*>(&clients), sizeof(clients));
		//std::cout << "[Server]: Sending " << len << " bytes of data to " << clients.sin_addr.S_un.S_addr << std::endl;
	}
	/*for (int i = 0; i < clientAddresses.size(); ++i)
	{
		if (clientAddresses[i].sin_addr.S_un.S_addr == 0)
			continue;

		sendto(m_recvSocket, reinterpret_cast<const char*>(m_buffer_game), len, 0, reinterpret_cast<SOCKADDR*>(&clientAddresses[i]), sizeof(clientAddresses[i]));
		std::cout << "[Server]: Sending " << len << " bytes of data to " << clientAddresses[i].sin_addr.S_un.S_addr << std::endl;
	}*/
}

void Server::SendClientID(int& id)
{
	char clientIDBuffer[MTU];
	std::memset(clientIDBuffer, 0, MTU);
	std::memcpy(clientIDBuffer, &id, 4);
	for (int i = 0; i < System::clientAddresses.size(); ++i)
	{
		if (System::clientAddresses[i].sin_addr.S_un.S_addr == 0)
			continue;

		sendto(m_recvSocket, reinterpret_cast<const char*>(clientIDBuffer), 4, 0, reinterpret_cast<SOCKADDR*>(&System::clientAddresses[i]), sizeof(System::clientAddresses[i]));
	}
}

void Server::SendFlagFor2Players(bool& flag)
{
	char flagBuffer[MTU];
	std::memset(flagBuffer, 0, MTU);
	std::memcpy(flagBuffer, &flag, 1);
	for (int i = 0; i < System::clientAddresses.size(); ++i)
	{
		if (System::clientAddresses[i].sin_addr.S_un.S_addr == 0)
			continue;

		sendto(m_recvSocket, reinterpret_cast<const char*>(flagBuffer), 1, 0, reinterpret_cast<SOCKADDR*>(&System::clientAddresses[i]), sizeof(System::clientAddresses[i]));
	}
}

void Server::Read(int& x1, int& y1, int& x2, int& y2)
{
	for (auto& client : clientAddresses)
	{
		if (client.sin_addr.S_un.S_addr == 0)continue;
		int lenClient = sizeof(client);
		int bytes = recvfrom(m_recvSocket, m_buffer_recieve, MTU, 0, reinterpret_cast<SOCKADDR*>(&client), &lenClient);
		if (bytes == SOCKET_ERROR)
		{
			int wsaErr{ WSAGetLastError() };
			if (wsaErr != WSAEWOULDBLOCK)
				std::cerr << "[Server]: error: " << wsaErr << std::endl;
		}
		else
		{
			std::memcpy(&x1, reinterpret_cast<int*>(m_buffer_recieve + 0), 4);
			std::memcpy(&y1, reinterpret_cast<int*>(m_buffer_recieve + 4), 4);
			std::memcpy(&x2, reinterpret_cast<int*>(m_buffer_recieve + 8), 4);
			std::memcpy(&y2, reinterpret_cast<int*>(m_buffer_recieve + 12), 4);
			//std::cout << "[Server]: Receiving " << bytes << " of data. (" << x << ", " << y << ")" << std::endl;
		}

	}/*
	int bytes = recvfrom(m_sendSocket, m_buffer_recieve, MTU, 0, nullptr, nullptr);
	if (bytes == SOCKET_ERROR)
	{
		int wsaErr{ WSAGetLastError() };
		if (wsaErr != WSAEWOULDBLOCK)
			std::cerr << "[Server]: error: " << wsaErr << std::endl;
	}
	else
	{
		std::memcpy(&x, reinterpret_cast<int*>(m_buffer_recieve), 4);
		std::memcpy(&y, reinterpret_cast<int*>(m_buffer_recieve + 4), 4);
		std::cout << "[Server]: Receiving " << bytes << " of data. (" << x << ", " << y << ")" << std::endl;
	}*/
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
	/*int sendresult{ sendto(m_sendSocket, m_buffer, MTU, 0, reinterpret_cast<SOCKADDR*>(&m_serverAddr), sizeof(m_serverAddr)) };
	if (sendresult == SOCKET_ERROR)
	{
		std::cerr << "[Client]: Sendto() error: " << WSAGetLastError() << std::endl;
		closesocket(m_sendSocket);
		WSACleanup();
		std::exit(EXIT_FAILURE);
	}*/
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
		std::cout << "[Client]: Receiving " << bytes << " of data. Message is: " << *(int*)(m_buffer) << std::endl;
	}
}

void Client::Send(void* buffer, int len)
{
	std::memset(m_buffer, 0, MTU);
	sendto(m_sendSocket, (const char*)buffer, len, 0, reinterpret_cast<SOCKADDR*>(&m_serverAddr), sizeof(m_serverAddr));
	std::cout << "[Client]: Sending " << len << " bytes of data\n";
}

int Server::GetPlayers()
{
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

		// skip if current list of IP contains new one
		for (auto& clients : System::clientAddresses)
		{
			if (clients.sin_addr.S_un.S_addr == newClientAddress.sin_addr.S_un.S_addr) return -1;
		}

		// Append new client IP into my list
		if (newClientAddress.sin_addr.S_un.S_addr != 0)
		{
			System::clientAddresses.push_back(newClientAddress);
			++connectedClient;
			SendClientID(connectedClient);
			//Send(&connectedClient, MTU);
		}
	}
	return connectedClient;
}

void Client::Send(int& x1, int& y1, int& x2, int& y2)
{
	std::memset(m_buffer_send, 0, MTU);
	std::memcpy(m_buffer_send + 0,  &x1, 4);
	std::memcpy(m_buffer_send + 4,  &y1, 4);
	std::memcpy(m_buffer_send + 8,  &x2, 4);
	std::memcpy(m_buffer_send + 12, &y2, 4);
	size_t len = sizeof(int) * 4;
	sendto(m_sendSocket, (const char*)m_buffer_send, len, 0, reinterpret_cast<SOCKADDR*>(&m_serverAddr), sizeof(m_serverAddr));
}

void Client::Read(int& x1, int& y1, int& x2, int& y2)
{
	std::memset(m_buffer_recieve, 0, MTU);
	int bytes = recvfrom(m_sendSocket, m_buffer_recieve, MTU, 0, nullptr, nullptr);
	if (bytes == SOCKET_ERROR)
	{
		int wsaErr{ WSAGetLastError() };
		if (wsaErr != WSAEWOULDBLOCK)
			std::cerr << "[Client]: error: " << wsaErr << std::endl;
	}
	else
	{
		/*x1 = reinterpret_cast<int>(*m_buffer_recieve + 0);
		y1 = reinterpret_cast<int>(*(m_buffer_recieve + 4));
		x2 = reinterpret_cast<int>(*(m_buffer_recieve + 8));
		y2 = reinterpret_cast<int>(*(m_buffer_recieve + 12));*/
		std::memcpy(&x1, m_buffer_recieve, 4);
		std::memcpy(&y1, m_buffer_recieve + 4, 4);
		std::memcpy(&x2, m_buffer_recieve + 8, 4);
		std::memcpy(&y2, m_buffer_recieve + 12, 4);
		
	}
}

int Client::GetClientId()
{
	char bufferID[MTU];
	std::memset(bufferID, 0, MTU);
	int bytes = recvfrom(m_sendSocket, bufferID, MTU, 0, nullptr, nullptr);
	if(bytes != SOCKET_ERROR)
	{
		int id{};
		std::memcpy(&id, bufferID, 4);
		return id;
	}
	/*if (bytes == SOCKET_ERROR)
	{
		int wsaErr{ WSAGetLastError() };
		if (wsaErr != WSAEWOULDBLOCK)
			std::cerr << "[Client]: error: " << wsaErr << std::endl;
	}
	else
	{
		int id{};
		std::memcpy(&id, bufferID, 4);
		return id;
	}*/
}

bool Client::WaitFor2Players()
{
	bool readFlag = 0;
	char tmp[MTU];
	std::memset(tmp, 0, MTU);
	int bytes = recvfrom(m_sendSocket, tmp, MTU, 0, nullptr, nullptr);
	if(bytes != SOCKET_ERROR)
	{
		std::memcpy(&readFlag, tmp, 1);
		std::cout << "Flag is " << readFlag << std::endl;
		return readFlag;
	}

}

void Client::Read(int& value)
{
	int bytes = recvfrom(m_sendSocket, m_buffer, MTU, 0, nullptr, nullptr);
	value = *(int*)(m_buffer);
	
}


void Client::Read(float& x, float& y)
{
	int bytes = recvfrom(m_sendSocket, m_buffer_game, MTU, 0, nullptr, nullptr);
	if (bytes == SOCKET_ERROR)
	{
		int wsaErr{ WSAGetLastError() };
		if (wsaErr != WSAEWOULDBLOCK)
			std::cerr << "[Client]: error: " << wsaErr << std::endl;
	}
	else
	{
		
		std::cout << "[Client]: " << static_cast<float>(*m_buffer_game) << ", " << static_cast<float>(*(m_buffer_game + 4)) << std::endl;
		x = static_cast<float>(*m_buffer_game);
		y = static_cast<float>(*(m_buffer_game + 4));
		/*std::memcpy((float*)&x, m_buffer, 4);
		std::memcpy((float*)&y, m_buffer + 4, 4);
		std::cout << "[Client]: Receiving " << bytes << " of data. Message is: " << x << ", " << y << std::endl;*/
	}
	//std::cout << "[Client]: Bytes read: " << bytes << std::endl;
	//std::memcpy(&x, m_buffer, 4);		// x 
	//std::memcpy(&y, m_buffer + 4, 4);	// y
}


//template <typename T>
//void Client::Read(void* buffer, int len)
//{
//	std::memset(buffer, 0, MTU);
//	int bytes = recvfrom(m_sendSocket, m_buffer, len, 0, nullptr, nullptr);
//	std::memcpy(buffer, m_buffer, bytes);
//	std::cout << "[Client]: Receiving " << bytes << " of data. Message is: " << *(T*)buffer << std::endl;
//}