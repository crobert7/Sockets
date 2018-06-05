#include <stdio.h>  
#include <stdlib.h>  
#include <limits.h>  
#include <signal.h>  
#include <sys/types.h>  
#include <sys/socket.h>  

#include <sys/un.h>           /*  para sockets UNIX  */  

#define PROTOCOLO_DEFECTO 0  

/****************************************************/  
main()  
{  
 int dfServer, dfClient, longServer, longClient;  

 struct sockaddr_un dirUNIXServer;  
 struct sockaddr_un dirUNIXClient;  

 struct sockaddr* puntSockServer;  
 struct sockaddr* puntSockClient;  
 signal ( SIGCHLD, SIG_IGN );    /*  para no crear zombies */  

 puntSockServer = ( struct sockaddr* ) &dirUNIXServer;  
 longServer = sizeof ( dirUNIXServer );  
 puntSockClient = ( struct sockaddr* ) &dirUNIXClient;  
 longClient = sizeof ( dirUNIXClient );  

 dfServer = socket ( AF_UNIX, SOCK_STREAM, PROTOCOLO_DEFECTO );  
                 /* se crea un socket UNIX, bidireccional */  
 dirUNIXServer.sun_family = AF_UNIX;    /* tipo de dominio */  
 strcpy ( dirUNIXServer.sun_path, "archivo2" );   /* nombre */  
 unlink ( "archivo2" );  
 bind ( dfServer, puntSockServer, longServer );   /* crea el archivo2 */  
                                          /* o sea, nombra el socket */  
 printf ("\n estoy a la espera \n");  
 listen ( dfServer, 5 );  
 while (1)  
   {  
     dfClient = accept ( dfServer, puntSockClient, &longClient );  
                              /* acepta la conexion cliente */  
     printf ("\n acepto la conexion \n");  
     if ( fork() == 0 )  /* crea hijo y envia archivo2 */  
       {  
         escribeFichero ( dfClient );  
         leeFichero ( dfClient );  
         close ( dfClient );        /* cierra el socket */  
         exit ( 0 );    
        }  
     else  
       close ( dfClient );      /* cierra el descriptor cliente */  
   }                            /* en el padre */  
}  

/******** funcion escribeFichero( df ) ***************/  
escribeFichero ( int df )  
{  
 // char linea1[4];
 char linea1[LINE_MAX];
 fflush(stdin);
 fgets(linea1,LINE_MAX,stdin);
 // gets(linea1);
 // scanf("%c%c%c%c",&linea1[0],&linea1[1],&linea1[2],&linea1[3]);
 // scanf("%s",linea1);
 fflush(stdin);
 printf("el mensaje al cliente es: %s\n", linea1);

 write ( df, linea1, strlen(linea1) );   
}  

leeFichero ( int df )
{
 char cad[100];
 int n = read ( df, cad, sizeof(cad) );          /* lectura de un caracter */
 printf(" n=%d ",n);
 printf(" cad=%s ",cad);
 printf("\n");
}
   
/******************   fin de servidor.c   ***********************/  
