#include "ConnectionManager.h"

namespace Connectionmanager {

	void Connect(const std::string& _ipAddress, unsigned short _portNum)
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
		serverAddr.sin_port = htons(_portNum); // Port number
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
	}

	
	

	void PreUpdate()
	{

	}

	void Update()
	{

	}

	void Free()
	{

	}

	void ConnectionStageUpdate()
	{
		// 
	}

	void GameLoopStageUpdate()
	{

		// game update loop here client side
		
		//! Send user input to server

	// Create game message
		/*
		CreateGameMessage(buffer, MTU, playerID, playerLogic->pressedDurations, sequenceNumber);

		// Send message to server
		int sendResult{ sendto(sendSocket, buffer, MTU, 0, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr)) };
		if (sendResult == SOCKET_ERROR)
		{
			std::cerr << "sendto() error: " << WSAGetLastError() << std::endl;
			closesocket(sendSocket);
			WSACleanup();
			std::exit(EXIT_FAILURE);
		}

		// Push input into pending acknowledgments queue
		pendingInputs.push({ sequenceNumber, playerLogic->pressedDurations });

		// Increment sequence number
		sequenceNumber == UINT32_MAX ? 0 : ++sequenceNumber;
		*/
	}

	void GameLoopStagePostUpdate()
	{

	}




}