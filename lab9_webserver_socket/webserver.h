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

#define SUCCESS_PAGE "<html><head><title></title></head><body><h1>Congrats! You've successfully connected!</h1><p>This is a UBC CPSC 261 project.</p></body></html>\n"
#define BAD_REQ "<html><head><title></title></head><body><p>Bad Request.</p></body></html>\n"
#define UNDEF_OP_PAGE "<html><head><title></title></head><body><p>Undefined Operation.</p></body></html>\n"
#define INVAL_OP_PAGE "<html><head><title></title></head><body><p>Invalid Operation.</p></body></html>\n"

#define HEADER_OK "HTTP/1.0 200 OK\n Server: CPSC261 fake web server\nContent-Type: text/html\n\n"
#define HEADER_FAIL "HTTP/1.0 400 Bad Request\n Server: CPSC261 fake web server\nContent-Type: text/html\n\n"
#define HEADER_UNDEF_OP "HTTP/1.0 400 Undefined Operation\n Server: CPSC261 fake web server\nContent-Type: text/html\n\n"
#define HEADER_INVAL_OP "HTTP/1.0 400 Invalid Operation\n Server: CPSC261 fake web server\nContent-Type: text/html\n\n"

#define INDEX_PAGE "/index.html"
#define CALC_HTML "/calculate.html?"
#define DATE_HTML "/date.html"

#define MAX_STRLEN 1024
#define HTTP_END_SEQ "\r\n\r\n"

// function prototypes:
void sendHeader(char *, char *, int);
long calculate(char *, int);
char *getCurTime(void);
int webserver_init(struct sockaddr_in *, int);
int substrcmp(char *, char *, int);
