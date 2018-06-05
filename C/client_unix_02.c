#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

main()
{
 // este es el descriptor de archivo o file descriptor
 // para el socket cliente
 // se le asignara el valor devuelto por la funcion socket
 int socket_fd;

 // creamos el socket
 // la funcion socket devuelve un int que es el file descriptor
 socket_fd = socket (AF_UNIX, SOCK_STREAM, 0);

 // una variable de tipo struct sockaddr_un
 // que sera nuestra estructura socket cliente
 struct sockaddr_un cliente;

 // un apuntador a la variable anterior
 struct sockaddr* pcliente = (struct sockaddr*)&cliente;

 // este int almacenara el size de la estructura
 // sockaddr_un que es nuestra estructura socket cliente
 int size_cliente = sizeof(cliente);

 // el archivo con el que se nombro al socket del servidor
 const char* const socket_name = "/tmp/socket";

 // inicializamos el atributo sun_family de la struct
 cliente.sun_family = AF_UNIX;

 // inicializamos el atributo sun_path con el nombre del archivo
 strcpy( cliente.sun_path, socket_name );

 // hacemos la peticion de conexion al servidor
 int result = connect( socket_fd, pcliente, size_cliente);

 printf("connect devolvio: %d\n", result);

 if( result == 0 )
 {
  printf("enviare el mensaje \"hola mundo\" al servidor\n");
  const char* const mensaje = "hola mundo";
  int longitud = strlen( mensaje ) + 1;
  write ( socket_fd, &longitud, sizeof(longitud) );
  write ( socket_fd, mensaje, longitud );
 }

 close( socket_fd );
 exit(0);
}
