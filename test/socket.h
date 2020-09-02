#ifndef _SOCKET_H_
#define _SOCKET_H_

class Server {
	private:
		int serverFd, newSocket, readValue;
		int options, addrLen;
		struct sockaddr_in serverAddr;

	public:
		int port;
		Server(int);
		bool actionCtrl();
		void menu(char* , char*);
};

class Client {
	private:
		int soket, readValue;
		struct sockaddr_in clientAddr;

	public:
		int port;
		Client(int);
		bool actionCtrl();
		void menu(char*, char*);
};


#endif
