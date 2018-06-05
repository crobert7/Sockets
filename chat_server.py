#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""Server para chat asíncrono"""

import socket #Biblioteca para socket
import threading

#----Construimos socket----
clients = {}
addresses = {}

HOST = '' #Dejamos puerto abierto para que podamos elegir nosotros a que IP haremos la conexion
PORT = 9999 #Puerto puede ser cualquiera a apartir del 1024
BUFSIZE = 1024  #Tamaño del buffer
ADDR = (HOST, PORT)

#instanciamos un objeto para trabajar con el socket
SERVER = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#Con el metodo bind le indicamos que puerto debe escuchar y de que servidor esperar conexiones
SERVER.bind(ADDR)


def accept_connections():

    """Funcion para manejar los clientes que se conectan"""

    while True:

        # acepta conexiones externas
        client, client_address = SERVER.accept()
        print("%s:%s se ha conectado" %client_address)
        # manda mensaje "Hola escribe tu nombre"
        client.send("Hola escribe tu nombre y presiona enter!")
        addresses[client] = client_address
        #Inicializa el hilo(que comience a correr su funcion objetivo)
        threading.Thread(target = client_handle, args = (client, )).start()

def client_handle(client): #Toma el socket del cliente como argumento

    """Maneja una sola conexion del cliente"""

    name = client.recv(BUFSIZE)
    welcome = 'Bienvenido %s! Si en algún momento deseas salir teclea quit ' % name
    client.send(welcome)
    msg = "%s se ha unido a la sala!" % name
    broadcast(msg)
    clients[client] = name

    while True:

        #Recibimos el mensaje, con el metodo recv recibimos datos y como parametro
        #la cantidad de bytes para recibir
        msg = client.recv(BUFSIZE)
        #Si el mensaje recibido es la palabra quit se cierra la aplicacion
        if msg != "quit":
            broadcast(msg, name+": ")
        else:
            client.send("quit")

            #Cerramos la instancia del cliente
            client.close()
            del clients[client]
            broadcast("%s ha dejado la sala." % name)
            break

def broadcast(msg, prefix = ""):  # prefix es para la identifiacion del nombre.

    """Broadcasts los mensajes a todos los clientes."""

    for sock in clients:
        #Devolvemos el mensaje al cliente
        sock.send(prefix + msg)


if __name__ == "__main__":

    #Aceptamos conexiones entrantes con el metodo listen, y ademas aplicamos como parametro
    #El numero de conexiones entrantes que vamos a aceptar
    SERVER.listen(5)
    print("Esperando conexion...")
    #Inicializa el hilo(comienza a correr su funcion objetivo)
    ACCEPT_THREAD = threading.Thread(target = accept_connections)
    ACCEPT_THREAD.start()
    #Hace que el programa espere a que el hilo finalice
    ACCEPT_THREAD.join()
    #Cerramos la inatnacia del servidor
    SERVER.close()
