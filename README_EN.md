This is an automatic translation, may be incorrect in some places. See sources and examples!

# mString
SHARP AS DIARRH AND LIGHT AS A FEATHER STRING REPLACEMENT
- Almost complete analogue of String, but static
- There are several built-in string parsing functions

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by name **mString** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download Library](https://github.com/GyverLibs/mString/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
```cpp
mString<size> str;
```

<a id="usage"></a>
## Usee
```cpp
str.length() - current length
str.clear() - clear
str.add( [char / char* / Fchar / numbers / String] ) - add
str += [char / char* / Fchar / numbers / String] - add
str = str + [char / char* / Fchar / numbers / String] - can be summed
str == [char / char* / numbers / String] - compare
To add/compare with mString use str.buf

Reading a character by index
str[idx]
str.buf[idx]
str.charAt(idx)

Write character by index
str[idx] = with
str.buf[idx] = c
str.setCharAt(idx, c)

Access to char buffer
str.buf
str.c_str()

str.toInt(from) - convert to int starting from from
str.toUint(from) - convert to uint starting from from
str.toFloat(from) - convert to float starting from from
str.startsWith(char*) - starts with
str.substring(from, to, char* arr) - copy from from to to to outer arr
str.truncate(amount) - truncate from the end to amount
str.remove(idx, amount) - remove (cut) amount characters starting from idx
str.toLowerCase() - convert letters to lowercase
str.toUpperCase() - convert letters to uppercase
str.indexOf(char, from) - find char, search starting from from
str.indexOf(char*, from) - find string char, search starting from from
str.split(char* str[], div) - split into strings by div separator

Parsing a batch where the data is separated by a div delimiter and ends with ter
str.parseBytes(data, len, div, ter) - parse the content into a byte array of length len
str.parseInts(data, len, div, ter) - parse content into an int array of length len
div and ter default and NULL
For example, to parse such packets: "12,34,56"
Custom: "12;34;56;78\n"
Parse str.parseBytes(data, len, ';', '\n')
```

<a id="example"></a>
## Example
```cpp
#include "mString.h"
void setup() {
  Serial.begin(9600);
  /*
    mString<50>str;
    str = "kek";
    str = str + ',' + 12345 + ',' + 3.14 + ',' + "hello";
    Serial.println(str.buf);
    str = 1234;
    Serial.println(str.toInt());
    // sketch takes 2522/198 bytes
  */
  /*Cranberry
    // comparison with String
    String str;
    str = "kek";
    str = str + ',' + 12345 + ',' + 3.14 + ',' + "hello";
    Serial println(str);
    str = 1234;
    Serial.println(str.toInt());
    // sketch takes 5370/208 bytes
  */

  // other tests
  mString<50>test;

  test="puk";
  test += "kek";
  test = test + "cheburek" + ',' + 123 + ',' + 3.14;

  Serial.println(test.buf); // puk kek cheburek,123,3.14
  test.clear(); // clear
  // test = ""; // similar

  mString<10> some;
  some="added";
  String str = "string";
  test += some.buf;
  test +=str;

  Serial.println(test.buf); // added String

  // parsing
  test = "1234,2345,3456,4567,5,6";
  Serial.println(test.startsWith("lol2")); // 0
  Serial.println(test.startsWith("1234")); // one
  Serial.println(test.indexOf('k')); // -one

  intdata[10];
  byte get = test.parseInts(data, 10);
  Serial println(get); // 6
  Serial.println();

  for (int i = 0; i < get; i++) {
    Serial.println(data[i]); // 1234 2345 3456 4567 5 6
  }

  // Search
  test = "puk kek hello friend hello world";
  Serial.println(test.indexOf('h')); // eight
  Serial.println(test.indexOf('h', 9)); // 21
  Serial.println(test.indexOf("friend")); // fourteen

  // comparison
  test=12;
  Serial.println(test == 12); // one

  test="kek";
  Serial.println(test == "kek"); // one

  mString<40> test2;
  test2 = "kek";
  Serial.println(test == test2.buf); // one

  // selection
  test = "abcd,123,-456,3.14";
  Serial.println(test.toInt(5)); // 123
  Serial.println(test.toInt(9)); // -456
  Serial.println(test.toFloat(14)); // 3.14

  charbuf3[10];
  test.substring(0, 5, buf3);
  Serial println(buf3); // abcd,1

  test.remove(5, 4);
  Serial.println(test.buf); // abcd,-456,3.14
  test.toUpperCase();
  Serial.println(test.buf); // ABCD,-456,3.14
  test truncate(4);
  Serial.println(test.buf); // ABCD,-456,

  // split
  test = "hello,1234,test,5678";
  char*strings[5];
  int amount = test.split(cranberry strings, ',');
  // action will corrupt the string by adding NULLs to it!

  for (int i = 0; i < amount; i++) {
    Serial.println(strings[i]);
  }
}

void loop() {
}
```

<a id="versions"></a>
## Versions
- v1.0

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!