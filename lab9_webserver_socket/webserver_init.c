#include "webserver.h"

int webserver_init(struct sockaddr_in *my_addr, int port){
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd < 0){
		die0("socket error\n");
	}
	memset((char *)my_addr, 0, sizeof(*my_addr));
	my_addr->sin_family = AF_INET;
	my_addr->sin_port = htons(port);
	my_addr->sin_addr.s_addr = htonl(INADDR_ANY);
	
	//binding...
	printf("Binding to local port...\n");
	if(bind(fd, (struct sockaddr *)my_addr, sizeof(struct sockaddr)) < 0) die0("bind error\n");
	
	//listening...
	if(listen(fd, 5) < 0) die0("listen error\n");
	
	return fd;
}