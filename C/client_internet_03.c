#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <limits.h>

#define PORT 4897

main(int argc, char *argv[])
{
  struct sockaddr_in server;
  struct hostent *sp;
  int sd;
  int n;
  char *host;
  char buf[LINE_MAX];

  sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  memset((char *) &server, 0, sizeof(struct sockaddr_in));
  server.sin_family = AF_INET;
  server.sin_port = htons((u_short) PORT);
  sp = gethostbyname(argv[1]);
  memcpy(&server.sin_addr, sp->h_addr, sp->h_length);

  connect(sd, (struct sockaddr *) &server, sizeof(struct sockaddr_in));

  fgets(buf, LINE_MAX, stdin);
  printf("El mensaje al servidor es %s\n", buf);
  send( sd, buf, strlen(buf), 0 );

  n = read ( sd, buf, sizeof(buf) );
  printf(" n=%d ",n);
  printf(" buf=%s ",buf);

  close(sd);
  exit(0);
}
