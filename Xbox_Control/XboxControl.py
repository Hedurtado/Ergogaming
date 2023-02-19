# Importar la librería para control de Xbox One
import inputs


# Mapeo de botones de Xbox One a botones del código
XBOX_BUTTON_MAP = {
    'BTN_SOUTH': BUTTON_MAP['INDEX1'],    # Botón A
    'BTN_EAST': BUTTON_MAP['MIDDLE1'],    # Botón B
    'BTN_WEST': BUTTON_MAP['RING1'],      # Botón X
    'BTN_NORTH': BUTTON_MAP['PINKY1'],    # Botón Y
    'BTN_SELECT': BUTTON_MAP['INDEX3'],   # Botón View
    'BTN_START': BUTTON_MAP['MIDDLE3'],   # Botón Menu
    'BTN_MODE': BUTTON_MAP['RING3'],      # Botón Xbox
    'BTN_THUMBL': BUTTON_MAP['THUMB'],    # Joystick izquierdo pulsado
    'BTN_THUMBR': BUTTON_MAP['MIDDLE2'],  # Joystick derecho pulsado
    'ABS_HAT0Y': BUTTON_MAP['INDEX2'],    # Cruceta arriba/abajo
    'ABS_HAT0X': BUTTON_MAP['MIDDLE2']    # Cruceta izquierda/derecha
}

# Bucle principal
while True:
    events = inputs.get_gamepad()
    for event in events:
        # Buscar el botón en el mapeo de botones de Xbox One
        xbox_button = event.ev_type + '_' + event.code
        if xbox_button in XBOX_BUTTON_MAP:
            # Obtener el número de botón correspondiente en el código
            button_num = XBOX_BUTTON_MAP[xbox_button]
            # Ejecutar la acción correspondiente
            if event.state == 0:
                perform_action(button_num, 'SHORT')
            elif event.state == 1:
                button_was_pressed[button_num] = True
                button_press_times[button_num] = int(round(time.time() * 1000))
            elif event.state == 2:
                if (int(round(time.time() * 1000)) - button_press_times[button_num] > 1000):
                    perform_action(button_num, 'LONG')
                elif button_was_pressed[button_num] and (int(round(time.time() * 1000)) - button_press_times[button_num] < 500):
                    perform_action(button_num, 'DOUBLE')
                    button_was_pressed[button_num] = False
                elif (int(round(time.time() * 1000)) - button_press_times[button_num] < 500):
                    perform_action(button_num, 'SHORT')
