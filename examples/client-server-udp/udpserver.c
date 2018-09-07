/* 
 * udpserver - an example Internet server using UDP.
 *
 * Reads messages from a UDP socket and prints them to stdout.
 * 
 * usage: ./udpserver
 *  and ctrl-C to exit.
 *
 * David Kotz - May 2016, May 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>	      // bool type
#include <unistd.h>	      // read, write, close
#include <strings.h>	      // bcopy, bzero
#include <arpa/inet.h>	      // socket-related calls

/**************** file-local constants ****************/
static const int BUFSIZE = 1024;     // read/write buffer size

/**************** main() ****************/
int
main(const int argc, char *argv[])
{
  // no arguments to parse

  // Create socket on which to listen (file descriptor)
  int comm_sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (comm_sock < 0) {
    perror("opening datagram socket");
    exit(1);
  }

  // Name socket using wildcards
  struct sockaddr_in server;  // server address
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 0;
  if (bind(comm_sock, (struct sockaddr *) &server, sizeof(server))) {
    perror("binding socket name");
    exit(2);
  }

  // Print our assigned port number
  socklen_t serverlen = sizeof(server);	// length of the server address
  if (getsockname(comm_sock, (struct sockaddr *) &server, &serverlen)) {
    perror("getting socket name");
    exit(3);
  }
  printf("Ready at port %d\n", ntohs(server.sin_port));
  printf("To find your MacOS IP address, ifconfig | grep 'inet '\n");
  
  // Receive datagrams and print them out
  while (true) {
    char buf[BUFSIZE];	      // buffer for reading data from socket
    struct sockaddr_in them;  // sender's address
    struct sockaddr *themp = (struct sockaddr *) &them;
    socklen_t themlen = sizeof(them);
    int nbytes = recvfrom(comm_sock, buf, BUFSIZE-1, 0, themp, &themlen);

    if (nbytes < 0) {
      perror("receiving from socket");
      exit(1);
    } else {      
      buf[nbytes] = '\0';     // null terminate string

      // where was it from?
      if (them.sin_family != AF_INET) {
	printf("From non-Internet address: Family %d\n", them.sin_family);
      } else {
	printf("From %s, port %d: '%s'\n", 
	       inet_ntoa(them.sin_addr),
	       ntohs(them.sin_port), 
	       buf);
      }

      // echo it back to the client
      if (sendto(comm_sock, buf, nbytes, 0, 
		 (struct sockaddr *) &them, sizeof(them)) < 0) {
	perror("sending in datagram socket");
	exit(6);
      }
    }
  }
  
  close(comm_sock);

  /* Note the server never explicitly exits or closes the socket,
   * but the socket will be closed when the program is killed or 
   * terminates. */    
}
