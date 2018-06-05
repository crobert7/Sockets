#!/usr/bin/env python
# -*- coding: utf-8 -*-

"Tkinter GUI chat client"""

import socket #Biblioteca para socket
import threading #Bibiioteca para manejar hilos.
import Tkinter #biblioteca para GUI

#----Construimos socket----
HOST = input('Host: ')
PORT = input('Port: ')
if not PORT:
    PORT = 9999
else:
    PORT = int(PORT)

BUFSIZE = 1024
ADDR = (HOST, PORT)

#Nos conectamos al servidor con el metodo connect. Tiene dos parametros
#El primero es la IP del servidor y el segundo el puerto de conexion
#Ya deeclarados en la variable ADDR
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(ADDR)


def receive():

    """Maneja el recibo de mensajes."""

    while True:
        try:
            # #Recibimos el mensaje, con el metodo recv recibimos datos y como parametro
            #la cantidad de bytes para recibir
            msg = client_socket.recv(BUFSIZE)
            msg_list.insert(Tkinter.END, msg)
        except OSError:
            break

def send(event = None):  # evento lo pasa por binders.

    """Maneja el envio de mensajes."""

    msg = my_msg.get()
    my_msg.set("")  # limpia el cuadro de entrada.
    client_socket.send(msg)
    if msg == "quit":
        #Cerramos la instancia del socket del cliente
        client_socket.close()
        top.quit()

def on_closing(event = None):

    """Esta funcion se llama cuando se cierra la ventana"""

    my_msg.set("quit")
    send()

top = Tkinter.Tk()
top.title("Chat Me!")

messages_frame = Tkinter.Frame(top)
my_msg = Tkinter.StringVar()  # Para los mensajes que se envian
my_msg.set("Escribe tu mensaje aqui.")
scrollbar = Tkinter.Scrollbar(messages_frame)  # Scrollbar

# Esto contendra los mensajes
msg_list = Tkinter.Listbox(messages_frame, height=15, width=50, yscrollcommand=scrollbar.set)
scrollbar.pack(side = Tkinter.RIGHT, fill = Tkinter.Y)
msg_list.pack(side = Tkinter.LEFT, fill = Tkinter.BOTH)
msg_list.pack()
messages_frame.pack()

entry_field = Tkinter.Entry(top, textvariable = my_msg)
entry_field.bind("<Return>", send)
entry_field.pack()
send_button = Tkinter.Button(top, text = "Enviar", command = send)
send_button.pack()

top.protocol("WM_DELETE_WINDOW", on_closing)
#Inicializa el hilo(comienza a correr su funcion objetivo)
receive_thread = threading.Thread(target = receive)
receive_thread.start()
Tkinter.mainloop()  # GUI exe.
