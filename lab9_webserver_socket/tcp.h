/*
 * Print error messages and exit
 */
extern void die0(const char *msg);
extern void diee(const char *msg);
extern void die1(const char *format, const char *msg);

extern int udp_open(int port);
extern struct sockaddr *get_sockaddr(const char *s, int port, struct sockaddr *saddr);
extern char *format_sockaddr(struct sockaddr *saddr, char *buffer);

/*
 * Connect to the given port on the given host, returning the connected
 * socket.  If there are any errors, print an error message and exit.
 */
extern int tcpconnect(char *hostname, int port);
