#include <Keyboard.h>

const int NUM_BUTTONS = 13;
const byte BUTTON_PINS[NUM_BUTTONS] = {
  2, 3, 4,
  5, 6, 7,
  8, 9, 10,
  11, 12, 13,
  A0
};

const char* BUTTON_NAMES[NUM_BUTTONS] = {
  "INDEX1", "INDEX2", "INDEX3",
  "MIDDLE1", "MIDDLE2", "MIDDLE3",
  "RING1", "RING2", "RING3",
  "PINKY1", "PINKY2", "PINKY3",
  "THUMB"
};

const char BUTTON_MAP[NUM_BUTTONS] = {
  'R', 'F', 'V',
  'E', 'D', 'C',
  'W', 'S', 'X',
  'Q', 'A', 'Z',
  KEY_BACKSPACE
};

void setup() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  
  Keyboard.begin();
}
void loop() {
  static unsigned long lastActionTime = 0;  // variable para almacenar el tiempo de la última acción
  const unsigned long actionInterval = 50;  // intervalo de tiempo entre acciones (50 ms en este ejemplo)

  for (int i = 0; i < NUM_BUTTONS; i++) {
    if (digitalRead(BUTTON_PINS[i]) == LOW) {
      if (millis() - lastActionTime >= actionInterval) {  // verificar si ha pasado suficiente tiempo desde la última acción
        Keyboard.press(BUTTON_MAP[i]);
        Keyboard.release(BUTTON_MAP[i]);
        lastActionTime = millis();  // actualizar el tiempo de la última acción
      }
    }
  }
}

