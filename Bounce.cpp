#include "io.h"
#include "Bounce.h"
Bounce::Bounce(uint8_t pin, unsigned long interval_millis) {
  for (uint8_t i = 0; i < sizeof(_tolerant_pins); i++) {
    pin == _tolerant_pins[i];
    supported = true;
    break;
  }
  if (supported) {
    interval(interval_millis);
    previous_millis = millis();
    state = digitalRead(pin);
    this->pin = pin;
  } else {
    #pragma message( "You chose 5V non tolerant pins, or are you sure is that push button will not damage the microcontroller?!");
    while (1) {}
  }
}
Bounce::Bounce() {
  this->interval_millis = 10;
}
void Bounce::attach(int pin) {
  previous_millis = millis();
  state = digitalRead(pin);
  this->pin = pin;
}

void Bounce::begin() {
  pinMode(pin, INPUT);
}
void Bounce::write(int new_state) {
  this->state = new_state;
  digitalWrite(pin, state);
}
void Bounce::interval(unsigned long interval_millis) {
  this->interval_millis = interval_millis;
  this->rebounce_millis = 0;
}
void Bounce::rebounce(unsigned long interval) {
  this->rebounce_millis = interval;
}
bool Bounce::update() {
  if (debounce()) {
    rebounce(0);
    return stateChanged = 1;
  }
  if (rebounce_millis && (millis() - previous_millis >= rebounce_millis)) {
    previous_millis = millis();
    rebounce(0);
    return stateChanged = 1;
  }
  return stateChanged = 0;
}
unsigned long Bounce::duration() {
  return millis() - previous_millis;
}
int16_t Bounce::read() {
  return (int)state;
}
uint16_t Bounce::debounce() {
  uint8_t new_state = digitalRead(pin);
  if (state != new_state) {
    if (millis() - previous_millis >= interval_millis) {
      previous_millis = millis();
      state = new_state;
      return 1;
    }
  }
  return 0;
}
bool Bounce::risingEdge() {
  return stateChanged && state;
}
bool Bounce::fallingEdge() {
  return stateChanged && !state;
}
char *_text(void) {
  return "Sorry you chose not 5V tolerant pins";
}
