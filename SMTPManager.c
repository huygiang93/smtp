//
//  SMTPManager.c
//  SMTP

#include "SMTPManager.h"
#include <stdlib.h>
#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h>
#include <WinSock2.h>
#include <stdio.h>
#include <errno.h>
#include <sys/time.h>		/* for gettimeofday() */
#include <strings.h>


struct SMTPClient *createSMTPClient(void) {
  struct SMTPClient *ptr = (struct SMTPClient *)malloc(sizeof(struct SMTPClient));


  int socket;
  struct sockaddr_in rcvr; 	
  struct hostent *hp, *gethostbyname();
  int buflen = 1500;
  char *buf=(char*)malloc(buflen);
  int optlen;
  struct timeval sndtime;
  struct timezone zone;
  int rval, seqno;


  /* create socket */
  socket = socket(AF_INET, SOCK_STREAM, 0);
  if(socket < 0) {
    perror("Opening stream socket");
    exit(1);
  }

  /* Create rcvr socket address using command line arguments */
  rcvr.sin_family = AF_INET;
  hp = gethostbyname(argv[1]);
  if(hp == 0) {
    printf("%s: unknown host\n",argv[1]);
    exit(2);
  }
  bcopy(hp->h_addr, &rcvr.sin_addr, hp->h_length);
  rcvr.sin_port = htons(atoi(argv[2]));

  /* connect socket using name specified at command line */
  if(connect(socket, (struct sockaddr *)&rcvr, sizeof(rcvr)) < 0) {
    perror("connecting stream socket");
    exit(1);
  }

  if (gettimeofday(&sndtime, &zone) < 0) {
    perror("Getting time");
  }
  printf("Start time: %ld %ld\n", sndtime.tv_sec, sndtime.tv_usec);
  printf("Socket created \n");
  printf("socket: %d\n", socket);
  ptr->socket= socket;
  ptr->buflen=buflen;
  ptr->buf=buf;

  return ptr;
}

void closeClient(SMTPClient *ptr) {
  free(ptr->buf);
  close ptr->socket;
}
