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
#define BUF_LEN 1234
#define PORT 1234
#define BUF_LEN 1234

static int fd = STDOUT_FILEND;
int my_printf(const char * format,)
{
    char buf[BUF_LEN]; int len;
    va_list ap;
    va_start(ap,format);
    len = vsnprintf(buf, BUF_LEN, format, ap);
    va_end(ap);
    return write(fd, buf, len);

}

int write_fd(int fd, const char * buf, int len)
{
    int i, nbytes;
    len++;
    if (write(fd,&len,sizeof(int))!=sizeof(int))
    return -1;
    for(i=0;len > 0; i+=nbytes, len-=nbytes)
    {
	nbytes = write(fd, buf+i, len);
	if(nbytes < = 0) return -2;
    }
    return 0;

}

int read(int fd, char * buf)
{
    int len , i,nbytes;
    if (read(fd, &len, sizeof(int))!= sizeof(int))
    return -1;
    for(i=0; len > 0; i+=nbytes, len-=nbytes)
    {
	nbytes = read(fd, buf+i, len);
	if(nbytes <= 0) return -2;
    }
    return 0;
}

int main(void)
{
int sock; int opt = 1; struct sockaddr_in addr;
fd_set active_set, read_set;
struct sockaddr_in addr; int size; int new_sock;
sock = socket(PF_INET, SOCK_STREAM, 0);
if (sock < 0) return -2;
setsock opt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
adr.sin_family = AF_INET;
addr.sin_port = htons(PORT);
addr.sin_addr.s_addr = htonl(INETADDR_ANY);
if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) return -3;
if (listen (sock, 3) < 0) return -1;
FD_ZERO(&active_set);
FD_SET(sock, &active_set);
while(1)
{
    read_set = active_set;
    if(select(FD_SETSIZE, &read_set, 0, 0, 0) < 0) return -4;
    for(i = 0; i < FD_SETSIZE; i++)
    {
	if(FD_ISSET(i, &read_set))
	{
	    if(i == sock)
	    {
		size = sizeof(client);
		new_sock = accept(sock, (struct sockaddr *)&client, &size);
		FD_SET(new_sock, &active_set);
		
	    }
	    else 
	    {
		if(read_fd(i, buf) < 0)
		{close(i); FD_CLR(i, &active_set);}
		else 
		{
		    write_fd(i, buf, len);
		    close(i);
		    FD_CLR(i, &active_set);
		    if(!strcmp(buf, "stop"))
		    {
			close(sock);
			return 0;
		    }
		} 
	    }
	}
    }
}


}
