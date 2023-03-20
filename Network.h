#pragma once

//#include <WS2tcpip.h>
#include <string>
#include <queue>
#include <chrono>
#include <iostream>
#include <array>
//#include "GameManagerLogic.h"
//#include "PlayerLogic.h"
//#include "GameObjects.h"

namespace Network
{

	//struct Input
	//{
	//	uint_least32_t seqNum;
	//	//std::array<int, 4> input;
	//};

	//static std::queue<Input> pendingInputs;

	// Networking Variables
	static SOCKET sendSocket; // Socket to send messages from
	static sockaddr_in serverAddr; // Server address and port
	const int MTU = 1500; // Max buffer size
	static char buffer[MTU]; // Actual buffer to store messages to be sent

	static std::chrono::steady_clock::time_point prevTP;
	static double serverUpdateRate{ 0.0 };


	// Game Variables
	static int playerID{ -1 };
	//static GameManager* gameManager{ nullptr };
	//static Player* playerLogic{ nullptr };
	//static GameObject* player1Object{ nullptr };
	//static GameObject* player2Object{ nullptr };
	//static AEVec2 player2PrevPosition{ 0.f };
	static uint_least32_t sequenceNumber{ 0 };

	inline void Initialize(		)
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
		sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (sendSocket == INVALID_SOCKET)
		{
			std::cerr << "socket() error: " << WSAGetLastError() << std::endl;
			closesocket(sendSocket);
			WSACleanup();
			std::exit(EXIT_FAILURE);
		}

		//! Set socket as non blocking for receiving from server
		unsigned long mode{ 1 };
		ioctlsocket(sendSocket, FIONBIO, &mode);

		//! Create hint structure for server information
		serverAddr.sin_family = AF_INET; //IPv4
		serverAddr.sin_port = htons(_portNumber); // Port number
		inet_pton(AF_INET, _ipAddress.c_str(), &serverAddr.sin_addr); // IP Address

		//! TESTING OF SENDING MESSAGE TO SERVER
		std::cout << "Sending message to server..." << std::endl;
		sprintf_s(buffer, "Hello from Client!"); // Write to buffer

		//! Send datagram to server
		int sendResult{ sendto(sendSocket, buffer, MTU, 0, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr)) };
		if (sendResult == SOCKET_ERROR)
		{
			std::cerr << "sendto() error: " << WSAGetLastError() << std::endl;
			closesocket(sendSocket);
			WSACleanup();
			std::exit(EXIT_FAILURE);
		}
		std::cout << "Sent: " << buffer << " to server" << std::endl;

		//// Initialize Game variables
		////? Did not do error checking cause lazy...
		//player1Object = GOM::GetGameObject("Player 1");
		//player2Object = GOM::GetGameObject("Player 2");
		//gameManager = GOM::GetComponent<GameManager>(GOM::GetGameObject("GameManager")); // Set Game Manager Logic
		//prevTP = std::chrono::steady_clock::now();
	}

	inline void CreateGameMessage(char* _buffer, int _bufferSize, int _playerID, const std::array<int, 4>& _playerInputData, uint32_t _seq)
	{
		std::memset(_buffer, 0, _bufferSize);

		// PlayerID
		std::memcpy(_buffer, &_playerID, sizeof(_playerID));
		// Player input data
		std::memcpy(_buffer + sizeof(playerID), _playerInputData.data(), _playerInputData.size() * sizeof(int));
		// Sequence number
		std::memcpy(_buffer + sizeof(playerID) + _playerInputData.size() * sizeof(int), &_seq, sizeof(_seq));

	}

	inline void ConnectionStageUpdate()
	{
		// Receive message from server
		std::memset(buffer, 0, MTU);

		int bytesRecv{ recvfrom(sendSocket, buffer, MTU, 0, nullptr, nullptr) };
		// Error checking
		if (bytesRecv == SOCKET_ERROR)
		{
			int wsaError{ WSAGetLastError() };
			if (wsaError != WSAEWOULDBLOCK)
				std::cerr << "Error recvfrom: " << WSAGetLastError() << std::endl;
		}
		else
		{
			// Set Player ID from message
			std::memcpy(&playerID, buffer, sizeof(int));
			std::cout << "[DEBUG] I am player " << playerID << std::endl;
			// Set Logic Handle for this player
			//playerLogic = playerID ? GOM::GetComponent<Player>(player2Object) : GOM::GetComponent<Player>(player1Object);
			//// Set if game should start in GameManager
			//std::memcpy(&gameManager->is2PlayersConnected, buffer + sizeof(playerID), sizeof(gameManager->is2PlayersConnected));
		}

	}

}



