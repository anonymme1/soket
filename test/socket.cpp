#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "socket.h"

Server::Server(int port) {
	this->port = port;
	this->options = 1;
	this->addrLen = sizeof(serverAddr);
	this->serverAddr.sin_addr.s_addr = INADDR_ANY;
	this->serverAddr.sin_family = AF_INET;
	this->serverAddr.sin_port = htons(port);
}

bool Server::actionCtrl() {
	if((serverFd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
		std::cout<<"\n\e[91msocket error!!\n";
		return false;
	}

	if(setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &options, sizeof(options))) {
		std::cout<<"\n\e[91mSetopt error!!\n";
		return false;
	}

	if(bind(serverFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
		std::cout<<"\n\e[91mBind error!!\n";
		return false;
	}

	if(listen(serverFd, 3) < 0) {
		std::cout<<"\n\e[91mListen error!!\n";
		return false;
	}

	if((newSocket = accept(serverFd, (struct sockaddr*)&serverAddr, (socklen_t*)&addrLen)) < 0) {
		std::cout<<"\n\e[91mAccept error!!\n";
		return false;
	}

	return true;
}

void Server::menu(char *buff, char* msg) {
	if(actionCtrl()) {
		std::cout<<"\nWaiting...\n\n";
		this->readValue = read(newSocket, buff, 1024);
		std::cout<<"\nGelen >> "<<buff<<"\n";
		send(newSocket, msg, strlen(msg), 0);
	}
}

Client::Client(int port) {
	this->port = port;
	this->clientAddr.sin_family = AF_INET;
	this->clientAddr.sin_port = htons(port);
}

bool Client::actionCtrl() {
	if((soket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout<<"\n\e[91mSocket error!!\n";
		return false;
	}

	if(inet_pton(AF_INET, "127.0.0.1", &clientAddr.sin_addr) <= 0) {
		std::cout<<"\n\e[91mAddress error!!\n";
		return false;
	}

	if(connect(soket, (struct sockaddr*)&clientAddr, sizeof(clientAddr)) < 0) {
		std::cout<<"\n\e[91mConnect error!!\n";
		return false;
	}

	return true;
}

void Client::menu(char *buff, char *msg) {
	if(actionCtrl()) {
		send(soket, msg, strlen(msg), 0);
		readValue = read(soket, buff, 1024);
		std::cout<<"\n\e[93mGelen >> "<<buff<<"\n";
	}
}
