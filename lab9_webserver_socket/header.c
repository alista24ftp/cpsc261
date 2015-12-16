#include "webserver.h"

void sendHeader(char *header, char *body, int socket){
	
	strcat(header, body);
	send(socket, header, strlen(header), 0);
	close(socket);
}

int substrcmp(char *str, char *toBeMatchedWith, int begin){
	int nbytes = strlen(toBeMatchedWith);
	char *substr = (char *)malloc((nbytes+1) * sizeof(char));
	memcpy(substr, &str[begin], nbytes);
	substr[nbytes] = '\0';
	if(!strcmp(substr, toBeMatchedWith)){
		free(substr);
		return 0;
	}
	else{
		free(substr);
		return 1;
	}
}