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
#include <string.h>

#include "tcp.h"

#define SQR(X) (X*X)
#define MAX_CHARS 1024
#define BUF_SIZE 1


/*
 * ./webclient <server name> <server port number> <name of document to request>
 * eg. ./webclient www.google.ca 80 /index.html
 */
int main(int argc, char **argv){

	int fd;
	int shut_write;
	int len, bytes_sent, bytes_recv;
	char buffer[1];
	char *msg, *recvbuf;

	if(argc != 4)
		die0("usage: send local_port destination_host remote_port");

	// get file descriptor returned from connecting to server
	fd = tcp_connect(argv[1], atoi(argv[2]));
	
	/*
	 * send request to server:
	 * requests should be in the form of:
	 * "GET <name of requested document> HTTP/1.0
	 * Host: <name of web server>"
	 */
	
	// 1. compose the message to be sent
	msg = (char *)malloc(MAX_CHARS * sizeof(char));
	strcpy(msg, "GET ");
	strcat(msg, argv[3]);
	strcat(msg, " ");
	strcat(msg, "HTTP/1.0\nHost: ");
	strcat(msg, argv[1]);
	strcat(msg, "\r\n\r\n"); // ends in CRLF
	printf("\n%s\n", msg);
	len = strlen(msg);
	
	// 2. send the message over socket
	bytes_sent = send(fd, msg, len, 0);
	if(bytes_sent<0){
		free(msg);
		die0("send error\n");
	}
	
	// send no more messages to the server
	free(msg);
	shut_write = shutdown(fd, SHUT_WR);
	if(shut_write < 0){
		die0("shutdown error\n");
	}
	
	// 3. store whatever's received from the server into recvbuf
	int index = 0;
	recvbuf = (char *)malloc(SQR(MAX_CHARS) * sizeof(char));
	do{
		if((bytes_recv = recv(fd, buffer, sizeof(buffer), 0)) < 0){
			free(recvbuf);
			die0("recv error\n");
		}
		
		sprintf((char *)&recvbuf[index], buffer);
		index += bytes_recv;
	}while(bytes_recv != 0 && strlen(recvbuf) < SQR(MAX_CHARS));

	printf("%s\n", recvbuf);
	
	// we're done...
	close(fd);
	
	free(recvbuf);
	return 0;
}
