import serial
import time

# Configuración de la comunicación serial
ser = serial.Serial('COM3', 9600)

# Diccionario que asocia cada botón con un número
BUTTON_MAP = {
    'INDEX1': 0,
    'INDEX2': 1,
    'INDEX3': 2,
    'MIDDLE1': 3,
    'MIDDLE2': 4,
    'MIDDLE3': 5,
    'RING1': 6,
    'RING2': 7,
    'RING3': 8,
    'PINKY1': 9,
    'PINKY2': 10,
    'PINKY3': 11,
    'THUMB': 12
}

# Variables para la detección de doble pulsación y pulsación larga
button_press_times = [0] * 13
button_was_pressed = [False] * 13


# Función para realizar una acción en función del botón y tipo de pulsación
def perform_action(button, press_type):
    # Ejemplo: imprimir un mensaje en función del botón y tipo de pulsación
    if press_type == 'SHORT':
        print(f'Short press on button {button}')
    elif press_type == 'LONG':
        print(f'Long press on button {button}')
    elif press_type == 'DOUBLE':
        print(f'Double press on button {button}')


# Bucle principal
while True:
    # Leer el estado de los botones desde el Arduino
    button_states = ser.readline().decode().strip().split()

    # Detectar doble pulsación y pulsación larga
    for i, state in enumerate(button_states):
        button_num = i
        # Si el botón se acaba de pulsar, guardar el tiempo actual
        if state == '0' and not button_was_pressed[i]:
            button_press_times[i] = int(round(time.time() * 1000))
            button_was_pressed[i] = True
        # Si el botón se acaba de soltar, marcarlo como no pulsado
        elif state == '1' and button_was_pressed[i]:
            button_was_pressed[i] = False
        # Si el botón ha sido pulsado durante un tiempo determinado, marcarlo como pulsación larga
        if state == '0' and (int(round(time.time() * 1000)) - button_press_times[i] > 1000):
            perform_action(button_num, 'LONG')
        # Si el botón ha sido pulsado dos veces en un corto periodo de tiempo, marcarlo como doble pulsación
        if state == '0' and button_was_pressed[i] and (int(round(time.time() * 1000)) - button_press_times[i] < 500):
            perform_action(button_num, 'DOUBLE')
            button_was_pressed[i] = False
        # Si el botón ha sido pulsado durante un corto periodo de tiempo, marcarlo como pulsación corta
        if state == '0' and (int(round(time.time() * 1000)) - button_press_times[i] < 500):
            perform_action(button_num, 'SHORT')
