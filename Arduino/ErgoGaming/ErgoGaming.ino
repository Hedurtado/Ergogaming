// Definir los pines de los botones
const int index_buttons[] = {2, 3, 4};
const int middle_buttons[] = {5, 6, 7};
const int ring_buttons[] = {8, 9, 10};
const int pinky_buttons[] = {11, 12, 13};
const int thumb_buttons[] = {A0};

void setup() {
  // Inicializar el puerto serial a 9600 baudios
  Serial.begin(9600);

  // Configurar los pines de los botones como entradas
  for (int i = 0; i < 3; i++) {
    pinMode(index_buttons[i], INPUT_PULLUP);
    pinMode(middle_buttons[i], INPUT_PULLUP);
    pinMode(ring_buttons[i], INPUT_PULLUP);
    pinMode(pinky_buttons[i], INPUT_PULLUP);
  }
  pinMode(thumb_buttons[0], INPUT_PULLUP);
}

void loop() {
  // Leer el estado de los botones
  int button_states[13] = {
    digitalRead(index_buttons[0]),
    digitalRead(index_buttons[1]),
    digitalRead(index_buttons[2]),
    digitalRead(middle_buttons[0]),
    digitalRead(middle_buttons[1]),
    digitalRead(middle_buttons[2]),
    digitalRead(ring_buttons[0]),
    digitalRead(ring_buttons[1]),
    digitalRead(ring_buttons[2]),
    digitalRead(pinky_buttons[0]),
    digitalRead(pinky_buttons[1]),
    digitalRead(pinky_buttons[2]),
    digitalRead(thumb_buttons[0])
  };

  // Enviar los estados de los botones por el puerto serial
  for (int i = 0; i < 13; i++) {
    Serial.print(button_states[i]);
    Serial.print(" ");
  }
  Serial.println();

  // Esperar un breve tiempo antes de leer los botones de nuevo
  delay(10);
}

