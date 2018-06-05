#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

// imprime el contenido de la pagina del servidor
void get_home_page(int socket_fd)
{
  // Un arreglo lo suficientemente grande para que contenga el codigo fuente de la pagina web
  char buffer[10000];
  ssize_t num_caracteres_leidos;

  // Envia el comando GET
  sprintf(buffer, "GET\n");
  // Escribe al socket del servidor, es decir hace una peticion
  write(socket_fd, buffer, strlen(buffer));

  while(1)
  {
    // Lee la respuesta del servidor y la almacena en el arreglo buffer
    num_caracteres_leidos = read(socket_fd, buffer, 10000);
    // cuando los caracteres leidos sean cero, sale del metodo con el return y termina
    if( num_caracteres_leidos == 0 )
      return;
    // escribe el contenido del arreglo buffer al stdout o sea el monitor
    fwrite(buffer, sizeof(char), num_caracteres_leidos,stdout);
  }
}

int main(int argc, char* const argv[])
{
  // el descriptor de archivo
  int socket_fd;
  // la estructura de tipo sockadd_in
  struct sockaddr_in direccion;
  // el apuntador a la estructura hostent que devuelve la funcion
  // gethostbyname()
  struct hostent* hostinfo;

  // llamada a la funcion socket para inicializar el descriptor
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  // se inicializa el atributo sin_family
  direccion.sin_family = AF_INET;
  // se obtiene el argumento y se pasa a gethostbyname()
  // si es NULL retorna 1 y termina anormalmente
  hostinfo = gethostbyname( argv[1] );
  if( hostinfo== NULL)
    return 1;
  // en caso exitoso, se obtiene la primera direccion y se pasa a sin_addr
  else
    direccion.sin_addr = *((struct in_addr *)hostinfo -> h_addr);
  // se pasa el puerto 80 que es el puerto default para HTTP
  direccion.sin_port = htons( 80 );

  // si connect devuelve -1, es error y termina anormalmente
  if( connect(socket_fd,(struct sockaddr*)&direccion, sizeof(struct sockaddr_in)) == -1 )
  {
    perror("error al conectar\n");
    return 1;
  }

  // se llama a la funcion get_home_page pasando el descriptor
  get_home_page(socket_fd);
  return 0;
}
