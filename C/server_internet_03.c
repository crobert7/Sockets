#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <limits.h>

#define PORT 4897

main()
{
  struct sockaddr_in server;
  struct sockaddr_in client;
  struct hostent *info_client;
  int sd, td, n;
  int longClient;
  char buf[256];
  char mensaje[200];

  sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	      
  memset((char *) &server, 0, sizeof(struct sockaddr_in));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons((u_short) PORT);

  bind(sd, (struct sockaddr *) &server, sizeof(struct sockaddr_in));

  listen(sd, 20);

  while (1) {
    longClient = sizeof(struct sockaddr_in);
    td = accept(sd, (struct sockaddr *) &client, &longClient);

    info_client = gethostbyaddr((char *) &client.sin_addr, sizeof(struct in_addr), AF_INET);
    printf("Conectado desde %s\n", info_client->h_name);

    n = read ( td, buf, sizeof(buf) );
    printf(" n=%d ",n);
    printf(" buf=%s ",buf);

    fgets(buf, LINE_MAX, stdin);
    printf("El mensaje al cliente es %s\n", buf);
    send( td, buf, strlen(buf), 0 );

    close(td);
  }
}

