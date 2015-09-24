//Server code by Bhagyashri Pathak
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE 512

int main()
{
	int fd;
       	socklen_t len;
	struct sockaddr_in serverAddr, clientAddr;
	char buffer[SIZE];
	
	fd = socket(AF_INET, SOCK_DGRAM,0);
	if(fd == -1) {
		perror("socket failed\n");
		exit(EXIT_FAILURE);
	}

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7800);
	if(inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) == -1) {
		perror("addr conversion failed\n");
		exit(EXIT_FAILURE);
	}
	//serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if( bind(fd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
		perror("bind failed\n");
		exit(EXIT_FAILURE);
	}

	while(1) {
		if(recvfrom(fd, buffer, SIZE,0,(struct sockaddr *)&clientAddr, &len) == -1) {
			perror("bind failed\n");
			exit(EXIT_FAILURE);
		}

		fprintf(stdout,"%s",buffer);
	}
	close(fd);
}
