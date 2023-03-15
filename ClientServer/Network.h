#pragma once

#include <WS2tcpip.h>
#include <winsock.h>
#include <WinSock2.h>
#include <string>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

namespace Network
{
	// Variables
	static SOCKET recvSocket; // Socket to receive messages from, this is your "server socket" but you might have one for sending and one for receving
	static sockaddr_in serverAddr; //

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

		std::cout << "Server successfully created.\n";
	}
}