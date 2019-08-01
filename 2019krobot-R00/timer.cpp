#include "timer.h"

void Timer::set(unsigned long t) {
  settime = t;
  lasttime = millis();
  defined = true;
}

bool Timer::check() {
  if (defined == false)return false;
  if (millis() - lasttime >= settime) {
    lasttime = millis();
    return true;
  }
  return false;
}
