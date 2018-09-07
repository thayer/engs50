/* 
 * inserver - an example Internet server.
 *
 * This program accepts connections forever in an infinite loop.
 * 
 * usage: inserver
 *  and ctrl-C to exit.
 *
 * David Kotz, 1987, 1992, 2016
 * Adapted from Figure 7b in Introductory 4.3bsd IPC, PS1:7-16,17.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>	      // bool type
#include <unistd.h>	      // read, write, close
#include <strings.h>	      // bcopy, bzero
#include <arpa/inet.h>	      // socket-related calls

/**************** file-local constants ****************/
static const int LISTEN_BACKLOG = 5; // number of connections to keep waiting
static const int BUFSIZE = 1024;     // read/write buffer size

/**************** main() ****************/
int
main(const int argc, char *argv[])
{
  // no arguments to parse

  // Create socket on which to listen (file descriptor)
  int list_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (list_sock < 0) {
    perror("opening socket stream");
    exit(1);
  }

  // Name socket using wildcards
  struct sockaddr_in server;  // server address
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 0;
  if (bind(list_sock, (struct sockaddr *) &server, sizeof(server))) {
    perror("binding socket name");
    exit(2);
  }

  // Print our assigned port number
  socklen_t serverlen = sizeof(server);	// length of the server address
  if (getsockname(list_sock, (struct sockaddr *) &server, &serverlen)) {
    perror("getting socket name");
    exit(3);
  }
  printf("Listening at port %d\n", ntohs(server.sin_port));
  printf("To find your MacOS IP address, ifconfig | grep 'inet '\n");
  
  // Start accepting connections, and allow one connection at a time
  listen(list_sock, LISTEN_BACKLOG);
  while (true) {
    // accept connection and receive communication socket (file descriptor)
    int comm_sock = accept(list_sock, 0, 0);
    if (comm_sock == -1) {
      perror("accept");
    } else {
      printf("Connection started\n");
      
      char buf[BUFSIZE];      // buffer for reading data from socket
      int bytes_read;	      // #bytes read from socket
      
      do {
	bzero(buf, sizeof(buf)); // fill buffer with nulls
	// read from socket into buffer - but leave room for null
	if ((bytes_read = read(comm_sock, buf, BUFSIZE-1)) < 0) {
	  perror("reading stream message");
	}
	if (bytes_read == 0) {
	  printf("Ending connection\n");
	} else {
	  printf("\t%s", buf);
	}
      } while (bytes_read != 0);
      
      close(comm_sock);
       
      printf("Connection ended\n");
    }
  }
  
  /* Note the server never explicitly exits or closes the listen socket,
   * but the socket will be closed when the program is killed or 
   * terminates. */
}
