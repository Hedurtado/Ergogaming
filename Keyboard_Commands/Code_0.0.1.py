import keyboard
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


button_was_pressed = [False] * 13


# Función para realizar una acción en función del botón y tipo de pulsación
def perform_action(button, press_type):
    # Ejemplo: pulsar las teclas 'W', 'A', 'S' o 'D' en función del botón
    if press_type == 'SHORT':
        if button == BUTTON_MAP['INDEX1']:
            keyboard.press('R')
            time.sleep(0.1)
            keyboard.release('R')
        elif button == BUTTON_MAP['INDEX2']:
            keyboard.press('F')
            time.sleep(0.1)
            keyboard.release('F')
        elif button == BUTTON_MAP['INDEX3']:
            keyboard.press('V')
            time.sleep(0.1)
            keyboard.release('V')
        elif button == BUTTON_MAP['MIDDLE1']:
            keyboard.press('E')
            time.sleep(0.1)
            keyboard.release('E')
        elif button == BUTTON_MAP['MIDDLE2']:
            keyboard.press('D')
            time.sleep(0.1)
            keyboard.release('D')
        elif button == BUTTON_MAP['MIDDLE3']:
            keyboard.press('C')
            time.sleep(0.1)
            keyboard.release('C')
        elif button == BUTTON_MAP['RING1']:
            keyboard.press('W')
            time.sleep(0.1)
            keyboard.release('W')
        elif button == BUTTON_MAP['RING2']:
            keyboard.press('S')
            time.sleep(0.1)
            keyboard.release('S')
        elif button == BUTTON_MAP['RING3']:
            keyboard.press('X')
            time.sleep(0.1)
            keyboard.release('X')
        elif button == BUTTON_MAP['PINKY1']:
            keyboard.press('Q')
            time.sleep(0.1)
            keyboard.release('Q')
        elif button == BUTTON_MAP['PINKY2']:
            keyboard.press('A')
            time.sleep(0.1)
            keyboard.release('A')
        elif button == BUTTON_MAP['PINKY3']:
            keyboard.press('Z')
            time.sleep(0.1)
            keyboard.release('Z')
        elif button == BUTTON_MAP['THUMB']:
            keyboard.press('SPACE')
            time.sleep(0.1)
            keyboard.release('SPACE')


# Bucle principal
while True:
    # Leer el estado de los botones desde el Arduino
    button_states = ser.readline().decode().strip().split()

    # Detectar pulsación
    for i, state in enumerate(button_states):
        # Si el botón se acaba de pulsar, realizar la acción correspondiente
        if state == '0' and not button_was_pressed[i]:
            perform_action(i, 'SHORT')
            button_was_pressed[i] = True
        # Si el botón se acaba de soltar, marcarlo como no pulsado
        elif state == '1' and button_was_pressed[i]:
            button_was_pressed[i] = False
