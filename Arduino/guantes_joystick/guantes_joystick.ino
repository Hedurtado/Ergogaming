//Inicia depuracion y definicion de elementos para un manejo mas rapido
#ifdef DEBUG
#define KEY_BEGIN()
#define KEY_PRESS(x)
#define KEY_RELEASE(x)
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
// Key constants, numeric values used in DEBUG mode
#define KEY_LEFT_CTRL 128
#define KEY_LEFT_SHIFT 129
#define KEY_LEFT_ALT 130
#define KEY_LEFT_GUI 131
#define KEY_RIGHT_CTRL 132
#define KEY_RIGHT_SHIFT 133
#define KEY_RIGHT_ALT 134
#define KEY_RIGHT_GUI 135
#define KEY_UP_ARROW 218
#define KEY_DOWN_ARROW 217
#define KEY_LEFT_ARROW 216
#define KEY_RIGHT_ARROW 215
#define KEY_BACKSPACE 178
#define KEY_TAB 179
#define KEY_RETURN 176
#define KEY_ESC 177
#define KEY_INSERT 209
#define KEY_DELETE 212
#define KEY_PAGE_UP 211
#define KEY_PAGE_DOWN 214
#define KEY_HOME 210
#define KEY_END 213
#define KEY_CAPS_LOCK 193
#define KEY_F1 194
#define KEY_F2 195
#define KEY_F3 196
#define KEY_F4 197
#define KEY_F5 198
#define KEY_F6 199
#define KEY_F7 200
#define KEY_F8 201
#define KEY_F9 202
#define KEY_F10 203
#define KEY_F11 204
#define KEY_F12 205
#else
#include <Keyboard.h>
#define KEY_BEGIN() Keyboard.begin()
#define KEY_PRESS(x) Keyboard.press(x)
#define KEY_RELEASE(x) Keyboard.release(x)
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif
// ------------ //

//Globals | Constantes globales
const int xCenter = 250;    // Tweak for your D-pad's center values, should be 250
const int yCenter = 250;
const int xDeadband = 10;  // Sets the size of the center deadband
const int yDeadband = 10;


//Constantes para el joystick
enum DPadDirection {
  dPadNone = 0,
  dPadUp = 'p',
  dPadDn = 'b',
  dPadLt = 'a',
  dPadRt = 't'
};
 

// Se crea una estrucuta para dKey de 3 tipos: entero, caracter y boleano
typedef struct {
  int pin;
  char cmd;
  bool wasPressed;
} dKey;

// Switch pins, {PIN, KEY, False} | Se usa la estructura dKey como dSwitch y se colocan los pines que se van a usar, que letra/comando 
// representa, el 'false' se usa para leer el estado del boton, si fue pulsado o no.
dKey dSwitch[] = {
  {19, 'p', false}, // Pin 19 = A1
  {2, 'y', false},
  {3, 'q', false},
  {4, 'f', false},
  {5, 'w', false},
  {6, '2', false},
  {7, 'm', false},
  {8, 'e', false},
  {9, 'g', false},
  {10, 'j', false},
  {16, 'u', false},
  {14, KEY_TAB, false},
  {15, 'r', false}
};

void setup() {
  Serial.begin(9600);
  KEY_BEGIN(); //Inicializa el programa
  // Pin Mode setup
  for (int i = 0; i <= 12; i++) {
    pinMode(dSwitch[i].pin, INPUT_PULLUP);//Se inicia un bucle for para leer los 13 estados de los botones, el .pin leera que botones estan conectados a la board
  }
  // Shows key mapping if in DEBUG
  #ifdef DEBUG
  while (!Serial);  // Wait for serial to come up
  DEBUG_PRINTLN("Key mapping: ");
  DEBUG_PRINT("Pin\t");
  DEBUG_PRINTLN("Key");
  for (int i = 0; i <= 12; i++) {
    DEBUG_PRINT(dSwitch[i].pin); //Lo mismo de arriba, sin embargo, el .cmd vera que letras o comando representa cada pin
    DEBUG_PRINT('\t');
    DEBUG_PRINTLN(dSwitch[i].cmd);
  }
  DEBUG_PRINTLN();
  #endif
}

void loop() {
  readJoystick();
  readKeys();
}



void readJoystick() {
  static char lastKeyPressed = dPadNone;
  int joyX = analogRead(A2);
  int joyY = analogRead(A3);
  
  // Check if joystick is centered
  if (joyX < (xCenter + xDeadband) && joyX > (xCenter - xDeadband) && joyY < (yCenter + yDeadband) && joyY > (yCenter - yDeadband)) {
    if (lastKeyPressed != dPadNone) {
      KEY_RELEASE(lastKeyPressed);
      lastKeyPressed = dPadNone;
      DEBUG_PRINTLN("Joystick released");
    }
    return;
  }
  joyX = 1023 - joyX;
  joyY = 0 - joyY;
  // Determine which direction the joystick is in
  DPadDirection direction = dPadNone;
  if ((joyX > 310) && (joyX < 370)) {
  direction = dPadLt;
} else if ((joyX > 10) && (joyX < 70)) {
  direction = dPadRt;
} else if ((joyY > 310) && (joyY < 370)) { 
  direction = dPadDn;
} else if ((joyY > 10) && (joyY < 70)) {
  direction = dPadUp;}

  
  // Send the key press if it has changed
  if (lastKeyPressed != direction) {
    if (lastKeyPressed != dPadNone) {
      KEY_RELEASE(lastKeyPressed);
      DEBUG_PRINTLN("Joystick released");
    }
    lastKeyPressed = direction;
    KEY_PRESS(direction);
    DEBUG_PRINTLN("Joystick pressed");
  }
}




void readKeys() {
  for (int i = 0; i <= 12; i++)  {
    if (digitalRead(dSwitch[i].pin) == LOW) {//Arriba se inicializo el .pin como input_pullup, esto es para tener un valor conocido y asi, si hay un cambio sera mas facil y eficiente detectarlo
      if (dSwitch[i].wasPressed == false)  {// Aqui si el estado boleano es false detecta que fue presionado 
        KEY_PRESS(dSwitch[i].cmd)
        DEBUG_PRINT("Key press:\t");
        DEBUG_PRINT(dSwitch[i].pin);
        DEBUG_PRINT('\t');
        DEBUG_PRINTLN (dSwitch[i].cmd);
        dSwitch[i].wasPressed = true; // luego lo cambia a true para que al momento de soltar el boton se detecte el cambio y vuelva a cambiar de estado
      }
    }
    else  {
      if (dSwitch[i].wasPressed == true)  {// Aqui se detecta si la tecla presionada es igual a true, si es asi se entendera que la solto 
        KEY_RELEASE(dSwitch[i].cmd);
        DEBUG_PRINT("Key released:\t");
        DEBUG_PRINT(dSwitch[i].pin);
        DEBUG_PRINT('\t');
        DEBUG_PRINTLN (dSwitch[i].cmd);
        dSwitch[i].wasPressed = false;// devuelve la tecla al estado inicial
      }
    }
  }
}
