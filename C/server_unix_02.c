#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

main()
{
 // este es el descriptor de archivo o file descriptor
 // para el socket servidor
 // se le asignara el valor devuelto por la funcion socket
 int socket_fd;

 // creamos el socket
 // la funcion socket devuelve un int que es el file descriptor
 socket_fd = socket (AF_UNIX, SOCK_STREAM, 0);

 // una variable de tipo struct sockaddr_un
 // que sera nuestra estructura socket servidor
 struct sockaddr_un servidor;

 // un apuntador a la variable anterior
 struct sockaddr* pservidor = (struct sockaddr*)&servidor;

 // este int almacenara el size de la estructura
 // sockaddr_un que es nuestra estructura socket servidor
 int size_servidor = sizeof(servidor);

 // el archivo con el que se nombrara al socket
 // el archivo no debe existir y se creara con size 0
 const char* const socket_name = "/tmp/socket";

 // inicializamos el atributo sun_family de la struct
 servidor.sun_family = AF_UNIX;

 // inicializamos el atributo sun_path con el nombre del archivo
 strcpy( servidor.sun_path, socket_name );

 // ligamos/asociamos el socket al archivo, para que sea un socket nombrado
 bind( socket_fd, pservidor, size_servidor );

 // ponemos al servidor a que escuche por peticiones de conexion de un cliente
 listen( socket_fd, 1 );

 // creamos una estructura cliente en el servidor
 // para que se conecte con el socket en el cliente,
 // es quien atendera al cliente
 struct sockaddr_un cliente;

 // un apuntador a la variable anterior
 struct sockaddr* pcliente = (struct sockaddr*)&cliente;

 // este int almacenara el size de la estructura
 // sockaddr_un que es nuestra estructura cliente socket
 int size_cliente = sizeof(cliente);

 // este es el descriptor de archivo o file descriptor
 // para el socket cliente
 // se le asignara el valor devuelto por la funcion accept
 int cliente_socket_fd;

 // el servidor acepta la conexion del cliente
 cliente_socket_fd = accept( socket_fd, pcliente, &size_cliente );
 printf( "accept devolvio:  %d\n", cliente_socket_fd );

 // como el cliente escribe, el servidor lee
 char* mensaje;
 int longitud;
 // primero se lee la longitud del mensaje enviado por el cliente
 // se lee a traves del socket cliente en el lado del servidor
 // Si read() devuelve cero, es porque el cliente cerro la conexion
 if( read( cliente_socket_fd, &longitud, sizeof(longitud) ) == 0 )
 {
  printf("el cliente cerro la conexion\n");
  return 0;
 }

 printf( "longitud:  %d\n", longitud );
 
 // se reserva la memoria para mantener el texto del mensaje
 mensaje = (char*)malloc(longitud);

 // Se lee el mensaje y se imprime en pantalla
 read( cliente_socket_fd, mensaje, longitud );
 printf("mensaje: %s\n", mensaje);

 // este sleep es para hacer tiempo y poder ver el archivo /tmp/socket
 sleep( 10 );

 // Se cierra el descriptor del socket cliente
 close( cliente_socket_fd );
 // Se cierra el descriptor del socket servidor
 close( socket_fd );
 // Se desliga el archivo del socket servidor
 unlink( socket_name );
 // buen fin
 exit(0);
}
