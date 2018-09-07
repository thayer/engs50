/* 
 * udpclient - an example Internet client using UDP.
 *
 * Reads lines from stdin and sends them as messages to the given host/port.
 * 
 * usage: ./udpclient hostname port
 * 
 * David Kotz - May 2016, May 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	      // read, write, close
#include <string.h>	      // strlen
#include <strings.h>	      // bcopy, bzero
#include <netdb.h>	      // socket-related structures
#include "file.h"	      // readline

/**************** file-local constants ****************/
static const int BUFSIZE = 1024;     // read/write buffer size

/**************** main() ****************/
int
main(const int argc, char *argv[])
{
  char *program;	      // this program's name
  char *hostname;	      // server hostname
  int port;		      // server port

  // check arguments
  program = argv[0];
  if (argc != 3) {
    fprintf(stderr, "usage: %s hostname port\n", program);
    exit(1);
  } else {
    hostname = argv[1];
    port = atoi(argv[2]);
  }

  // Look up the hostname specified on command line
  struct hostent *hostp = gethostbyname(hostname);
  if (hostp == NULL) {
    fprintf(stderr, "%s: unknown host '%s'\n", program, hostname);
    exit(3);
  }

  // Initialize fields of the server address
  struct sockaddr_in server;  // address of the server
  server.sin_family = AF_INET;
  bcopy(hostp->h_addr_list[0], &server.sin_addr, hostp->h_length);
  server.sin_port = htons(port);

  // Create socket
  int comm_sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (comm_sock < 0) {
    perror("opening datagram socket");
    exit(2);
  }

  printf("Ready!\n");

  // read a line from stdin (file descriptor = 0) and write to socket
  char *line;
  while ( (line = readlinep(stdin)) != NULL) {
    // send it to the server
    if (sendto(comm_sock, line, strlen(line), 0, 
	       (struct sockaddr *) &server, sizeof(server)) < 0) {
      perror("sending in datagram socket");
      exit(6);
    }
    free(line);

    // wait for a response
    char buf[BUFSIZE];	      // buffer for reading data from socket
    struct sockaddr_in them;  // sender's address
    struct sockaddr *themp = (struct sockaddr *) &them;
    socklen_t themlen = sizeof(them);
    int nbytes = recvfrom(comm_sock, buf, BUFSIZE-1, 0, themp, &themlen);

    // if a response, print it
    if (nbytes < 0) {
      perror("receiving from socket");
      exit(1);
    } else {      
      buf[nbytes] = '\0';     // null terminate string
      puts(buf);
    }
  }
  
  close(comm_sock);

  return 0;
}
