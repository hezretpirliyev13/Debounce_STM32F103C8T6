#ifndef _BOUNCE_H
#define _BOUNCE_H

#ifdef MCU_STM32F103C8
#pragma message("STM32F103C8T6 microcontroller found")
#include "board/board.h"
#include "io.h"
#include <cstdint>
#include "wirish_time.h"


class Bounce {
public:
  Bounce();
  Bounce(uint8_t pin, unsigned long interval_millis);
  void begin();
  void attach(int pin);
  void interval(unsigned long interval_millis);
  bool update();
  void rebounce(unsigned long interval);
  int16_t read();
  void write(int new_state);
  unsigned long duration();
  bool risingEdge();
  bool fallingEdge();
  char *_text(void);

protected:
  uint16_t debounce();
  uint16_t previous_millis, interval_millis, rebounce_millis;
  uint8_t state;
  uint8_t pin;
  uint8_t stateChanged;
  bool supported = false;
  const uint8_t _tolerant_pins[18] = {
    PB12,
    PB13,
    PB14,
    PB15,
    PA8,
    PA11,
    PA12,
    PA13,
    PA14,
    PA15,
    PB3,
    PB4,
    PB6,
    PB7,
    PB8,
    PB9,
    PB10,
    PB11
  };
};
#endif

#endif
