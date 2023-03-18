#pragma once
#include <WS2tcpip.h>
#include <winsock.h>
#include <WinSock2.h>
#include <string>
#include <iostream>
#include <queue>
#include <chrono>
#include "Constants.h"
#pragma comment(lib, "Ws2_32.lib")


namespace Connectionmanager
{
	struct Input
	{
		uint_least32_t seqNum;
		std::array<int, 4> input;
	};


	static std::queue<Input> pendingInputs;

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
	static Player* playerLogic{ nullptr };
	// 

	
	//static Player player1;
	//static Player player2;


	static GameObject* player1Object{ nullptr };
	static GameObject* player2Object{ nullptr };
	//static AEVec2 player2PrevPosition{ 0.f };
	static uint_least32_t sequenceNumber{ 0 };

	static bool is2PlayersConnected = false;

	static bool isMultiplayer = true;


	void Connect(const std::string& _ipAddress, unsigned short _portNum);

	void PreUpdate();

	void Update();

	void Free();

	void ConnectionStageUpdate();

	void GameLoopStageUpdate();

	void GameLoopStagePostUpdate();




}
