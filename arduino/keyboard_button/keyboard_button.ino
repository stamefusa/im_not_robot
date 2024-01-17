#include <Keyboard.h>

int pin = 3;

int val = 0, pre_val = 0;

void setup() {
  //Serial.begin(9600);
  Keyboard.begin();
  pinMode(pin, INPUT_PULLUP);
}

void loop() {
  val = digitalRead(pin);
  //Serial.println(val);
  if ((pre_val == 1 && val == 0)
  || (pre_val == 0 && val == 1)) {
    Keyboard.press('q');
  }
  pre_val = val;
  delay(100);
  Keyboard.releaseAll();
}