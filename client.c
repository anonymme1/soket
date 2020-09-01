#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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

		send(soket, encrypt(msg), strlen(msg), 0);
		readVal = read(soket, buff, 1024);
		printf("\n\n\e[93mO: %s\n\n", decrypt(buff));
	}

	return 0;
}
