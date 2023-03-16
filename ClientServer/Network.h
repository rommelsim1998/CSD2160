#pragma once

#include <WS2tcpip.h>
#include <winsock.h>
#include <WinSock2.h>
#include <string>
#include <iostream>
#include <array>
#pragma comment(lib, "Ws2_32.lib")

namespace Network
{
	// Variables
	static SOCKET recvSocket; // Socket to receive messages from, this is your "server socket" but you might have one for sending and one for receving
	static sockaddr_in serverAddr; //

	const int MTU = 1500; // Max buffer size
	static char buffer[MTU]; // actual buffer to write data into
	static std::array<sockaddr_in, 2> clientAddresses; // Client addresses that will be updated by recvfrom function
	// that will be updated by recvfrom function
		static int connectedClientCount{ 0 };


		// Game variables
		
		//static GameObject* player1Object{ nullptr };
		//static GameObject* player2Object{ nullptr };

	// Definitions
	inline void Init(const std::string& ip_addr, const unsigned short& portNum)
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

		//! Create listening socket
		recvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (recvSocket == INVALID_SOCKET)
		{
			std::cerr << "socket() error: " << WSAGetLastError() << std::endl;
			closesocket(recvSocket);
			WSACleanup();
			std::exit(EXIT_FAILURE);
		}

		//! Create hint structure for this server
		serverAddr.sin_family = AF_INET; //IPv4
		serverAddr.sin_port = htons(54000); // Port number
		serverAddr.sin_addr.S_un.S_addr = ADDR_ANY; // Use any IP avail on machine

		//! Bind socket to IP and port
		if (bind(recvSocket, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
		{
			std::cout << "bind() error: " << WSAGetLastError() << std::endl;
			closesocket(recvSocket);
			WSACleanup();
			std::exit(EXIT_FAILURE);
		}

		//! Set socket to Non-blocking so we do not need to use Multi threading
		unsigned long mode{ 1 };
		ioctlsocket(recvSocket, FIONBIO, &mode);

		std::cout << "Server successfully created.\n";
	}

	void CreateNewClientMessage(char* _buffer, int _bufferSize, int _playerID, bool _gameStart)
	{
		// Clear buffer
		std::memset(_buffer, 0, _bufferSize);

		// Set PlayerID
		std::memcpy(_buffer, &_playerID, sizeof(_playerID));
		// Set gameStart
		std::memcpy(_buffer + sizeof(_playerID), &_gameStart, sizeof(_gameStart));
	}


	void ClientConnectionStageUpdate()
	{
		std::memset(&buffer, 0, MTU); // Clear buffer

		//! Block and wait for message
		// Store newly connect client address
		sockaddr_in newClientAddr;
		int clientAddrSize{ sizeof(newClientAddr) };
		std::memset(&newClientAddr, 0, sizeof(newClientAddr));

		
		//! Receive Message from client
		int bytesRecv{ recvfrom(recvSocket, buffer, MTU, 0, reinterpret_cast<SOCKADDR*>(&newClientAddr), &clientAddrSize) };


		if (bytesRecv == SOCKET_ERROR)
		{
			int wsaError{ WSAGetLastError() };
			if (wsaError != WSAEWOULDBLOCK)
				std::cerr << "Error recvfrom: " << WSAGetLastError() << std::endl;
			//return;
		}
		else
		{
			// Check if IP already exist
			for (auto& clientAddr : clientAddresses)
			{
				if (clientAddr.sin_addr.S_un.S_addr == newClientAddr.sin_addr.S_un.S_addr)
					return;
			}

			// Add new client to empty slot in client list
			for (auto& clientAddr : clientAddresses)
			{
				if (clientAddr.sin_addr.S_un.S_addr == 0)
				{
					clientAddr = newClientAddr;
					std::cout << "[DEBUG] new client added!\n";
					++connectedClientCount;
					break; // Exit loop so we do not add the same client multiple times
				}
			}

			// Send new client message to all clients
			for (int i{ 0 }; i < clientAddresses.size(); ++i)
			{
				// Skip if slot is unconnected client
				if (clientAddresses[i].sin_addr.S_un.S_addr == 0)
					continue;

				// Form "Successfully Connected" message and send back to client
				char clientMessage[MTU];
				CreateNewClientMessage(clientMessage, sizeof(clientMessage), i, connectedClientCount == 2);
				sendto(recvSocket, clientMessage, MTU, 0, reinterpret_cast<SOCKADDR*>(&clientAddresses[i]), sizeof(clientAddresses[i]));
			}

			//! Print message
			// convert client IP to string
			char clientIP[256];
			inet_ntop(AF_INET, &newClientAddr.sin_addr, clientIP, 256);

			// Display message
			std::cout << "[Debug] New Client connected from " << clientIP << " with message: " << buffer << std::endl;

			//! Change game state for when 2 clients connected
			//gameManager->is2PlayersConnected = (connectedClientCount == 2);
		}
	}

}