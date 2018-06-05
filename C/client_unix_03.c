/************************************************************/  
/**************                         cliente.c           **********************/  
/************************************************************/  
/*********                   proceso cliente con sockets AF_UNIX   **********/  
/************************************************************/  

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
 int dfClient, longServer, resultado;  
 struct sockaddr_un dirUNIXServer;  
 struct sockaddr* puntSockServer;  

 puntSockServer = ( struct sockaddr* ) &dirUNIXServer;  
 longServer = sizeof ( dirUNIXServer );  

 dfClient = socket ( AF_UNIX, SOCK_STREAM, PROTOCOLO_DEFECTO );  
                 /* se crea un socket UNIX, bidireccional */  

 dirUNIXServer.sun_family = AF_UNIX;    /* tipo de dominio server */  
 strcpy ( dirUNIXServer.sun_path, "archivo2" );   /* nombre server */  

 do    
  {  
   resultado = connect ( dfClient, puntSockServer, longServer );  
   if ( resultado == -1 ) sleep (1);   /* reintento */  
 }  
 while ( resultado == -1 );  

 leeFichero ( dfClient );     /* lee el archivo2 */  
 escribeFichero ( dfClient );     /* escribe el archivo2 */  
 close ( dfClient );      /* cierra el socket */  
 exit (0);     /* buen fin */  

}  

/*************     leeFichero ( df )  *****************/  

leeFichero ( int df )  
{  
 char cad[100];  
 int n = read ( df, cad, sizeof(cad) );          /* lectura de un caracter */  
 printf(" n=%d ",n);
 printf(" cad=%s ",cad);
 printf("\n");
}  

escribeFichero ( int df )
{
 //char linea1[4];
 char linea1[LINE_MAX];
 fflush(stdin);
 fgets(linea1,LINE_MAX,stdin);
 // gets(linea1);
 // scanf("%c%c%c%c",&linea1[0],&linea1[1],&linea1[2],&linea1[3]);
 // scanf("%s",linea1);
 fflush(stdin);
 printf("el mensaje al servidor es: %s\n", linea1);

 write ( df, linea1, strlen(linea1) );
 // write ( df, linea1, strlen (linea1) + 1 );
 // write ( df, linea2, strlen (linea2) + 1 );  
}


/************* fin de cliente.c ****************************/  
