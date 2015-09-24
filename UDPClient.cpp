#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define SIZE 512

int main()
{
	int fd, nbytes;
       	socklen_t len;
	struct sockaddr_in connectTo;
	char buffer[SIZE] = "abc.txt";// = "Hi Dear. How are You\n";

	fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(fd == -1) {
		perror("socket failed\n");
		exit(EXIT_FAILURE);
	}

	memset(&connectTo, 0, sizeof(connectTo));
	connectTo.sin_family = AF_INET;
	connectTo.sin_port = htons(7800);

	if(inet_pton(AF_INET, "172.16.1.159",&connectTo.sin_addr) == -1) {
		perror("convert error\n");
		exit(EXIT_FAILURE);
	}
	//connectTo.sin_addr.s_addr = inet_addr("127.0.0.1");
	len = sizeof(connectTo);
	while(1) {
		fprintf(stdout,"Sending file name to read\n ");
		//fgets(buffer,512,stdin);
		/*nbytes = strlen(buffer) + 1;
		if(sendto(fd, buffer,nbytes, 0, (struct sockaddr*)&connectTo, len) == -1) {
			perror("send failed\n");
			//fprintf(stdout,"%s", strerror(errno));
			exit(EXIT_FAILURE);
		}*/

		while(recvfrom(fd, buffer, SIZE, 0, (struct sockaddr*)&connectTo, &len) != -1) {
			fprintf(stdout,"%s",buffer);
		}
	}
}
