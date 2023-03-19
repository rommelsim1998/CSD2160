#include "ConnectionManager.h"

namespace Connectionmanager {



	//void CreateGameMessage(char* _buffer, int _bufferSize, int _playerID, const std::array<int, 4>& _playerInputData, uint32_t _seq);

	// Set player position based on server message
	void HandleAuthoritativePosition(const char* _buffer);




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


	void Update()
	{
		//! 2 Players not connected yet. Continue listening for go ahead from server
		if (!Connectionmanager::is2PlayersConnected)
			ConnectionStageUpdate();
		else
			GameLoopStageUpdate();
	}

	void PreUpdate()
	{
		if (Connectionmanager::is2PlayersConnected)
			GameLoopStagePostUpdate();
	}


	void Free()
	{

		//! Close socket
		std::cout << "Closing sending socket" << std::endl;
		int result{ closesocket(sendSocket) };
		if (result == SOCKET_ERROR)
		{
			std::cerr << "closesocket() error: " << WSAGetLastError() << std::endl;
			WSACleanup();
			std::exit(EXIT_FAILURE);
		}

		//! Clean up WSA
		std::cout << "Clean up WSA" << std::endl;
		WSACleanup();

	}

	void ConnectionStageUpdate()
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

	void GameLoopStageUpdate()
	{

		//! Send user input to server

			// Create game message

		//CreateGameMessage(buffer, MTU, playerID, playerLogic->pressedDurations, sequenceNumber);

		// Send message to server
		int sendResult{ sendto(sendSocket, buffer, MTU, 0, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr)) };
		if (sendResult == SOCKET_ERROR)
		{
			std::cerr << "sendto() error: " << WSAGetLastError() << std::endl;
			closesocket(sendSocket);
			WSACleanup();
			std::exit(EXIT_FAILURE);
		}

		// Push input into pending acknowledgment queue
		pendingInputs.push({ sequenceNumber, playerLogic->pressedDurations });

		// Increment sequence number
		sequenceNumber == UINT32_MAX ? 0 : ++sequenceNumber;
	}

	void GameLoopStagePostUpdate()
	{
		// Receive game related data from server
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
			HandleAuthoritativePosition(buffer);
			serverUpdateRate = std::chrono::duration<double>(std::chrono::steady_clock::now() - prevTP).count();
			prevTP = std::chrono::steady_clock::now();
		}
		/*
		// Reset held duration
		std::memset(playerLogic->pressedDurations.data(), 0, playerLogic->pressedDurations.size() * sizeof(int));
		*/
	}


	void HandleAuthoritativePosition(const char* _buffer)
	{
		int checkPlayer1ID{ -1 }, checkPlayer2ID{ -1 };
		AEVec2 player1Pos{ 0.f }, player2Pos{ 0.f };
		uint32_t serverSeqNum{ 0 };


		std::memcpy(&checkPlayer1ID, buffer, sizeof(checkPlayer1ID)); // P1 ID
		std::memcpy(&player1Pos.x, buffer + sizeof(checkPlayer1ID), sizeof(player1Pos.x)); // P1 Pos x
		std::memcpy(&player1Pos.y, buffer + sizeof(checkPlayer1ID) + sizeof(player1Pos.x), sizeof(player1Pos.y)); // P1 Pos y

		// P2 ID
		std::memcpy(&checkPlayer2ID,
			buffer + sizeof(checkPlayer1ID) + sizeof(player1Pos.x) + sizeof(player1Pos.y),
			sizeof(checkPlayer2ID));

		// P2 Pos x
		std::memcpy(&player2Pos.x,
			buffer + sizeof(checkPlayer1ID) + sizeof(player1Pos.x) + sizeof(player1Pos.y) + sizeof(checkPlayer2ID),
			sizeof(player2Pos.x));

		// P2 Pos y
		std::memcpy(&player2Pos.y,
			buffer + sizeof(checkPlayer1ID) + sizeof(player1Pos.x) + sizeof(player1Pos.y) + sizeof(checkPlayer2ID) + sizeof(player2Pos.x),
			sizeof(player2Pos.y));

		/*
		// Caught
		std::memcpy(&caught,
			buffer + sizeof(checkPlayer1ID) + sizeof(player1Pos.x) + sizeof(player1Pos.y) + sizeof(checkPlayer2ID) + sizeof(player2Pos.x) + sizeof(player2Pos.y),
			sizeof(caught));
			*/

			// Sequence Number -> If Seq number < seq number sent out by Client, do not update position
		std::memcpy(&serverSeqNum,
			buffer + sizeof(checkPlayer1ID) + sizeof(player1Pos.x) + sizeof(player1Pos.y) + sizeof(checkPlayer2ID) + sizeof(player2Pos.x) + sizeof(player2Pos.y),
			sizeof(serverSeqNum));

		// Update last authoritative position
		//playerID ? player2Object->transform.position = player2Pos : player1Object-//>transform.position = player1Pos;


		// if reconciliation on
		/*
		if (gameManager->isReconciliation)
		{

			// Compare against pending queue, dump entry in queue if server seq > pending entry seq
			while (!pendingInputs.empty() && (pendingInputs.front().seqNum <= serverSeqNum))
				pendingInputs.pop();

			if (pendingInputs.empty())
				return;


			// Apply whatevers left between server message and current input
			std::queue<Input> newQueue{ pendingInputs };
			while (!newQueue.empty())
			{
				playerLogic->ApplyInput(playerID ? player2Object : player1Object, newQueue.front().input);
				newQueue.pop();
			}
		}
		*/


		// Update other player
		/*
		if (gameManager->isInterpolate)
		{
			if (playerID == 0)
			{
				float xInterpolatePos{ player2PrevPosition.x + (player2Pos.x - player2Object->transform.position.x) * (Time::deltaTime / (float)serverUpdateRate) };
				float yInterpolatePos{ player2PrevPosition.y + (player2Pos.y - player2Object->transform.position.y) * (Time::deltaTime / (float)serverUpdateRate) };
				player2Object->transform.position.x = xInterpolatePos;
				player2Object->transform.position.y = yInterpolatePos;
			}
			else if (playerID == 1)
			{
				float xInterpolatePos{ player2PrevPosition.x + (player1Pos.x - player1Object->transform.position.x) * (Time::deltaTime / (float)serverUpdateRate) };
				float yInterpolatePos{ player2PrevPosition.y + (player1Pos.y - player1Object->transform.position.y) * (Time::deltaTime / (float)serverUpdateRate) };
				player1Object->transform.position.x = xInterpolatePos;
				player1Object->transform.position.y = yInterpolatePos;
			}
		}
		else
			playerID ? player1Object->transform.position = player1Pos : player2Object->transform.position = player2Pos;

		player2PrevPosition = playerID ? player1Object->transform.position : player2Object->transform.position;



		// if clear then change state to game over


	}
	*/

	}
}