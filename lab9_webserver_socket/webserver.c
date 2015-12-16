#include "webserver.h"

/*
 * ./webserver <port number>
 * Usage: Open up browser and type in URL (eg. "http://remote.ugrad.cs.ubc.ca:<port number>/calculate.html?345/23" or "http://remote.ugrad.cs.ubc.ca:<port number>/index.html")
 */
int main(int argc, char **argv){
	
	int recvlen, port, index, newSocket;
	long answer;
	char buffer[1], body[MAX_STRLEN], longBuffer[MAX_STRLEN], header[MAX_STRLEN];
	
	if(argc != 2) die0("Error... Please only enter port number\n");

	port = atoi(argv[1]);
	
	//initialize...
	struct sockaddr_in *my_addr;
	my_addr = malloc(sizeof(struct sockaddr_in));
	int fd = webserver_init(my_addr, port);
	
	//accepting...
	long addrlen = sizeof(struct sockaddr_in);
	while((newSocket = accept(fd, (struct sockaddr *)my_addr, (socklen_t *)&addrlen)) >= 0){
		
		//recv...
		index = 0;
		while(!strstr(longBuffer, HTTP_END_SEQ)){
			if((recvlen = recv(newSocket, buffer, sizeof(buffer), 0)) < 0)
				die0("recv error\n");
			
			sprintf((char *)&longBuffer[index], buffer);
			index+=recvlen;
		}
		
		//check for "GET"
		if(memcmp(longBuffer, "GET", 3)!=0){
			strcpy(body, BAD_REQ);
			strcpy(header, HEADER_FAIL);
			sendHeader(header, body, newSocket);
			
		}else{
			//check for "GET /index.html"
			if(!substrcmp(longBuffer, INDEX_PAGE, 4)){
				//go and GET /index.html
				strcpy(body, SUCCESS_PAGE);
				strcpy(header, HEADER_OK);
				sendHeader(header, body, newSocket);
				
			}
			else if(!substrcmp(longBuffer, CALC_HTML, 4)){
				//check for "GET /calculate.html?"
				answer = calculate(longBuffer, newSocket);
				sprintf(body, "<html><head><title></title></head><body><p>The answer is %ld.</p></body></html>\n", answer);
				strcpy(header, HEADER_OK);
				sendHeader(header, body, newSocket);
			}
			else if(!substrcmp(longBuffer, DATE_HTML, 4)){
				// check for "GET /date.html"
				sprintf(body, "<html><head><title></title></head><body><p>%s<p></body></html>\n", getCurTime());
				strcpy(header, HEADER_OK);
				sendHeader(header, body, newSocket);
			}
			else{
				strcpy(body, BAD_REQ);
				strcpy(header, HEADER_FAIL);
				sendHeader(header, body, newSocket);
			}
				
		}
		
		/*
		printf("Would you like to close the socket? [y for yes, anything else for no]\n");
		char closeSocket[MAX_STRLEN];
		scanf("%s", closeSocket);
		if(!strcmp(closeSocket, "y")){
			close(newSocket);
			close(fd);
		}
		*/
		close(fd);
	}
	
	free(my_addr);
	return 0;
}
