import serial
import subprocess
import threading
import time
from serial.tools import list_ports

# Encontrar el puerto serial en el que está conectado el Arduino
port = None
for p in list_ports.comports():
    if 'Arduino' in p.description:
        port = p.device
if port is None:
    raise IOError("No se pudo encontrar el puerto serial del Arduino.")

# Iniciar el programa de Arduino como un proceso en segundo plano
arduino_process = subprocess.Popen(['guante_optimazao.ino'])

# Abrir el puerto serial para la comunicación con el Arduino
ser = serial.Serial(port, 9600, timeout=0.1)


# Función que envía una asignación de teclas al Arduino
def send_key_assignment(button_index, key):
    message = f'{button_index}:{key}\n'.encode('utf-8')
    ser.write(message)


# Función que lee los mensajes del Arduino
def read_messages():
    while True:
        message = ser.readline().decode('utf-8').strip()
        if message:
            parts = message.split(':')
            if len(parts) == 2:
                button_index = int(parts[0])
                key = parts[1]
                # Enviar la tecla correspondiente al sistema operativo
                # Usando la biblioteca de teclado correspondiente


# Iniciar un hilo para leer mensajes del Arduino
message_thread = threading.Thread(target=read_messages)
message_thread.start()

# Iniciar el programa de asignación de teclas como un proceso separado
key_assignment_process = subprocess.Popen(['Tkinter_Interfaz_02.py'])

# Esperar a que ambos programas terminen
arduino_process.wait()
key_assignment_process.wait()

# Cerrar el puerto serial
ser.close()
