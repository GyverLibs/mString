/*
    РЕЗКАЯ КАК ПОНОС И ЛЁГКАЯ КАК ПЁРЫШКО ЗАМЕНА STRING
    Документация:
    GitHub: https://github.com/GyverLibs/mString
    Возможности:
    - Практически полный аналог String, но статический
    - Есть несколько встроенных функций парсинга строк
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.0 - релиз
    v1.1 - разбил утилиты на .h .cpp
    v1.1.1 - исправлена ошибка компиляции
    v1.2 
    - Исправлено прибавление uint32_t чисел
    - Добавлен режим внешнего буфера
    - Добавлены _P функции для строк из Flash
    - Добавлена unsplit()
    v1.3 - добавлена универсальная функция parse
    v1.4 - возможность инициализации внешнего буфера без очистки
    v1.5 - добавлена updateLength()
*/

#ifndef _mString_h
#define _mString_h

#include <Arduino.h>
#include "utils.h"

#ifndef MS_EXTERNAL
template < uint16_t _MS_SIZE >
#endif
class mString {
public:

#ifndef MS_EXTERNAL
    char buf[_MS_SIZE + 1];
    
    mString() {
        clear();
    }
    
#else
    char* buf;
    uint16_t _MS_SIZE = 0;
    
    mString(char* nbuf, uint16_t size, bool clear = true) {
        buf = nbuf;
        _MS_SIZE = size;
        if (clear) clear();
        else _len = strlen(buf);
    }
#endif

    uint16_t capacity() {
        return _MS_SIZE - 1;
    }
    
    uint16_t length() {
        return _len;
    }
    
    void clear() {
        buf[0] = '\0';
        _len = 0;
    }
    
    void updateLength() {
        _len = strlen(buf);
    }

    // add
    mString& add(const char c) {
        if (length() + 1 >= _MS_SIZE) return *this;
        buf[_len++] = c;
        buf[_len] = '\0';
        return *this;
    }
    mString& add(const char* str) {
        uint16_t plen = strlen(str);
        if (length() + plen >= _MS_SIZE) return *this;
        strcat(buf, str);
        _len += plen;
        return *this;
    }
    mString& add_P(PGM_P pstr) {
        uint16_t plen = strlen_P(pstr);
        if (length() + plen >= _MS_SIZE) return *this;
        strcpy_P(buf + length(), pstr);
        _len += plen;
        return *this;
    }
    mString& add(const __FlashStringHelper *fstr) {
        return add_P((PGM_P)fstr);
    }
    mString& add(uint32_t value) {
        char vBuf[11];
        ultoa(value, vBuf, DEC);
        return add(vBuf);
    }
    mString& add(uint16_t value) {
        char vBuf[6];
        utoa(value, vBuf, DEC);
        return add(vBuf);
    }
    mString& add(uint8_t value) {
        return add((uint16_t)value);
    }
    mString& add(int32_t value) {
        char vBuf[12];
        ltoa(value, vBuf, DEC);
        return add(vBuf);
    }
    mString& add(int16_t value) {
        char vBuf[7];
        itoa(value, vBuf, DEC);
        return add(vBuf);
    }
    mString& add(int8_t value) {
        return add((int16_t)value);
    }
    mString& add(double value, int8_t dec = 2) {
        char vBuf[20];
        mFtoa(value, dec, vBuf);
        return add(vBuf);
    }
    mString& add(mString data) {
        return add(data.buf);
    }
    mString& add(const String& data) {
        return add(data.c_str());
    }

    // add +=
    mString& operator += (const char c) {
        return add(c);
    }
    mString& operator += (const char* data) {
        return add(data);
    }
    mString& operator += (const __FlashStringHelper *data) {
        return add(data);
    }
    mString& operator += (uint32_t value) {
        return add(value);
    }
    mString& operator += (int32_t value) {
        return add(value);
    }
    mString& operator += (uint16_t value) {
        return add(value);
    }
    mString& operator += (int16_t value) {
        return add(value);
    }
    mString& operator += (uint8_t value) {
        return add(value);
    }
    mString& operator += (int8_t value) {
        return add(value);
    }
    mString& operator += (double value) {
        return add(value);
    }
    mString& operator += (mString data) {
        return add(data.buf);
    }
    mString& operator += (const String& data) {
        return add(data);
    }

    // +
    mString operator + (const char c) {
        return (*this).add(c);
    }
    mString operator + (const char* data) {
        return (*this).add(data);
    }
    mString operator + (const __FlashStringHelper *data) {
        return (*this).add(data);
    }
    mString operator + (uint32_t value) {
        return (*this).add(value);
    }
    mString operator + (int32_t value) {
        return (*this).add(value);
    }
    mString operator + (uint16_t value) {
        return (*this).add(value);
    }
    mString operator + (int16_t value) {
        return (*this).add(value);
    }
    mString operator + (uint8_t value) {
        return (*this).add(value);
    }
    mString operator + (int8_t value) {
        return (*this).add(value);
    }
    mString operator + (double value) {
        return (*this).add(value);
    }
    mString operator + (mString data) {
        return (*this).add(data);
    }
    mString operator + (const String& data) {
        return (*this).add(data);
    }

    // assign
    mString& operator = (const char c) {
        clear();
        return add(c);
    }
    mString& operator = (const char* data) {
        clear();
        return add(data);
    }
    mString& operator = (const __FlashStringHelper *data) {
        clear();
        return add(data);
    }
    mString& operator = (uint32_t value) {
        clear();
        return add(value);
    }
    mString& operator = (int32_t value) {
        clear();
        return add(value);
    }
    mString& operator = (uint16_t value) {
        clear();
        return add(value);
    }
    mString& operator = (int16_t value) {
        clear();
        return add(value);
    }
    mString& operator = (uint8_t value) {
        clear();
        return add(value);
    }
    mString& operator = (int8_t value) {
        clear();
        return add(value);
    }
    mString& operator = (double value) {
        clear();
        return add(value);
    }
    mString& operator = (const String& data) {
        clear();
        return add(data);
    }
    
    // compare
    bool equals_P(PGM_P pstr) {
        return !strcmp_P(buf, pstr);
    }
    bool operator == (const char c) {
        return (buf[0] == c && !buf[1]);
    }
    bool operator == (const char* data) {
        return !strcmp(buf, data);
    }
    bool operator == (uint32_t value) {
        char valBuf[11];
        return !strcmp(buf, ultoa(value, valBuf, DEC));
    }
    bool operator == (uint16_t value) {
        char valBuf[6];
        return !strcmp(buf, utoa(value, valBuf, DEC));
    }
    bool operator == (uint8_t value) {
        char valBuf[4];
        return !strcmp(buf, utoa(value, valBuf, DEC));
    }
    bool operator == (int32_t value) {
        char valBuf[12];
        return !strcmp(buf, ltoa(value, valBuf, DEC));
    }
    bool operator == (int16_t value) {
        char valBuf[7];
        return !strcmp(buf, itoa(value, valBuf, DEC));
    }
    bool operator == (int8_t value) {
        char valBuf[5];
        return !strcmp(buf, itoa(value, valBuf, DEC));
    }
    bool operator == (float value) {
        char valBuf[20];
        return !strcmp(buf, mFtoa(value, 2, valBuf));
    }
    bool operator == (mString data) {
        return !strcmp(buf, data.buf);
    }
    bool operator == (const String& data) {
        return !strcmp(buf, data.c_str());
    }

    // convert & parse
    char operator [] (uint16_t index) const {
        return buf[index];
    }
    char& operator [] (uint16_t index) {
        return buf[index];
    }
    char charAt(uint16_t index) {
        return buf[index];
    }
    void setCharAt(uint16_t index, char c) {
        buf[index] = c;
    }
    
    int32_t toInt(uint16_t from = 0) {
        return atol(buf + from);
    }
    float toFloat(uint16_t from = 0) {
        return atof(buf + from);
    }
    const char* c_str() {
        return buf;
    }

    bool startsWith(const char *data, uint16_t offset = 0) {
        uint16_t dlen = strlen(data);
        return !strncmp(buf + offset, data, dlen);
    }
    bool startsWith_P(PGM_P data, uint16_t offset = 0) {
        uint16_t dlen = strlen_P(data);
        return !strncmp_P(buf + offset, data, dlen);
    }

    void substring(uint16_t from, uint16_t to, char* arr) {
        char backup = buf[++to];
        buf[to] = '\0';
        strcpy(arr, buf + from);
        buf[to] = backup;
    }
    int split(char** ptrs, char div = ',') {
        int i = 0, j = 1;
        ptrs[0] = buf;
        while (buf[i]) {
            if (buf[i] == div) {
                buf[i] = '\0';
                ptrs[j++] = buf + i + 1;
            }
            i++;
        }
        return j;
    }
    void unsplit(char div = ',') {
        uint16_t len = length();
        for (uint16_t i = 0; i < len; i++) {
            if (!buf[i]) buf[i] = div;
        }
    }
    void truncate(uint16_t amount) {
        if (amount >= length()) clear();
        else buf[length() - amount] = '\0';
    }
    void remove(uint16_t index, uint16_t count) {
        uint16_t len = length();
        if (index >= len) return;
        if (count <= 0) return;
        if (count > len - index) {
            count = len - index;
        }
        char *writeTo = buf + index;
        len -= count;
        strncpy(writeTo, buf + index + count, len - index);
        buf[len] = '\0';
    }

    void toLowerCase() {
        if (!length()) return;
        for (char *p = buf; *p; p++) *p = tolower(*p);
    }

    void toUpperCase() {
        if (!length()) return;
        for (char *p = buf; *p; p++) *p = toupper(*p);
    }

    int indexOf(char ch, uint16_t fromIndex = 0) {
        if (fromIndex >= length()) return -1;
        const char* temp = strchr(buf + fromIndex, ch);
        return (temp == NULL) ? -1 : (temp - buf);
    }

    int indexOf(char* ch, uint16_t fromIndex = 0) {
        if (fromIndex >= length()) return -1;
        const char* temp = strstr(buf + fromIndex, ch);
        return (temp == NULL) ? -1 : (temp - buf);
    }
    
    uint16_t parse(void* data, uint8_t bsize, int len, char div = ',') {
        char* bufp = buf;
        uint16_t idx = 0;
        while (1) {
            switch (bsize) {
            case 1: ((int8_t*)data)[idx++] = atoi(bufp);
                break;
            case 2: ((int16_t*)data)[idx++] = atoi(bufp);
                break;
            case 4: ((int32_t*)data)[idx++] = atol(bufp);
                break;
            }
            if (idx == len) return idx;
            char* cur = strchr(bufp, div);
            if (cur) bufp = cur + 1;
            else return idx;
        }
    }
    
    // legacy
    uint16_t parseBytes(uint8_t* data, int len, char div = ',', char ter = '\0') {
        return parse(data, 1, len, div);
    }
    uint16_t parseInts(int* data, int len, char div = ',', char ter = '\0') {
        return parse(data, 2, len, div);
    }
    
    // cast
    operator const char*() {
        return buf;
    }
    operator bool() {
        return _len;
    }
    
private:
    uint16_t _len = 0;
};
#endif
