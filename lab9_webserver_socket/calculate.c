#include "webserver.h"

/*
 * Get the values operand1, operand2, and operator from the string passed by longBuffer
 * ie. /calculate.html?(op1)(operator)(op2)
 */
long calculate(char *longBuffer, int socket){
	long ans, op1, op2;
	char *header = (char *)malloc(MAX_STRLEN * sizeof(char));
	char *body = (char *)malloc(MAX_STRLEN * sizeof(char));;
	
	// GET /calculate?(20th to nondigit char)
	char *c = &longBuffer[20];
	if(isdigit(*c)){
		op1 = strtol(c, &c, 10);
		//now c points at character after digit, the operator
		if(*c == '+'){
			c++;
			if(!isdigit(*c)){
				strcpy(body, UNDEF_OP_PAGE);
				strcpy(header, HEADER_UNDEF_OP);
				sendHeader(header, body, socket);
			}
			op2 = strtol(c, &c, 10);
			ans = op1 + op2;
		}
		else if(*c == '-'){
			c++;
			if(!isdigit(*c)){
				strcpy(body, UNDEF_OP_PAGE);
				strcpy(header, HEADER_UNDEF_OP);
				sendHeader(header, body, socket);
			}
			op2 = strtol(c, &c, 10);
			ans = op1 - op2;
		}
		else if(*c == '*'){
			c++;
			if(!isdigit(*c)){
				strcpy(body, UNDEF_OP_PAGE);
				strcpy(header, HEADER_UNDEF_OP);
				sendHeader(header, body, socket);
			}
			op2 = strtol(c, &c, 10);
			ans = op1 * op2;
		}
		else if(*c == '/'){
			c++;
			if(!isdigit(*c)){
				strcpy(body, UNDEF_OP_PAGE);
				strcpy(header, HEADER_UNDEF_OP);
				sendHeader(header, body, socket);
			}
			op2 = strtol(c, &c, 10);
			ans = op1 / op2;
		}
		else{
			strcpy(body, INVAL_OP_PAGE);
			strcpy(header, HEADER_INVAL_OP);
			sendHeader(header, body, socket);
		}
	}else{
		strcpy(body, UNDEF_OP_PAGE);
		strcpy(header, HEADER_UNDEF_OP);
		sendHeader(header, body, socket);
	}

	free(body);
	free(header);
	return ans;
}

char *getCurTime(void){
	// find current time
	time_t current_time;
	struct tm * timeinfo;
	time(&current_time);
	timeinfo = localtime(&current_time);
	return (char *)asctime(timeinfo);
}