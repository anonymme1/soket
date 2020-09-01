#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

#define port 8080

char *encrypt(char *a) {
        char *temp = (char*)malloc(sizeof(char)*sizeof(a));
        strcpy(temp, a);
        int len=0;

        for(int i=0;a[i] != '\0';i++)
                len++;

	for(int i=0;i<len;i++)
		temp[i] = temp[i] + 2;

        return temp;

}

char *decrypt(char *a) {
        char *temp = (char*)malloc(sizeof(char)*sizeof(a));
        strcpy(temp, a);
        int len=0;

        for(int i=0;a[i] != '\0';i++)
                len++;

	for(int i=0;i<len;i++)
		temp[i] = temp[i] - 2;
        return temp;

}
int main(int argc, char *argv[], char *envp[]) {

	int serverFd, newSocket, readVal;
	struct sockaddr_in addr;
	int opt=1;
	int addrLen = sizeof(addr);

	if((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		printf("\nSocket error!!\n");
		exit(EXIT_FAILURE);
	}

	if(setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		printf("\nSetsockopt error!!\n");
		exit(EXIT_FAILURE);
	}

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);

	if(bind(serverFd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		printf("\nBind error!!\n");
		exit(EXIT_FAILURE);
	}

	if(listen(serverFd, 3) < 0) {
		printf("\nListen error!!\n");
		exit(EXIT_FAILURE);
	}

	if((newSocket = accept(serverFd, (struct sockaddr*)&addr, (socklen_t*)&addrLen)) < 0) {
		printf("\nAccept error!!\n");
		exit(EXIT_FAILURE);
	}

	printf("\nMesaj bekleniyo...\n\n");

	while(1) {

		char msg[500];
		char buff[1024] = {0};

		readVal = read(newSocket, buff, 1024);

		printf("\n\e[93mO: %s\n\n", decrypt(buff));
		printf("\n\e[90mSen: ");
		gets(msg, 500);

		send(newSocket, encrypt(msg), strlen(msg), 0);
	}

	return 0;
}
