#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

#include "tcp.h"

#define MAX_CHARS 1024
#define BUF_SIZE 1
#define SQR(X) (X*X)

int main(int argc, char **argv){

	int fd;
	int bytes_sent, bytes_recv;
	int len;
	char buffer[BUF_SIZE];
	char *msg;
	char *longbuf;
	
	if(argc != 3)
		die0("usage: ./client <destination_hostname> <remote_port>");
	
	// connect
	fd = tcp_connect(argv[1], atoi(argv[2]));
	
	// compose msg to be sent
	msg = (char *)malloc(MAX_CHARS * sizeof(char));
	strcpy(msg, "GET /index.html HTTP/1.0\nHost: ");
	strcat(msg, argv[1]);
	strcat(msg, "\r\n\r\n"); // ends in CRLF
	len = strlen(msg);
	
	if((bytes_sent = send(fd, msg, len, 0)) < 0){
		free(msg);
		die0("send error\n");
	}
	printf("sent:\n %s\n", msg);
	
	// receive into longbuf
	longbuf = (char *)malloc(SQR(MAX_CHARS) * sizeof(char));
	int index = 0;
	do{
		if((bytes_recv = recv(fd, buffer, sizeof(buffer), 0)) < 0){
			free(msg);
			free(longbuf);
			die0("recv error\n");
		}
		sprintf((char *)&longbuf[index], buffer);
		index += bytes_recv;
	}while(bytes_recv != 0 && strlen(longbuf) < SQR(MAX_CHARS));
	
	printf("received:\n %s\n", longbuf);
	
	close(fd);
	free(msg);
	free(longbuf);
	return 0;
}
