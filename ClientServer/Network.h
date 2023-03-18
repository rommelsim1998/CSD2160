#pragma once

#include <WS2tcpip.h>
#include <winsock.h>
#include <WinSock2.h>
#include <string>
#include <iostream>
#include <array>
#include "Constants.h"
#include "GameStateManager.h"
#include "../ConnectionManager.h"


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
		//Player player1;
		//Player player2;
		void CreateNewClientMessage(char* _buffer, int _bufferSize, int _playerID, bool _gameStart);
		void CreateGameMessage(char* _buffer, int _bufferSize, int _playerID1, AEVec2 _pos1, int _playerID2, AEVec2 _pos2, bool _caught, uint32_t _seq);


	

	void Free()
	{
		//! Close socket
		std::cout << "Closing sending socket" << std::endl;
		int result{ closesocket(recvSocket) };
		if (result == SOCKET_ERROR)
		{
			std::cerr << "closesocket() error: " << WSAGetLastError() << std::endl;
			WSACleanup();
			std::exit(EXIT_FAILURE);
		}

		//! Clean up WSA
		std::cout << "Clean up WSA" << std::endl;
		WSACleanup();
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

		//player1Object = _em->CreateEntity(TYPE_PLAYER);
		//player2Object = _em->CreateEntity(TYPE_PLAYER);

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
			Connectionmanager::is2PlayersConnected = (connectedClientCount == 2);
		}
	}


	void GameLoopStageUpdate()
	{
		/*
			1. Receive input data from clients
			2. Set input data according to playerID in PlayerLogic
		*/

		int uniqueIPCount{ 0 };
		ULONG prevIP{ 0 };
		sockaddr_in ClientAddr;
		int clientAddrSize{ sizeof(ClientAddr) };
		while (1)
		{
			// Clear buffer
			std::memset(buffer, 0, MTU);

			//! Receive Message from client
			int bytesRecv{ recvfrom(recvSocket, buffer, MTU, 0, reinterpret_cast<SOCKADDR*>(&ClientAddr), &clientAddrSize) };
			if (bytesRecv == SOCKET_ERROR)
			{
				int wsaError{ WSAGetLastError() };
				if (wsaError != WSAEWOULDBLOCK)
					std::cerr << "Error recvfrom: " << WSAGetLastError() << std::endl;
				//return;
			}
			else
			{
				// Ensure both gets a chance to update
				if (ClientAddr.sin_addr.S_un.S_addr == prevIP)
					continue;

				prevIP = ClientAddr.sin_addr.S_un.S_addr;
				++uniqueIPCount;

				// Retrieve PlayerID data
				int recvPlayerID{ -1 };
				std::memcpy(&recvPlayerID, buffer, sizeof(recvPlayerID));

				// Set player 1
				if (recvPlayerID == 0)
				{
					/*
					// logic to set player 1
					std::memcpy(GOM::GetComponent<Player>(player1Object)->pressedDurations.data(),
						buffer + sizeof(recvPlayerID),
						GOM::GetComponent<Player>(player1Object)->pressedDurations.size() * sizeof(int));

					// Store Sequence Number
					std::memcpy(&prevSequenceNumber1,
						buffer + sizeof(recvPlayerID) + GOM::GetComponent<Player>(player1Object)->pressedDurations.size() * sizeof(int),
						sizeof(prevSequenceNumber1));
						*/
				}

				// Set player 2
				else if (recvPlayerID == 1)
				{
					// logic to set player 2
					/*
					std::memcpy(GOM::GetComponent<Player>(player2Object)->pressedDurations.data(),
						buffer + sizeof(recvPlayerID),
						GOM::GetComponent<Player>(player2Object)->pressedDurations.size() * sizeof(int));

					std::memcpy(&prevSequenceNumber2,
						buffer + sizeof(recvPlayerID) + GOM::GetComponent<Player>(player2Object)->pressedDurations.size() * sizeof(int),
						sizeof(prevSequenceNumber2));
						*/
				}

				// End if both client updated
				if (uniqueIPCount == 2)
					break;
			}
		}

	}
	
	void GameLoopStagePostUpdate()
	{
		/*
			Send absolute position of both players to all clients
		*/
		/*
		uint_least32_t seqNum{ 0 };
		// Send new game message to all clients
		for (int i{ 0 }; i < clientAddresses.size(); ++i)
		{
			seqNum = i ? prevSequenceNumber2 : prevSequenceNumber1;
			CreateGameMessage(buffer,
				MTU,
				0,
				player1Object->transform.position,
				1,
				player2Object->transform.position,
				gameManager->isCaught,
				seqNum
			);

			sendto(recvSocket, buffer, MTU, 0, reinterpret_cast<SOCKADDR*>(&clientAddresses[i]), sizeof(clientAddresses[i]));
		}*/
	}

	/*
	void CreateNewClientMessage(char* _buffer, int _bufferSize, int _playerID, bool _gameStart)
	{
		// Clear buffer
		std::memset(_buffer, 0, _bufferSize);

		// Set PlayerID
		std::memcpy(_buffer, &_playerID, sizeof(_playerID));
		// Set gameStart
		std::memcpy(_buffer + sizeof(_playerID), &_gameStart, sizeof(_gameStart));
	}
	*/

	void CreateGameMessage(char* _buffer, int _bufferSize, int _playerID1, AEVec2 _pos1, int _playerID2, AEVec2 _pos2, bool _caught, uint32_t _seq)
	{
		std::memset(_buffer, 0, _bufferSize);

		// Player 1 ID + position
		std::memcpy(_buffer, &_playerID1, sizeof(_playerID1));
		std::memcpy(_buffer + sizeof(_playerID1), &_pos1.x, sizeof(_pos1.x));
		std::memcpy(_buffer + sizeof(_playerID1) + sizeof(_pos1.x), &_pos1.y, sizeof(_pos1.y));

		// Player 2 ID + position
		std::memcpy(_buffer + sizeof(_playerID1) + sizeof(_pos1.x) + sizeof(_pos1.y)
			, &_playerID2,
			sizeof(_playerID2));

		std::memcpy(_buffer + sizeof(_playerID1) + sizeof(_pos1.x) + sizeof(_pos1.y) + sizeof(_playerID2),
			&_pos2.x,
			sizeof(_pos2.x));

		std::memcpy(_buffer + sizeof(_playerID1) + sizeof(_pos1.x) + sizeof(_pos1.y) + sizeof(_playerID2) + sizeof(_pos2.x),
			&_pos2.y,
			sizeof(_pos2.y));

		// Caught
		std::memcpy(_buffer + sizeof(_playerID1) + sizeof(_pos1.x) + sizeof(_pos1.y) + sizeof(_playerID2) + sizeof(_pos2.x) + sizeof(_pos2.y),
			&_caught,
			sizeof(_caught));

		// Sequence Number
		std::memcpy(_buffer + sizeof(_playerID1) + sizeof(_pos1.x) + sizeof(_pos1.y) + sizeof(_playerID2) + sizeof(_pos2.x) + sizeof(_pos2.y) + sizeof(_caught),
			&_seq,
			sizeof(_seq));
	}



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

	void Update()
	{

		if (!Connectionmanager::is2PlayersConnected)
		{
			ClientConnectionStageUpdate();
		}
		else
		{
			GameLoopStageUpdate();
		}


	}

	void PostUpdate()
	{
		if (Connectionmanager::is2PlayersConnected == true)
			GameLoopStagePostUpdate();
	}

}