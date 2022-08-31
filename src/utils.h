#ifndef _MS_UTILS_h
#define _MS_UTILS_h
#include <Arduino.h>

char* mUtoa(uint32_t value, char *buffer, bool clear = 1);
char* mLtoa(int32_t value, char *buffer, bool clear = 1);
char* mFtoa(double value, int8_t decimals, char *buffer);
#endif