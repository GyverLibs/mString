#include "utils.h"

char* mUtoa(uint32_t value, char *buffer, bool clear) {
    buffer += 11;
    if (clear) *--buffer = 0;
    do {
        *--buffer = value % 10 + '0';
        value /= 10;
    } while (value != 0);
    return buffer;
}

char* mLtoa(int32_t value, char *buffer, bool clear) {
    bool minus = value < 0;
    if (minus) value = -value;
    buffer = mUtoa(value, buffer, clear);
    if (minus) *--buffer = '-';
    return buffer;
}

char* mFtoa(double value, int8_t decimals, char *buffer) {
  if (value < 0) {
    value = -value;
    *buffer++ = '-';
  }
  int32_t mant = (int32_t)value;
  value -= mant;
  uint32_t exp = 1;
  while (decimals--) exp *= 10;
  exp *= (float)value;
  buffer = ltoa(mant, buffer, DEC);
  byte len = strlen(buffer);
  *(buffer + len++) = '.';
  ltoa(exp, buffer + len++, DEC);
  return buffer;
}
