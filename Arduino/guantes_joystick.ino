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

//Globals
const int xCenter = 250;    // Tweak for your D-pad's center values, should be 250
const int yCenter = 250;
const int xDeadband = 150;  // Sets the size of the center deadband
const int yDeadband = 150;


enum DPadDirection {
  dPadNone = '0',
  dPadUp = 'w',
  dPadDn = 's',
  dPadLt = 'a',
  dPadRt = 'd'
};


// D-pad: UP = w, RIGHT = d, DOWN = s, LEFT = a, DPadNone is "center value"
const DPadDirection dPadDnLt = dPadDn | dPadLt;
const DPadDirection dPadUpRt = dPadUp | dPadRt;
const DPadDirection dPadUpLt = dPadUp | dPadLt;
const DPadDirection dPadDnRt = dPadDn | dPadRt;


typedef struct {
  int pin;
  char cmd;
  bool wasPressed;
} dKey;

// Switch pins, {PIN, KEY, False}
dKey dSwitch[] = {
  {19, 'u', false}, // Pin 19 = A1
  {2, KEY_LEFT_SHIFT, false},
  {3, '1', false},
  {4, 'f', false},
  {5, 'q', false},
  {6, '2', false},
  {7, 'e', false},
  {8, 'x', false},
  {9, KEY_TAB, false},
  {10, 't', false},
  {16, 'b', false},
  {14, 'r', false},
  {15, '3', false}
};

void setup() {
  Serial.begin(9600);
  KEY_BEGIN();
  // Pin Mode setup
  for (int i = 0; i <= 12; i++) {
    pinMode(dSwitch[i].pin, INPUT_PULLUP);
  }
  // Shows key mapping if in DEBUG
  #ifdef DEBUG
  while (!Serial);  // Wait for serial to come up
  DEBUG_PRINTLN("Key mapping: ");
  DEBUG_PRINT("Pin\t");
  DEBUG_PRINTLN("Key");
  for (int i = 0; i <= 12; i++) {
    DEBUG_PRINT(dSwitch[i].pin);
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
  const float pi = 3.14159265358979323846;
  static char lastKeyPressed = dPadNone;
  int joyX = analogRead(A2);
  int joyY = analogRead(A3);
  float mapJoyX = map(joyX, 0, 1023, -500, 500);
  float mapJoyY = map(joyY, 0, 1023, -500, 500);

  // Determine if joystick is centered...
  if (abs(mapJoyX - xCenter) <= xDeadband && abs(mapJoyY - yCenter) <= yDeadband) {
    if (lastKeyPressed != dPadNone) {
      KEY_RELEASE(lastKeyPressed);
      lastKeyPressed = dPadNone;
      DEBUG_PRINTLN("Joystick released");
    }
  } else {  // Joystick is not centered, determine its angle
    float angle = atan2(mapJoyY - yCenter , mapJoyX - xCenter) * 180.0 / pi;
    if (angle < 0) {
      angle += 360.0; // Convert to positive degrees
    }

    // Determine which direction the joystick is in
    DPadDirection direction = dPadNone;
    if (angle >= 22.5 && angle < 67.5) {
      direction = dPadUpRt;
    } else if (angle >= 67.5 && angle < 112.5) {
      direction = dPadUp;
    } else if (angle >= 112.5 && angle < 157.5) {
      direction = dPadUpLt;
    } else if ((angle >= 157.5 && angle <= 180) || (angle >= 0 && angle < 22.5)) {
      direction = dPadLt;
    } else if (angle >= 202.5 && angle < 247.5) {
      direction = dPadDnLt;
    } else if (angle >= 247.5 && angle < 292.5) {
      direction = dPadDn;
    } else if (angle >= 292.5 && angle < 337.5) {
      direction = dPadDnRt;
    } else if (angle >= 337.5 && angle < 360) {
      direction = dPadRt;
    }

    // Send the key press if it has changed
    if (direction != dPadNone && direction != lastKeyPressed) {
      if (lastKeyPressed != dPadNone) {
        KEY_RELEASE(lastKeyPressed);
      }
      lastKeyPressed = direction;
      KEY_PRESS(direction);
      DEBUG_PRINT("Key pressed: ");
      DEBUG_PRINTLN(direction);
    }
  }
}

void readKeys() {
  for (int i = 0; i <= 12; i++)  {
    if (digitalRead(dSwitch[i].pin) == LOW) {
      if (dSwitch[i].wasPressed == false)  {
        KEY_PRESS(dSwitch[i].cmd)
        DEBUG_PRINT("Key press:\t");
        DEBUG_PRINT(dSwitch[i].pin);
        DEBUG_PRINT('\t');
        DEBUG_PRINTLN (dSwitch[i].cmd);
        dSwitch[i].wasPressed = true;
      }
    }
    else  {
      if (dSwitch[i].wasPressed == true)  {
        KEY_RELEASE(dSwitch[i].cmd);
        DEBUG_PRINT("Key released:\t");
        DEBUG_PRINT(dSwitch[i].pin);
        DEBUG_PRINT('\t');
        DEBUG_PRINTLN (dSwitch[i].cmd);
        dSwitch[i].wasPressed = false;
      }
    }
  }
}
