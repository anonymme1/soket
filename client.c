#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define port 8080

int main(int argc, char *argv[], char *envp[]) {
	int soket=0, readVal;
	struct sockaddr_in serverAddr;

	if((soket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\nSoket hatasi!!\n");
		return -1;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);

	if(inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
		printf("\nHatali adres!!\n");
		return -1;
	}

	if(connect(soket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
		printf("\nBaglanti hatasi!!\n");
		return -1;
	}

	while(1) {
		char msg[500];
		char buff[1024] = {0};

		printf("\n\e[90mSen: ");
		gets(msg, 500);

		send(soket, msg, strlen(msg), 0);
		readVal = read(soket, buff, 1024);
		printf("\n\n\e[93mO: %s\n\n", buff);
	}

	return 0;
}
