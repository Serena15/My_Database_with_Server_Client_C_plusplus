#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa;inet.h>
#include <netdb.h>
#include "ser.h"
#define PORT 1234
#define BUF_LEN 1234
#define SERVER "127.0.0.1"
int main(void)
{
    struct hostent *hostinfo;
    struct sockaddr_in server_addr;
    hostinfo = gethostbyname(SERVER);
    if(!hostint) return -1;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr = *(struct in_addr *) hostinfo -> h_addr;
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0) return -2;
    if(connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) return -3;
    while(fgets(buf, BUF_LEN, stdin))
    {
	write_fd(sock, buf, strlen(buf)+1);
	read_fd(sock, buf, BUF_LEN);
    }
    close(sock);
    return;    
}
